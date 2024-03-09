#include <list>

#include "Functions.cpp"

class Library{
	public:
		std::list<Function*>* Functions;
		std::list<Instruction*>* Instructions;
		Library(){
			Instructions = new std::list<Instruction*>;
		}
		void info(int tabs){
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("The Abstract Syntax Tree AST :");
			printf("\n");
			for (std::list<Function*>::iterator it = Functions->begin(); it != Functions->end(); ++it) 
				(*it)->info(tabs+1);
		}
		void GenerateByteCode(){
			
			for (std::list<Function*>::iterator it = Functions->begin(); it != Functions->end(); ++it)
				(*it)->GenerateByteCode(Instructions);
		}
		void info_bytecode(){
			printf("ByteCode:\n");
			int index = 0;
			for (std::list<Instruction*>::iterator it = Instructions->begin(); it != Instructions->end(); ++it) {
				printf("    %03d: ",index);
				(*it)->info();
				index++;
			}
		}
		~Library(){
			for (std::list<Function*>::iterator it = Functions->begin(); it != Functions->end(); ++it)
				delete (*it);
			delete Functions;
			for (std::list<Instruction*>::iterator it = Instructions->begin(); it != Instructions->end(); ++it) 
				delete (*it);
			delete Instructions;
		}
};
