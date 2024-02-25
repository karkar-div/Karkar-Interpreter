#include <string>
#include <stack>
#include <list>

#include "Instructions.cpp"

#include "Symbols&Types.cpp"

class Expression{
	protected:
		void derefrence(std::list<Instruction*>* instructions,int derefrence_num){
			for (int i = 0; i < derefrence_num; i++)
				instructions->push_back(new Instruction(InstructionType::drfrnc));
		}
	public:
		virtual void debug(int tabs){}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions,int derefrence_num = 0){}
};

class BinaryExpression : public Expression{
	public:
		enum Type{
			Addition = InstructionType::Add ,
			Subtraction = InstructionType::Sub ,
			Divition = InstructionType::Div,
			Multipication = InstructionType::Mul,
			Remanider = InstructionType::Rem,
			Comparation = InstructionType::Cmp ,
			BiggerThanComparation = InstructionType::CmpB,
			BitwizeAnd = InstructionType::And,
			BitwizeOr = InstructionType::Or,
			BitwizeXor = InstructionType::Xor,
			MemberAccess = 1002 ,
			PointerMemberAccess = 1003,
			Moving  = 1004,
		};
		Expression* FirstExpression;
		Expression* SecondExpression;
		Type Operation;
		BinaryExpression(Expression* first_expr,Expression* second_expr,Type operation){
			FirstExpression = first_expr;
			SecondExpression = second_expr;
			Operation = operation;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Binary Expression:");
			switch (Operation){
				case Addition : printf("Addition"); break;
				case Subtraction : printf("Subtraction"); break;
				case Divition : printf("Divition"); break;
				case Multipication :printf("Multipication"); break;
				case Remanider :printf("Remanider"); break;
				case Comparation :printf("Comparation"); break;
				case BiggerThanComparation :printf("BiggerThanComparation"); break;
				case MemberAccess :printf("MemberAccess"); break;
				case PointerMemberAccess :printf("PointerMemberAccess"); break;
				case BitwizeAnd :printf("BitwizeAnd"); break;
				case BitwizeOr :printf("BitwizeOr"); break;
				case BitwizeXor :printf("BitwizeXor"); break;
				case Moving :printf("Moving"); break;
			}
			printf("\n");
			FirstExpression->debug(tabs+1);
			SecondExpression->debug(tabs+1);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			switch(Operation){
				case Moving:
					FirstExpression->GenerateByteCode(instructions,derefrence_num-1);
					SecondExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction(InstructionType::Mov));
					break;
				case MemberAccess:
				case PointerMemberAccess:
					printf("UnFinished");
					break;
				default:
					FirstExpression->GenerateByteCode(instructions);
					SecondExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction((InstructionType)Operation));
					derefrence(instructions,derefrence_num);
					break;
			}
		}
		~BinaryExpression(){
			delete FirstExpression;
			delete SecondExpression;
		}
};

class UnaryExpression : public Expression{
	public:
		enum Type{
			BitwizeNot ,
			Derefrence ,
			Refrence ,
			LogicalNot ,
			Negativity ,
		};
		Expression* FirstExpression;
		Type Operation;
		UnaryExpression(Expression* first_expr,Type operation){
			FirstExpression = first_expr;
			Operation = operation;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Unary Expression:");
			switch(Operation){
				case BitwizeNot : printf("BitwizeNot"); break;
				case Derefrence : printf("Derefrence"); break;
				case Refrence   : printf("Refrence");   break;
				case LogicalNot : printf("LogicalNot"); break;
				case Negativity : printf("Negativity"); break;
			}
			printf("\n");
			FirstExpression->debug(tabs+1);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			switch(Operation){
				case BitwizeNot :
					FirstExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction(InstructionType::Not));
					derefrence(instructions,derefrence_num);
					break;
				case Derefrence :                     
					FirstExpression->GenerateByteCode(instructions,derefrence_num+1);
					break;
				case Refrence   : 
					FirstExpression->GenerateByteCode(instructions,derefrence_num-1);
					break;
				case LogicalNot :
					FirstExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction(InstructionType::Not));
					derefrence(instructions,derefrence_num);
					break;
				case Negativity :
					instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,0,false)));
					FirstExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction(InstructionType::Sub));
					derefrence(instructions,derefrence_num);
					break;
			}
		}
		~UnaryExpression(){
			delete FirstExpression;
		}
};

// TODO
class ArrayAccessExpression : public Expression{
	public:
		Expression* Array;
		Expression* Index;
		ArrayAccessExpression(Expression* array,Expression* index){
			Array = array;
			Index = index;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Array Access Expression\n");
			Array->debug(tabs+1);
			Index->debug(tabs+1);
		}
		~ArrayAccessExpression(){
			delete Array;
			delete Index;
		}
};

class NumberExpression : public Expression{
	public:
		int Value;
		NumberExpression(int value){
			Value = value;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Number Expression: %d\n",Value);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,Value,false))); // the value is already in the top of the stack
			derefrence(instructions,derefrence_num);
		}
};

// TODO
class StringExpression : public Expression{
	public:
		char* Value;
		StringExpression(char* value){
			Value = value;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("String Expression:%s\n",Value);
		}
		~StringExpression(){
			free(Value);
		}
};

// TODO
class IdentifierExpression : public Expression{
	public:
		char* Name;
		IdentifierExpression(char* name){
			Name = name;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Identifier Expression:%s\n",Name);
		}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions,int derefrence_num = 0){
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::BP,0,false))); // the value is already in the top of the stack
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,Symbol_Tables->Find(Name),false)));
			instructions->push_back(new Instruction(InstructionType::Sub));
			// TODO add referencing
			derefrence(instructions,derefrence_num+1);
		}
		~IdentifierExpression(){
			free(Name);
		}
};

class FunctionCallExpression : public Expression{
	public:
		Expression* Function;
		std::list<Expression*>* Parameters;
		FunctionCallExpression(Expression* function,std::list<Expression*>* parameters){
			Function = function;
			Parameters = parameters;
		}
		void debug (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Function Call Expression\n");
			Function->debug(tabs+1);
			for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it)
				(*it)->debug(tabs+1);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			if(Symbol_Tables->FindDefinition(((IdentifierExpression*)Function)->Name) != -1){
				Instruction* jmp_int = new Instruction(InstructionType::Push,Parameter(RegisterType::Null,0,false));
				instructions->push_back(jmp_int); 

				instructions->push_back(new Instruction(InstructionType::Push)); 

				for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) 
					(*it)->GenerateByteCode(instructions);
				for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) 
					instructions->push_back(new Instruction(InstructionType::Pop));
				
				instructions->push_back(new Instruction(InstructionType::Pop));

				instructions->push_back(
					new Instruction(
						InstructionType::Jmp,
						Parameter(
							RegisterType::Null,
							Symbol_Tables->FindDefinition(
								((IdentifierExpression*)Function)->Name
							),
							false
				)));

				instructions->push_back(new Instruction(InstructionType::Nop)); 
				jmp_int->Parameters[FIRST].Offset = instructions->size()-1;

				instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::AX,0,false)));
			}else if(Symbol_Tables->FindExternedFunction(((IdentifierExpression*)Function)->Name ) != -1){
				
			}
		}
		~FunctionCallExpression(){
			delete Parameters;
			delete Function;
		}
};
