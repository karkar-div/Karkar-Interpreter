#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <memory>

#include "VirtualMachine.cpp"

int main(int argc,char* argv[]) {
	const char* inputFileName = argv[1];
	const char* info_option_str = argv[2];

	bool info = false;
	bool verbose = false;
	
	if(argc == 1){
		printf("not enough arguments, please provide a file name .\n");
		return 1;
	}

	if(argc >= 3){
		if(!strcmp(info_option_str,"info")){
			info = true;
		}
		if(!strcmp(info_option_str,"verbose-info")){
			info = true;
			verbose = true;
		}
	}
    std::vector<Instruction*>* instructions = new std::vector<Instruction*>(0);
    std::vector<Dependency*>* dependencies = new std::vector<Dependency*>;
    int entry_point = 0;

    try{
        FILE* binaryFile = fopen(inputFileName, "rb");
        if (binaryFile == NULL) 
            throw ("Failed to open %s for reading\n",inputFileName);


		fread(&entry_point, sizeof(int), 1, binaryFile);

        int instructions_count = 0;
		fread(&instructions_count, sizeof(int), 1, binaryFile);
        for(int x = 0;x < instructions_count;x++){
            Instruction instruction = Instruction(InstructionType::Nop);
            fread(&instruction, sizeof(Instruction), 1, binaryFile);
            instructions->push_back(instruction.Clone());
        }
        if(info)
            for(Instruction* it : *instructions)
                it->info();

        int dependencies_count = 0;
		fread(&dependencies_count, sizeof(int), 1, binaryFile);
        for(int x = 0;x < dependencies_count;x++){
            Dependency dependency = Dependency("","",false);
            fread(&dependency, sizeof(dependency), 1, binaryFile);
            dependency.initalize();
            dependencies->push_back(dependency.Clone());
        }
        
        if(info)
            for(Dependency* it : *dependencies)
                it->info();

        fclose(binaryFile);
    }catch(...){
        return -1;
    }


    try{
        VirtualMachine* VM = new VirtualMachine(entry_point);
        VM->Run(
            instructions,
            dependencies,
            info && verbose
        );
        delete VM;
    }catch(const char* error_massage){
        printf("Unexpected Run-time Error :%s",error_massage);
        return -1;
    }

	if(info)printf("Program finished execution successfully.\n");

	for(Dependency* it : *dependencies)
		delete it;
	delete dependencies;



	for(Instruction* it : *instructions)
		delete it;
    delete instructions;
	return 0;
}
