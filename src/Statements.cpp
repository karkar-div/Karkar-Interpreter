#pragma once

#include "Expressions.cpp"
#include <list>

class Instruction;

class Statement{
	public:
		virtual void info(int tabs){}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions){}
		virtual ~Statement() {}
};

class EmptyStatement : public Statement{
	public:
		EmptyStatement(){}
		void info(int tabs){
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Empty Statement\n");
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			instructions->push_back(new Instruction(InstructionType::Nop));
		}
		~EmptyStatement() override {}
};

class ReturnStatement : public Statement{
	public:
		Expression* ReturnedExpression;
		ReturnStatement(Expression* expr){
			ReturnedExpression = expr;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Return Statement\n");
			ReturnedExpression->info(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			ReturnedExpression->GenerateByteCode(instructions);
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::AX,0))); // the value is already in the top of the stack
			/* leave Instruction hand implemented */
			// the leave instruction meant to collapse the stack by moving bp to sp
			// it also pop the stack top aka old bp into bp
			instructions->push_back(new Instruction(InstructionType::Mov,Parameter(RegisterType::SP,0),Parameter(RegisterType::BP,0)));
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BP,0))); 
		
			/* ret Instruction hand implemented */
			// a ret instruction jump to the address stored at he top of the stack,
			// this address is pushed by the caller 
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BX,0))); 
			instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::BX,0))); 
			
		}
		~ReturnStatement() override {
			delete ReturnedExpression;
		}
};

class CompoundStatement : public Statement{
	public:
		std::list<Statement*>* Statements;
		CompoundStatement(std::list<Statement*>* list ){
			Statements = list;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Compound Statement\n");
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it)
				(*it)->info(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			Symbol_Tables->PushNewTable();
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it)
				(*it)->GenerateByteCode(instructions);
			Symbol_Tables->Pop();
		}
		~CompoundStatement() override {
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it)
				delete (*it);
			delete Statements;
		}
};

class IfStatement : public CompoundStatement{
	public:
		/* 'Statements' came from the CompoundStatement class */
		Expression* Condition;
		IfStatement(std::list<Statement*>* list,Expression* condition):CompoundStatement(list){
			Condition = condition;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("If Statement\n");
			Condition->info(tabs+1);
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it)
				(*it)->info(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {

			// the result will be in the top of the stack
			Condition->GenerateByteCode(instructions);
			
			// we will pop the result into a compairation register
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::CR,0)));
			
			// skip if false by jumping ,continu if true by the command failing. the jump to line N is unknown
			Instruction* jmp_instruction = new Instruction(InstructionType::JN,Parameter(RegisterType::Null,0));
			instructions->push_back(jmp_instruction);

			Symbol_Tables->PushNewTable();
			// this statement will be skipped if false
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it)
				(*it)->GenerateByteCode(instructions);
			Symbol_Tables->Pop();

			// a Nop instruction works as a label
			instructions->push_back(new Instruction(InstructionType::Nop));
			// updating the the jump address meant for skipping to the nop instruction aka the label
			jmp_instruction->Parameters[0].Offset = instructions->size() - 1;


		}
		~IfStatement() override {
			// resources for Statements is already freed at ~CompoundStatement()
			delete Condition;
		}
};

class WhileStatement : public CompoundStatement{
	public:
		Expression* Condition;
		WhileStatement(std::list<Statement*>* list,Expression* condition):CompoundStatement(list){
			Condition = condition;
		}
		void info(int tabs) override{
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("While Statement\n");
			Condition->info(tabs+1);
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) 
				(*it)->info(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {

			// add a label to compaire again
			instructions->push_back(new Instruction(InstructionType::Nop));
			int comparation_line =  instructions->size() - 1;

			// the result will be in the top of the stack
			Condition->GenerateByteCode(instructions);
			
			// we will pop the result into a compairation register
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::CR,0)));
			
			// skip if false by jumping ,continu if true by the command failing. the jump to line N is unknown
			Instruction* jmp_instruction = new Instruction(InstructionType::JN,Parameter(RegisterType::Null,0));
			instructions->push_back(jmp_instruction);

			Symbol_Tables->PushNewTable();
			// this statement will be skipped if false
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) 
				(*it)->GenerateByteCode(instructions);
			Symbol_Tables->Pop();

			// jump to compair again ( note : this will happen only if true to compaire again)
			instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::Null,comparation_line)));

			// a Nop instruction works as a label
			instructions->push_back(new Instruction(InstructionType::Nop));
			// updating the the jump address meant for skipping to the nop instruction aka the label
			jmp_instruction->Parameters[0].Offset = instructions->size() - 1;
		}
		~WhileStatement()  {
			// resources for Statements is already freed at ~CompoundStatement()
			delete Condition;
		}
};

class VarDefineStatement : public Statement{
	public:
		VarType* Type;
		char* Identifier;
		VarDefineStatement(VarType* type,char * identifier){
			Type = type;
			Identifier = identifier;
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			Symbol_Tables->Tables[Symbol_Tables->Top]->push_back(new Symbol(Identifier,Type));
		}
		void info(int tabs) override{
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Var Define Statement:\n");
			for(int x = 0;x < tabs+1;x++)printf("    ");
			printf("Identifier:%s\n",Identifier);
			Type->info(tabs+1);
		}
		~VarDefineStatement() override {
			delete Type;
			free(Identifier);
		}
};

class ExpressionBasedStatement : public Statement{
	public:
		Expression* TheExpression;
		ExpressionBasedStatement(Expression* expr){
			TheExpression = expr;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Expression Based Statement\n");
			TheExpression->info(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			TheExpression->GenerateByteCode(instructions);
			instructions->push_back(new Instruction(InstructionType::Pop));
		}
		~ExpressionBasedStatement() override {
			delete TheExpression;
		}
};

