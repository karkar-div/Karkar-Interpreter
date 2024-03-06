#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <stdio.h>

#include "Instructions.cpp"
#include "Dependencies.cpp"

class VirtualMachine{
	private:
		union address_as_int{
			int64_t value;
			int64_t* address;
		};
		int _stack_size;
		int64_t* Registers;
		int64_t* Stack;
		int64_t* StackPointer;
		int64_t* BasePointer;
		int64_t parameter_value(Parameter* param){
			switch(param->Register){
				case Null:
					return param->Offset;
				case SP:
					return (int64_t)StackPointer;
				case BP:
					return (int64_t)BasePointer;
				default:
					return Registers[param->Register];
			}
		}
		int64_t* destination(Parameter param){
			switch(param.Register){
				case SP:
					return &((int64_t&)StackPointer);
				case BP:
					return &((int64_t&)BasePointer);
				default:
					return &Registers[param.Register];
			}
		}
		int64_t binary_operator(InstructionType type,int64_t value1,int64_t value2){
			switch(type){
				case Add  : return  value1 +  value2;
				case Sub  : return  value1 -  value2;
				case Div  : return  value1 /  value2;
				case Mul  : return  value1 *  value2;
				case Rem  : return  value1 %  value2;
				case And  : return  value1 &  value2;
				case Or   : return  value1 |  value2;
				case Xor  : return  value1 ^  value2;
				case Not  : return !value1          ;
				case Cmp  : return  value1 == value2;
				case CmpB : return  value1 >  value2;
			}
			return 0;
		}
	public:
		VirtualMachine(int64_t entrypoint,int64_t stack_size = 0x100000,int64_t registers_num = 20){
			Stack = new int64_t[stack_size];
			memset(Stack,0,sizeof(int64_t)*stack_size);
			_stack_size = stack_size;
			Registers = new int64_t[registers_num];
			memset(Registers,0,sizeof(int64_t)*registers_num);
			StackPointer = &Stack[stack_size-1];
			BasePointer = &Stack[stack_size-1];
			Registers[RegisterType::IP] = entrypoint;
		}
		void Run(const std::vector<Instruction*>* instructions,const std::vector<Dependency*>* Dependencies,bool debug = false){
			while(true){
				Instruction* instruction = (*instructions)[Registers[RegisterType::IP]];
				if(debug){
					printf("[");
					for(int x = 0;x < 10;x++){
						printf(" ");
						if(StackPointer == &Stack[_stack_size - x])
							printf("SP:");
						if(BasePointer == &Stack[_stack_size - x])
							printf("BP:");
						printf("%zd ",Stack[_stack_size - x]);
					}
					printf("]\n");
					printf("AX:%zd ",Registers[RegisterType::AX]);
					printf("IP:%zd ",Registers[RegisterType::IP]);
					printf("SP:%zd ",StackPointer);
					instruction->debug();
				}
				switch (instruction->Type){
					/* memory control */
					case drfrnc:{
						address_as_int stack_top;
						stack_top.value = *StackPointer;
						*StackPointer = *(stack_top.address);
						break;
					}
					/* control flow */
					case Jmp:{
						Registers[RegisterType::IP] = parameter_value(&(instruction->Parameters[FIRST]));
						Registers[RegisterType::IP]--;
						break;
					}
					case Nop:{
						break;                        
					}
					case JN:{
						if(Registers[RegisterType::CR] == false){
							Registers[RegisterType::IP] = parameter_value(&(instruction->Parameters[FIRST]));
							Registers[RegisterType::IP]--;
						}
						break;
					}
					/* Stack minipulation (not that the Stack grows upowrd)*/
					case Push:{
						StackPointer--;
						if(instruction->ParametersNum == 1)
							*StackPointer = parameter_value(&(instruction->Parameters[FIRST]));
						break;                        
					}
					case Pop:{
						if(instruction->ParametersNum == 1)
							*(destination(instruction->Parameters[FIRST])) = *StackPointer;
						StackPointer++;
						break;                        
					}
					case Mov:
						if(instruction->ParametersNum == 2)
							*(destination(instruction->Parameters[FIRST])) = parameter_value(&(instruction->Parameters[SECOND]));
						if(instruction->ParametersNum == 0){
							address_as_int temp;
							temp.value = *(StackPointer+1);
							*temp.address = *StackPointer;
							StackPointer++;
						}
						break;
					case Exit:{
						return;                        
					}
					case so_call:{
						std::list<int64_t>* args = new std::list<int64_t>;
						for(int x = 0; x < parameter_value(&(instruction->Parameters[SECOND])) ;x++){
							args->push_front(*StackPointer);
							StackPointer++;
						}
						Registers[RegisterType::AX] = (*Dependencies)[parameter_value(&(instruction->Parameters[FIRST]))]->Run(args);
						delete args;
						break;
					}
					/* binary operators */
					default:
						if(instruction->ParametersNum == 0){
							*(StackPointer+1) = binary_operator(
								instruction->Type,
								*(StackPointer+1),
								*StackPointer
							);
							StackPointer++;
						}
						if(instruction->ParametersNum == 2)
							*(destination(instruction->Parameters[FIRST])) = binary_operator(
								instruction->Type,
								parameter_value(&(instruction->Parameters[FIRST])),
								parameter_value(&(instruction->Parameters[SECOND]))
							);
						break;
				}
				Registers[RegisterType::IP]++;
			}
			throw("Unsuccessful Unknown exit");
		}
		~VirtualMachine(){
			delete Stack;
			delete Registers;
		}
};
