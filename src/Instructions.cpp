#pragma once

#include <stdio.h>

#define FIRST 0
#define SECOND 1

enum InstructionType{
	// 0 for no  parameter
	// 1 for one parameter
	// 2 for two parameters
	Mov,  //  0 , 2 
	/* Binary Operators  */
	Add  , // 0 , 2
	Sub  , // 0 , 2
	Div  , // 0 , 2
	Mul  , // 0 , 2
	Rem  , // 0 , 2
	And  , // 0 , 2
	Or   , // 0 , 2
	Xor  , // 0 , 2
	Not  , // 0 , 2
	Cmp  , // 0 , 2
	CmpB , // 0 , 2
	/* control flow */
	Jmp, // 1 ( pop only accept regesters)
	Nop, // 0
	JN,  // 1
	/* stack related */
	Push, // 0 , 1
	Pop,  // 0 , 1
	/* lea */
	drfrnc, // 0
	/* other */
	so_call, // 2 first: function index, second: agrument number
	Exit,    // special exit code
};

enum RegisterType{
	Null,
	SP, // stack pointer register
	BP, // base pointer register
	AX, // return value register
	DI, // general use register
	BX, // general use register
	CR, // comparetion register
	IP
};

struct Parameter{
	bool IsDerefrence;
	RegisterType Register;
	int Offset;
	Parameter(RegisterType type,int offset,bool is_derefrence){
		IsDerefrence = is_derefrence;
		Register = type;
		Offset = offset;
	}
	Parameter(){

	}
	void PrintOffset(const char * str,int offset){
		if(IsDerefrence)printf("[");
		else printf(" ");
		printf(str);

		if (Offset > 0) // AKA Positive
			printf("+%d",offset);
		if (Offset == 0 && Register == RegisterType::Null)
			printf("%d",offset);
		if (Offset < 0)
			printf("%d",offset);// printf does it atuomaticly
		
		if(IsDerefrence)printf("[");
		else printf(" ");
		
	}
	void debug(){
		switch (Register){
			case Null:PrintOffset(""  ,Offset);break;
			case SP  :PrintOffset("SP",Offset);break;
			case BP  :PrintOffset("BP",Offset);break;
			case AX  :PrintOffset("AX",Offset);break;
			case DI  :PrintOffset("DI",Offset);break;
			case BX  :PrintOffset("BX",Offset);break;
			case CR  :PrintOffset("CR",Offset);break;
			default  :PrintOffset("??",Offset);break;
		}
	}
};

struct Instruction{
	InstructionType Type;
	int ParametersNum;
	Parameter Parameters[2];
	Instruction(InstructionType type){
		ParametersNum = 0; // AKA stack based
		Type = type;
	}
	Instruction(InstructionType type,Parameter value){
		ParametersNum = 1; // AKA unary bytecode operator
		Parameters[FIRST] = value;
		Type = type;
	}
		Instruction(InstructionType type,Parameter first_value,Parameter second_value){
		ParametersNum = 2; // AKA binary bytecode operator
		Parameters[FIRST] = first_value;
		Parameters[SECOND] = second_value;
		Type = type;
	}
	void debug(){
		switch (Type){
			case Mov    : printf("Mov    ");break;
			case Push   : printf("Push   ");break;
			case Pop    : printf("Pop    ");break;
			case Add    : printf("Add    ");break;
			case Sub    : printf("Sub    ");break;
			case Div    : printf("Div    ");break;
			case Mul    : printf("Mul    ");break;
			case Rem    : printf("Rem    ");break;
			case And    : printf("And    ");break;
			case Or     : printf("Or     ");break;
			case Xor    : printf("Xor    ");break;
			case Not    : printf("Not    ");break;
			case Cmp    : printf("Cmp    ");break;
			case CmpB   : printf("CmpB   ");break;
			case Jmp    : printf("Jmp    ");break;
			case Nop    : printf("Nop    ");break;
			case JN     : printf("JN     ");break;
			case drfrnc : printf("drfrnc ");break;
			case so_call: printf("so_call");break;
			case Exit   : printf("exit   ");break;
			default     : printf("OMG    ");break;
		}
		printf(" ");
		for(int i = 0 ; i < ParametersNum;i++){
			Parameters[i].debug();
			if(i < ParametersNum-1)
				printf(",");
		}
		printf("\n");
	}
};