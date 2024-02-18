#include <list>

#include "Functions.cpp"

class Library{
	public:
		std::list<Function*>* Functions;
		std::list<Instruction*>* Instructions;
		void debug(int tabs){
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("The Abstract Syntax Tree AST :");
			printf("\n");
			for (std::list<Function*>::iterator it = Functions->begin(); it != Functions->end(); ++it) {
				auto g = *it;
				g->debug(tabs+1);
			}
		}
		void GenerateByteCode(bool show = false){
			Instructions = new std::list<Instruction*> ;
			for (std::list<Function*>::iterator it = Functions->begin(); it != Functions->end(); ++it) {
				auto g = *it;
				g->GenerateByteCode(Instructions);
			}
			if(show){
				printf("ByteCode:\n");
				int index = 0;
				for (std::list<Instruction*>::iterator it = Instructions->begin(); it != Instructions->end(); ++it) {
					auto g = *it;
					printf("    %03d: ",index);
					g->debug();
					index++;
				}
			}
		}
};
