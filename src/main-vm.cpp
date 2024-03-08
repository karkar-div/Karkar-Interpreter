#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <memory>

#include "VirtualMachine.cpp"

enum RunOptions{
	Normal,
	ByteCode,
};

int main(int argc,char* argv[]) {
	const char* inputFileName = argv[1];
	const char* debug_option_str = argv[2];
	const char* running_option_str = argv[3];

	bool debug = false;
	bool verbose = false;
	enum RunOptions run_options = RunOptions::Normal;
	
	if(argc == 1){
		printf("not enough arguments, please provide a file name .\n");
		return 1;
	}

	if(argc >= 3){
		if(!strcmp(debug_option_str,"debug")){
			debug = true;
		}
		if(!strcmp(debug_option_str,"verbose-debug")){
			debug = true;
			verbose = true;
		}
	}
	if(argc >= 4){
		if(!strcmp(running_option_str,"byte-code")){
			run_options = RunOptions::ByteCode;
		}
	}
	Global_Dependencies = new std::list<Dependency*>;


    try{
        VirtualMachine* VM = new VirtualMachine(0);
        std::vector<Instruction*>* temp_instructions_vector;

        FILE* binaryFile = fopen("out.kkb", "rb");
        if (binaryFile != NULL){
            printf("Failed to open data.bin for reading\n");
            return -1;
        }
        
        while (fread(&number, sizeof(int), 1, binaryFile) == 1) {
            Instruction* instruction = new Instruction(InstructionType::Nop);
            printf("%d ", number);
        }
        printf("\n");
        fclose(binaryFile);
        

        std::vector<Dependency*>* temp_dependencies_vector = new std::vector<Dependency*>(
            Global_Dependencies->begin(),
            Global_Dependencies->end()
        );
        VM->Run(
            temp_instructions_vector,
            temp_dependencies_vector,
            debug && verbose
        );
        delete VM;
        delete temp_dependencies_vector;
        delete temp_instructions_vector;
    }
    catch(const char* error_massage){
        printf("Unexpected Run-time Error :%s",error_massage);
        return -1;
    }
	

	if(debug)printf("Program finished execution successfully.\n");
	
	for(std::list<Dependency*>::iterator it = Global_Dependencies->begin();it != Global_Dependencies->end();++it)
		delete (*it);
	delete Global_Dependencies;
	


	return 0;
}

void yyerror(const char* s) {
	throw (" ");
}