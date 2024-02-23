#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <stdio.h>

#include "Instructions.cpp"


class VirtualMachine{
	private:
		int64_t parameter_value(Parameter* parameter){
			if(parameter->Register != Null)
				return Registers[parameter->Register] 
					+ parameter->Offset;
			else return parameter->Offset;
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
		int64_t* destenation(Instruction* instruction){
			if(instruction->Parameters[FIRST].Register == Null) 
				return &Stack[parameter_value(&(instruction->Parameters[SECOND]))];
			else
				return &Registers[instruction->Parameters[FIRST].Register];
		}
	public:
		int64_t* Registers;
		int64_t* Stack;
		VirtualMachine(int64_t entrypoint,int64_t stack_size = 0x100000,int64_t registers_num = 20){
			Registers = new int64_t[registers_num];
			memset(Registers,0,sizeof(int64_t)*registers_num);
			Registers[RegisterType::SP] = stack_size-1;
			Registers[RegisterType::BP] = stack_size-1;
			Registers[RegisterType::IP] = entrypoint;

			Stack = new int64_t[stack_size];
			memset(Stack,0,sizeof(Stack));
		}
		void Run(std::vector<Instruction*>* instructions,bool debug = false){
			for(;;Registers[RegisterType::IP]++){
				Instruction* instruction = (*instructions)[Registers[RegisterType::IP]];
				if(debug){
					printf("AX:%d ",Registers[RegisterType::AX]);
					printf("IP:%d ",Registers[RegisterType::IP]);
					printf("SP:%d ",Registers[RegisterType::SP]);
					instruction->debug();
				}
				switch (instruction->Type){
					/* memory control */
					case drfrnc:{
						Stack[Registers[RegisterType::SP]] = Stack[Stack[Registers[RegisterType::SP]]];
						break;
					}
					/* control flow */
					case Jmp:{
						Registers[RegisterType::IP] = parameter_value(&(instruction->Parameters[FIRST]));
						break;
					}
					case Nop:{
						break;
					}
					case JN:{
						if(Registers[RegisterType::CR] == false){
							Registers[RegisterType::IP] = parameter_value(&(instruction->Parameters[FIRST]));
						}
						break;
					}
					/* Stack minipulation (not that the Stack grows upowrd)*/
					case Push:{
						Registers[RegisterType::SP]--;
						Stack[Registers[RegisterType::SP]] = parameter_value(&(instruction->Parameters[FIRST]));
						break;
					}
					case Pop:{
						if(instruction->ParametersNum == 1){
							*(destenation(instruction)) = Stack[Registers[RegisterType::SP]];
						}
						Registers[RegisterType::SP]++;
						break;
					}
					case Mov:{
						if(instruction->ParametersNum == 2){
							*(destenation(instruction)) = parameter_value(&(instruction->Parameters[SECOND]));
						}if(instruction->ParametersNum == 0){
							Stack[Stack[Registers[RegisterType::SP]+1]] = Stack[Registers[RegisterType::SP]];
							Registers[RegisterType::SP]++;
						}
						break;
					}
					case Exit:
						return;
					/* binary operators */
					default:{
						if(instruction->ParametersNum == 0){
							Stack[Registers[RegisterType::SP]+1] = binary_operator(
								instruction->Type,
								Stack[Registers[RegisterType::SP]+1],
								Stack[Registers[RegisterType::SP]]
							);
							Registers[RegisterType::SP]++;
						}
						if(instruction->ParametersNum == 2)
							*(destenation(instruction)) = binary_operator(
								instruction->Type,
								parameter_value(&(instruction->Parameters[FIRST])),
								parameter_value(&(instruction->Parameters[SECOND]))
							);
						break;
					}
				}
			}
			throw("Unsuccesfull Unknown exit");
		}
};
