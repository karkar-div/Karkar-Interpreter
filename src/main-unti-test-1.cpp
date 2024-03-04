#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <list>
#include <vector>
#include <memory>

#include "Libraries.cpp"
#include "ScopeStack.cpp"
#include "VirtualMachine.cpp"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yy_scan_string ( const char *yy_str  );
extern int Tab_Num;
extern int Line_Index;

void yyerror(const char* s);



Function* Temperory_Function_Pointer ;


Library* lib;

#include "../parser.tab.cpp"

// TODO : this code doesn't work well
const char* detect_charset_from_buffer(const unsigned char* buffer) {

	if( buffer[0]==0xEF && buffer[1]==0xBB && buffer[2]==0xBF) return "UTF-8";
	if( buffer[0]==0xFE && buffer[1]==0xFF) return "UTF-16BE";
	if( buffer[0]==0xFF && buffer[1]==0xFE) return "UTF-16LE";
	if( buffer[0]==0x00 && buffer[1]==0x00 && buffer[2]==0xFE && buffer[3]==0xFF ) return "UTF-32BE";
	if( buffer[0]==0xFF && buffer[1]==0xFE && buffer[2]==0x00 && buffer[3]==0x00 ) return "UTF-32LE";
	return "UTF-16LE";
}

char* read_and_convert_file(const char* inputFileName){
	// Open the input file for reading
	FILE *inputFile = fopen(inputFileName, "rb");
	if (inputFile == NULL) 
		throw ("Error opening input file");

	// Determine the size of the input file
	fseek(inputFile, 0, SEEK_END);
	long fileSize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	// Allocate a buffer to hold the file content
	char *inputBuffer = (char *)malloc(fileSize);

	// Read the content of the input file into the buffer
	size_t bytesRead = fread(inputBuffer, 1, fileSize, inputFile);
	if (bytesRead != fileSize) {
		perror("Error reading file");
		free(inputBuffer);
		fclose(inputFile);
		throw ("");
	}

	// Close the input file
	fclose(inputFile);

	// Open the character set conversion descriptor
	iconv_t cd = iconv_open("UTF-8", detect_charset_from_buffer((const unsigned char*)inputBuffer));
	if (cd == (iconv_t)-1) {
		perror("Error opening converter");
		free(inputBuffer);
		throw ("");
	}

	// Perform the character set conversion
	char *outputBuffer = (char *)malloc(fileSize * 4); // Assume worst-case expansion for UTF-8
	char *inputPtr = inputBuffer;
	char *outputPtr = outputBuffer;

	size_t inputSize = bytesRead;
	size_t outputSize = fileSize * 4;

	if (iconv(cd, &inputPtr, &inputSize, &outputPtr, &outputSize) == (size_t)-1) {
		perror("Error converting character set");
		free(inputBuffer);
		free(outputBuffer);
		iconv_close(cd);
		throw ("");
	}
	iconv_close(cd);

	free(inputBuffer);

	return outputBuffer;
}

int main(int argc,char* argv[]) {
	const char* inputFileName = argv[1];
	const char* debug_option = argv[2];

	bool debug = false;
	bool verbose = false;
	
	if(argc == 1){
		printf("not enough arguments, please provide a file name .\n");
		return 1;
	}

	if(argc >= 3){
		if(!strcmp(debug_option,"debug")){
			debug = true;
		}
		if(!strcmp(debug_option,"verbose-debug")){
			debug = true;
			verbose = true;
		}
	}


	char* outputBuffer;
	try {
		outputBuffer = read_and_convert_file(inputFileName);
	} catch (const char * error_massage){
		printf("File Handling Error: %s\n",error_massage);
		return -1;
	}

	// Print the converted content to the console
	if(debug)printf("File Content:\n%s\n", outputBuffer);

	// prepere lib mem
	lib = new Library();
	Scopes = new ScopeStack();
	Symbol_Tables = new SymbolTableStack();
	Global_Dependencies = new std::list<Dependency*>;

	lib->Functions = new std::list<Function*>;
	free(outputBuffer);

	delete lib;
	delete Scopes;
	delete Symbol_Tables;
	for(std::list<Dependency*>::iterator it = Global_Dependencies->begin();it != Global_Dependencies->end();++it)
		delete (*it);
	delete Global_Dependencies;



	/* Running the code */
	if(debug)printf("Program finished execution successfully.\n");





	return 0;
}

void yyerror(const char* s) {
	throw (" ");
}