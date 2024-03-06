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
			for (std::list<Symbol*>::iterator it = Parameters->begin(); it != Parameters->end(); ++it) 
				(*it)->debug();
			printf("\n");
			MainStatement->debug(tabs+1);
		}
		
		void GenerateByteCode(std::list<Instruction*>* instructions){


			// add labal 
			Symbol_Tables->Push(Parameters);
			instructions->push_back(new Instruction(InstructionType::Nop)); 
			Symbol_Tables->Definitions->push_back(new Definition(Name,instructions->size()-1)) ;

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
			
			/*
			 * if main was found, a special exit code is added
			 * strcmp return 0 os success and 1 on faliure
			 */
			if(strcmp("main",Name) == 0)
				instructions->push_back(new Instruction(InstructionType::Exit)); // Restore the stack pointer to the orignal position
			else{
				/* leave Instruction hand implemented */
				// the leave instruction meant to collapse the stack by moving bp to sp
				// it also pop the stack top aka old bp into bp
				instructions->push_back(new Instruction(InstructionType::Mov,Parameter(RegisterType::SP,0,false),Parameter(RegisterType::BP,0,false)));
				instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BP,0,false))); 
			
				/* ret Instruction hand implemented */
				// a ret instruction jump to the address stored at he top of the stack,
				// this address is pushed by the caller 
				instructions->push_back(new Instruction(InstructionType::Pop,Parameter(RegisterType::BX,0,false))); 
				instructions->push_back(new Instruction(InstructionType::Jmp,Parameter(RegisterType::BX,0,false))); 
			}
			Symbol_Tables->ResetSize();
		}
		~Function(){
			// deleting parameters cases segmentation faults because it is duoble freed in Symbol_Tables
			// please don't refactor
			delete MainStatement;
			delete ReturnType;
			free(Name);
		}
};
