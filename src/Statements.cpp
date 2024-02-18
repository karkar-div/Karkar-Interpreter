#include "Expressions.cpp"
#include <list>

class Instruction;

class Statement{
	public:
		virtual void debug(int tabs){}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions){}
};

class EmptyStatement : public Statement{
	public:
		EmptyStatement(){
			
		}
		void debug(int tabs){
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Empty Statement\n");
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			instructions->push_back(new Instruction(InstructionType::Nop));
		}
		// nothing to look at
};

class ReturnStatement : public Statement{
	public:
		Expression* ReturnedExpression;
		ReturnStatement(Expression* expr){
			ReturnedExpression = expr;
		}
		void debug(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Return Statement\n");
			ReturnedExpression->debug(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			ReturnedExpression->GenerateByteCode(instructions);
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::AX,0,false))); // the value is already in the top of the stack
			/* collabsing the stack*/{
				/* leave Instruction hand implemented */{
					instructions->push_back(new Instruction(InstructionType::Mov,Parameter(RegisterType::SP,0,false),Parameter(RegisterType::BP,0,false))); // Restore the stack pointer to the orignal position
					instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BP,0,false))); // Restore the orignal Base Pointer, 
				}

				// do to the pop command subtracting the stack pointer. now it points to the return address

				/* ret Instruction hand implemented */{
					instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BX,0,false))); // restore the return address to a general regester so to jump to
					instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::BX,0,false))); // jump to the return address setuped by the caller
					// jmp to R AKA Executions start from the regester regester is
				}
			}
		}
};

class CompoundStatement : public Statement{
	public:
		std::list<Statement*>* Statements;
		int Count;
		CompoundStatement(std::list<Statement*>* list ){
			Statements = list;
		}
		void debug(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Compound Statement\n");
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->debug(tabs+1);
			}
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			Symbol_Tables->Push(new std::list<Symbol*>);
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->GenerateByteCode(instructions);
			}
			Symbol_Tables->Pop();
		}
};

class IfStatement : public CompoundStatement{
	public:
		Expression* Condition;
		IfStatement(std::list<Statement*>* list,Expression* condition):CompoundStatement(list){
			Condition = condition;
		}
		void debug(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("If Statement\n");
			Condition->debug(tabs+1);
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->debug(tabs+1);
			}
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {

			// the result will be in the top of the stack
			Condition->GenerateByteCode(instructions);
			
			// we will pop the result into a compairation register
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::CR,0,false)));
			
			// skip if false by jumping ,continu if true by the command failing. the jump to line N is unknown
			Instruction* jmp_instruction = new Instruction(InstructionType::JN,Parameter(RegisterType::Null,0,false));
			instructions->push_back(jmp_instruction);

			Symbol_Tables->Push(new std::list<Symbol*>);
			// this statement will be skipped if false
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->GenerateByteCode(instructions);
			}
			Symbol_Tables->Pop();

			// a Nop instruction works as a label
			instructions->push_back(new Instruction(InstructionType::Nop));
			// updating the the jump address meant for skipping to the nop instruction aka the label
			jmp_instruction->Parameters[0].Offset = instructions->size() - 1;


		}
};

class WhileStatement : public CompoundStatement{
	public:
		Expression* Condition;
		WhileStatement(std::list<Statement*>* list,Expression* condition):CompoundStatement(list){
			Condition = condition;
		}
		void debug(int tabs) override{
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("While Statement\n");
			Condition->debug(tabs+1);
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->debug(tabs+1);
			}
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {

			// add a label to compaire again
			instructions->push_back(new Instruction(InstructionType::Nop));
			int comparation_line =  instructions->size() - 1;

			// the result will be in the top of the stack
			Condition->GenerateByteCode(instructions);
			
			// we will pop the result into a compairation register
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::CR,0,false)));
			
			// skip if false by jumping ,continu if true by the command failing. the jump to line N is unknown
			Instruction* jmp_instruction = new Instruction(InstructionType::JN,Parameter(RegisterType::Null,0,false));
			instructions->push_back(jmp_instruction);

			Symbol_Tables->Push(new std::list<Symbol*>);
			// this statement will be skipped if false
			for (std::list<Statement*>::iterator it = Statements->begin(); it != Statements->end(); ++it) {
				auto g = *it;
				g->GenerateByteCode(instructions);
			}
			Symbol_Tables->Pop();

			// jump to compair again ( note : this will happen only if true to compaire again)
			instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::Null,comparation_line,false)));

			// a Nop instruction works as a label
			instructions->push_back(new Instruction(InstructionType::Nop));
			// updating the the jump address meant for skipping to the nop instruction aka the label
			jmp_instruction->Parameters[0].Offset = instructions->size() - 1;
		}
};

// TODO
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
		void debug(int tabs) override{
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Var Define Statement:\n",Identifier);
			for(int x = 0;x < tabs+1;x++)printf("    ");
			printf("Identifier:%s\n",Identifier);
			Type->debug(tabs+1);
		}
};

class ExpressionBasedStatement : public Statement{
	public:
		Expression* TheExpression;
		ExpressionBasedStatement(Expression* expr){
			TheExpression = expr;
		}
		void debug(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Expression Based Statement\n");
			TheExpression->debug(tabs+1);
		}
		void GenerateByteCode(std::list<Instruction*>* instructions) override {
			TheExpression->GenerateByteCode(instructions);
			instructions->push_back(new Instruction(InstructionType::Pop));
		}
};

