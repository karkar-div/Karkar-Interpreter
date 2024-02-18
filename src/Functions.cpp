#include <list>

#include "Statements.cpp"



class Function{
	public:
		std::list<Symbol*>* Parameters;
		Statement* MainStatement;
		VarType* ReturnType;
		char* Name;
		Function(char* name,VarType* return_type,Statement* stmt,std::list<Symbol*>* parameters){
			Name = name;
			ReturnType = return_type;
			MainStatement = stmt;
			Parameters = parameters;
		}
		void debug(int tabs){
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Function:%s ",Name);
			for (std::list<Symbol*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) {
				auto g = *it;
				(*it)->debug();
			}
			printf("\n");
			MainStatement->debug(tabs+1);
		}
		
		void GenerateByteCode(std::list<Instruction*>* instructions){


			// add labal 
			Symbol_Tables->Push(Parameters);
			instructions->push_back(new Instruction(InstructionType::Nop)); 
			Symbol_Tables->ConstGlobalSymbols->push_back(new ConstGlobalSymbol(new Symbol(Name,new IntType),instructions->size()-1)) ;

			/* set up the stack*/
			instructions->push_back(new Instruction(InstructionType::Push,Parameter(RegisterType::BP,0,false))); // Pushing the old Base Pointer so we dont lose it
			instructions->push_back(new Instruction(InstructionType::Mov ,Parameter(RegisterType::BP,0,false),Parameter(RegisterType::SP,0,false))); // setuping the base pointer to a new stack frame
			Instruction* StackAllocter = new Instruction(InstructionType::Sub,Parameter(RegisterType::SP,0,false),Parameter(RegisterType::Null,0,false));
			instructions->push_back(StackAllocter);// add stack pre-allocation
		

			/* main code */
			MainStatement->GenerateByteCode(instructions);  
			// we don't need these symbols any more because the code is generated.
			Symbol_Tables->Pop();
			// updating the max size for the stack       
			StackAllocter->Parameters[SECOND].Offset = Symbol_Tables->MaxSize;

			/* leave Instruction hand implemented */
			instructions->push_back(new Instruction(InstructionType::Mov,Parameter(RegisterType::SP,0,false),Parameter(RegisterType::BP,0,false))); // Restore the stack pointer to the orignal position
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BP,0,false))); // Restore the orignal Base Pointer, 
		

			// do to the pop command subtracting the stack pointer. now it points to the return address

			/* ret Instruction hand implemented */
			instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BX,0,false))); // restore the return address to a general regester so to jump to
			instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::BX,0,false))); // jump to the return address setuped by the caller
			// jmp to R AKA Executions start from the regester regester is

			Symbol_Tables->ResetSize();
		}
};