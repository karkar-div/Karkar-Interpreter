#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <stdio.h>

#include "Instructions.cpp"




int parameter_value(int64_t* registers,Parameter* parameter){
	if(parameter->Register != Null)
		return registers[parameter->Register] 
			 + parameter->Offset;
	else return parameter->Offset;
}

int64_t binary_operator(InstructionType type,int64_t value1,int64_t value2){
	printf("%d,%d\n",value1,value2);
	switch(type){
		case Add  : return value1 + value2;
		case Sub  : return value1 - value2;
		case Div  : return value1 / value2;
		case Mul  : return value1 * value2;
		case Rem  : return value1 % value2;
		case And  : return value1 & value2;
		case Or   : return value1 | value2;
		case Xor  : return value1 ^ value2;
		case Not  : return !value1        ;
		case Cmp  : return value1 ==value2;
		case CmpB : return value1 > value2;
	}
	return 0;
}



int Run(std::vector<Instruction*>* instructions,int entrypoint,int instruction_size,int stack_size = 0x100,bool debug = false){
	int64_t registers[20];
	memset(registers,0,sizeof(registers));
	registers[RegisterType::SP] = stack_size-1;
	registers[RegisterType::BP] = stack_size-1;
	registers[RegisterType::IP] = entrypoint;
	int64_t* stack = new int64_t[stack_size];
	memset(stack,0,sizeof(stack));
	for(;registers[RegisterType::IP] < instruction_size;registers[RegisterType::IP]++){
		Instruction* instruction = (*instructions)[registers[RegisterType::IP]];
		if(debug){
			printf("AX:%d ",registers[RegisterType::AX]);
			printf("IP:%d ",registers[RegisterType::IP]);
			printf("SP:%d ",registers[RegisterType::SP]);
			for(int x = 0;x < 10;x++){
				printf("%d ",stack[stack_size-(1+x)]);
			}
			instruction->debug();
		}

		switch (instruction->Type){
			/* memory control */
			case drfrnc:{
				stack[registers[RegisterType::SP]] = stack[stack[registers[RegisterType::SP]]];
				break;
			}
			/* control flow */
			case Jmp:{
				registers[RegisterType::IP] = parameter_value(registers,&(instruction->Parameters[FIRST]));
				break;
			}
			case Nop:{
				break;
			}
			case JN:{
				if(registers[RegisterType::CR] == false){
					registers[RegisterType::IP] = parameter_value(registers,&(instruction->Parameters[FIRST]));
				}
				break;
			}
			/* stack minipulation (not that the stack grows upowrd)*/
			case Push:{
				registers[RegisterType::SP]--;
				stack[registers[RegisterType::SP]] = parameter_value(registers,&(instruction->Parameters[FIRST]));
				break;
			}
			case Pop:{
				if(instruction->ParametersNum == 1){
					int64_t* destenation;
					if(instruction->Parameters[FIRST].Register == Null){
						destenation = &stack[parameter_value(registers,&(instruction->Parameters[SECOND]))];
					}else{
						destenation = &registers[instruction->Parameters[FIRST].Register];
					}
					*destenation = stack[registers[RegisterType::SP]];
				}
				registers[RegisterType::SP]++;
				break;
			}
			case Mov:{
				if(instruction->ParametersNum == 2){
					int64_t* destenation;
					if(instruction->Parameters[FIRST].Register == Null){
						destenation = &stack[parameter_value(registers,&(instruction->Parameters[SECOND]))];
					}else{
						destenation = &registers[instruction->Parameters[FIRST].Register];
					}
					*destenation = parameter_value(registers,&(instruction->Parameters[SECOND]));
				}if(instruction->ParametersNum == 0){
					stack[registers[RegisterType::SP-1]] = stack[registers[RegisterType::SP]];
					registers[RegisterType::SP-1]--;
				}
				break;
			}
			/* binary operators */
			default:{
				switch(instruction->ParametersNum){
					case 0:{
						stack[registers[RegisterType::SP]+1] = binary_operator(
							instruction->Type,
							stack[registers[RegisterType::SP]+1],
							stack[registers[RegisterType::SP]]
						);
						registers[RegisterType::SP]++;
						break;
					}
					case 2:{
						int64_t* destenation;
						if(instruction->Parameters[FIRST].Register == Null){
							destenation = &stack[parameter_value(registers,&(instruction->Parameters[SECOND]))];
						}else{
							destenation = &registers[instruction->Parameters[FIRST].Register];
						}
						*destenation = binary_operator(
							instruction->Type,
							parameter_value(registers,&(instruction->Parameters[FIRST])),
							parameter_value(registers,&(instruction->Parameters[SECOND]))
						);
						break;
					}
				}
				break;
			}
		}
		
	}
	return registers[RegisterType::IP];
}