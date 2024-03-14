#include <string>
#include <stack>
#include <list>

#include "Instructions.cpp"
#include "Symbols&Types.cpp"
#include "DataSections.cpp"

class Expression{
	protected:
		void derefrence(std::list<Instruction*>* instructions,int derefrence_num){
			for (int i = 0; i < derefrence_num; i++)
				instructions->push_back(new Instruction(InstructionType::drfrnc));
		}
	public:
		virtual void info(int tabs){}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions,int derefrence_num = 0){}
		virtual ~Expression(){}
};

class BinaryExpression : public Expression{
	public:
		enum Type{
			Addition              = InstructionType::Add ,
			Subtraction           = InstructionType::Sub ,
			Divition              = InstructionType::Div,
			Multipication         = InstructionType::Mul,
			Remanider             = InstructionType::Rem,
			Comparation           = InstructionType::Cmp ,
			BiggerThanComparation = InstructionType::CmpB,
			BitwizeAnd            = InstructionType::And,
			BitwizeOr             = InstructionType::Or,
			BitwizeXor            = InstructionType::Xor,
			MemberAccess        = -1 ,
			PointerMemberAccess = -2,
			Moving              = -3,
		};
		Expression* FirstExpression;
		Expression* SecondExpression;
		Type Operation;
		BinaryExpression(Expression* first_expr,Expression* second_expr,Type operation){
			FirstExpression = first_expr;
			SecondExpression = second_expr;
			Operation = operation;
		}
		void info (int tabs) override {
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
			FirstExpression->info(tabs+1);
			SecondExpression->info(tabs+1);
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
		~BinaryExpression() override {
			delete FirstExpression;
			delete SecondExpression;
		}
};

class UnaryExpression : public Expression{
	public:
		enum Type{
			BitwizeNot ,
			Derefrence ,
			Refrence   ,
			LogicalNot ,
			Negativity ,
		};
		Expression* FirstExpression;
		Type Operation;
		UnaryExpression(Expression* first_expr,Type operation){
			FirstExpression = first_expr;
			Operation = operation;
		}
		void info (int tabs) override {
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
			FirstExpression->info(tabs+1);
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
					instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,0)));
					FirstExpression->GenerateByteCode(instructions);
					instructions->push_back(new Instruction(InstructionType::Sub));
					derefrence(instructions,derefrence_num);
					break;
			}
		}
		~UnaryExpression() override {
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
		void info (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Array Access Expression\n");
			Array->info(tabs+1);
			Index->info(tabs+1);
		}
		~ArrayAccessExpression() override {
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
		void info (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Number Expression: %d\n",Value);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,Value))); // the value is already in the top of the stack
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
		void info (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("String Expression:%s\n",Value);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			strcpy(DataSection+DataSectionSize,Value);
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::data,0)));
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,DataSectionSize)));
			instructions->push_back(new Instruction(InstructionType::Add));
			DataSectionSize += strlen(Value)+1;
		}
		~StringExpression() override {
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
		void info (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Identifier Expression:%s\n",Name);
		}
		virtual void GenerateByteCode(std::list<Instruction*>* instructions,int derefrence_num = 0){
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::BP,0))); // the value is already in the top of the stack
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::Null,Symbol_Tables->Find(Name))));
			instructions->push_back(new Instruction(InstructionType::Sub));
			// TODO add referencing
			derefrence(instructions,derefrence_num+1);
		}
		~IdentifierExpression() override {
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
		void info (int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Function Call Expression\n");
			Function->info(tabs+1);
			for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it)
				(*it)->info(tabs+1);
		}
		void GenerateByteCode (std::list<Instruction*>* instructions,int derefrence_num = 0) override {
			if(Symbol_Tables->FindDefinition(((IdentifierExpression*)Function)->Name) != -1){
				Instruction* jmp_int = new Instruction(InstructionType::Push,Parameter(RegisterType::Null,0));
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
							)
				)));

				instructions->push_back(new Instruction(InstructionType::Nop)); 
				jmp_int->Parameters[FIRST].Offset = instructions->size()-1;

				instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::AX,0)));
			}else if(Symbol_Tables->FindExternedFunction(((IdentifierExpression*)Function)->Name ) != -1){
				for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) 
					(*it)->GenerateByteCode(instructions);
				instructions->push_back(
					new Instruction(
						InstructionType::so_call,
						Parameter(
							RegisterType::Null,
							Symbol_Tables->FindExternedFunction(((IdentifierExpression*)Function)->Name )
						),
						Parameter(
							RegisterType::Null,
							Parameters->size()
						)
					)
				);
				instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::AX,0)));
				
			}
		}
		~FunctionCallExpression() override {
			// THEY ARE MESED UP, review tomorrow, (hopefully)
			for (std::list<Expression*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) 
				delete (*it);
			delete Parameters;
			delete Function;
		}
};
