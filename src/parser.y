%{

#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string>
#include <list>
#include <vector>

#include "src/Libraries.cpp"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yy_scan_string ( const char *yy_str  );
extern int Tab_Num;

void yyerror(const char* s);

#define CAPACITY 100




Function* Temperory_Function_Pointer ;


Library* lib;

class ScopeStack{
	public:
		int Top = -1;
		std::vector<Statement*> Elements;
		ScopeStack(){
			Elements = std::vector<Statement*>(CAPACITY);
		}
		void Push(Statement* statement,int index){
			int collapse_num = Top-index + 1;
			for(int i = 0; i < collapse_num;i++){
				collapse();
			}
			Elements[index] = statement;
			Top = index;
		}
		void flat(int index){
			int collapse_num = Top-index + 1;
			for(int i = 0; i < collapse_num;i++){
				collapse();
			}
		}
		void collapse() {
			Statement* child = Elements[Top];
			Top--;
			((CompoundStatement*)Elements[Top])->Statements->push_back(child);
		}
};

ScopeStack* Scopes;

%}



%token LINE_END
%token TWO_DOTS
%token ROUND_BRACKET_START
%token ROUND_BRACKET_END
%token SQWAR_BRACKET_START
%token SQWAR_BRACKET_END
%token COMA
%token AMPERSAND
%token THICK_ARROW

%token FUNCTION
%token RETURN 
%token IF
%token WHILE
%token VAR
%token ELSE
%token INT

%token NUM
%token IDENTIFIER
%token STRING

%token PLUS
%token SUB
%token DIV
%token STAR
%token MODULO 

%token IS_EQUAL
%token ISNT_EQUAL
%token IS_GREATER
%token IS_SMALLER

%token LOGIC_AND
%token LOGIC_OR
%token LOGIC_NOT

%token EQUAL

%token BIT_OR
%token BIT_XOR
%token BIT_NOT

%left  COMA
%right EQUAL
%left  LOGIC_OR
%left  LOGIC_AND
%left  BIT_OR
%left  BIT_XOR
%left  AMPERSAND
%left  IS_EQUAL ISNT_EQUAL
%left  IS_GREATER IS_SMALLER
%left  PLUS SUB
%left  STAR DIV MODULO
%left  POINTER_STUFF
%right BIT_NOT LOGIC_NOT PL
%left  SQWAR_BRACKET_START ROUND_BRACKET_START DOT ARROW

%union {
	int   Integer;
	char* String;

	class Function*   Func_Pointer;
	class Statement*  Stmt_Pointer;
	class VarType*    Type_Pointer;
	class Expression* Expr_Pointer;
	class Symbol*     Smbl_Pointer;

	class std::list<Function*>*   Func_Pointer_list;
	class std::list<Statement*>*  Stmt_Pointer_List;
	class std::list<Expression*>* Expr_Pointer_List;
	class std::list<Symbol*>*     Smbl_Pointer_List;
}

%type <Expr_Pointer_List> ExpressionsOption Expressions
%type <Integer> NUM
%type <String> STRING IDENTIFIER
%type <Func_Pointer> Function
%type <Func_Pointer_list> Functions
%type <Stmt_Pointer> Statement
%type <Type_Pointer> Type ReturnTypeOptional
%type <Expr_Pointer> Expression
%type <Smbl_Pointer> Parameter
%type <Smbl_Pointer_List> Parameters ParametersOptional
%start File

%%


File: Functions {
	lib->Functions = $1 ;

}
;

Functions: Function Functions { $2->push_front($1); $$ = $2; }
|		   %empty { $$ = new std::list<Function*> ; }
;

Function: FUNCTION IDENTIFIER ROUND_BRACKET_START ParametersOptional ROUND_BRACKET_END ReturnTypeOptional TWO_DOTS {
	
	Temperory_Function_Pointer = new Function($2,$6,new CompoundStatement(new std::list<Statement*>),$4);
	Scopes->Push(Temperory_Function_Pointer->MainStatement,0);
}StatementsOpional {
	/*the last statement doesn't get collabs*/
	$$ = Temperory_Function_Pointer; 
	Scopes->flat(1);
	delete Scopes;
	Scopes = new ScopeStack();
}
;

ParametersOptional: Parameters { $$ = $1; }
|                   %empty { $$ = new std::list<Symbol*>; }
;

Parameters: Parameters COMA Parameter { $1->push_back($3); $$ = $1; }
|			Parameter { $$ = new std::list<Symbol*>; $$->push_back($1); }
;

Parameter: Type IDENTIFIER { $$ = new Symbol($2,$1);}
;

ReturnTypeOptional: THICK_ARROW Type { $$ = $2 ; }
|                   %empty           { $$ = new VarType();}
;

Type: INT                                                              { $$ = new IntType(); }
|     IDENTIFIER                                                       { $$ = new VarType(); }
|     Type SQWAR_BRACKET_START Expression SQWAR_BRACKET_END            { $$ = new VarType(); }
|     Type IS_SMALLER Type IS_GREATER /* angle brackets */             { $$ = new VarType(); }
|     Type STAR                                                        { $$ = new VarType(); }
|     Type STAR SQWAR_BRACKET_START Expression SQWAR_BRACKET_END       { $$ = new VarType(); }
;


StatementsOpional: Statement StatementsOpional
|		           %empty
;

Statement: LINE_END                      { Scopes->Push(new EmptyStatement(),Tab_Num); }
|		   RETURN Expression LINE_END    { Scopes->Push(new ReturnStatement($2),Tab_Num); }
|		   IF Expression TWO_DOTS        { Scopes->Push(new IfStatement(new std::list<Statement*>,$2),Tab_Num); }
|		   WHILE Expression TWO_DOTS     { Scopes->Push(new WhileStatement(new std::list<Statement*>,$2),Tab_Num); }
|          VAR Type IDENTIFIER LINE_END  { Scopes->Push(new VarDefineStatement($2,$3),Tab_Num); } // TODO
|		   Expression LINE_END           { Scopes->Push(new ExpressionBasedStatement($1),Tab_Num); }
;

Expression: NUM                              { $$ = new NumberExpression( $1 ); }
|			STRING                           { $$ = new StringExpression( $1 ); }
|			IDENTIFIER                       { $$ = new IdentifierExpression(  $1 );}
|           Expression PLUS   Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Addition);}
|			Expression SUB    Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Subtraction);}
|			Expression DIV    Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Divition);}
|			Expression STAR   Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Multipication);}
|			Expression MODULO Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Remanider);}
|			Expression EQUAL  Expression     { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Moving);}
|			Expression IS_EQUAL   Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Comparation);}
|           Expression ISNT_EQUAL Expression { $$ = new BinaryExpression( new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Comparation) , $$ = new NumberExpression( 0 ) ,BinaryExpression::Type::Comparation);}
|			Expression IS_GREATER Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BiggerThanComparation);}
|			Expression IS_SMALLER Expression { $$ = new BinaryExpression( $3 , $1 ,BinaryExpression::Type::BiggerThanComparation);}
|           Expression DOT   Expression      { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::MemberAccess);}
|           Expression ARROW Expression      { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::PointerMemberAccess);}
|			Expression LOGIC_AND Expression  { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeAnd);}
|			Expression LOGIC_OR  Expression  { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeOr);}
|			Expression AMPERSAND Expression  { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeAnd);}
|			Expression BIT_OR    Expression  { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeOr);}
|			Expression BIT_XOR   Expression  { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeXor);}
|			BIT_NOT    Expression            { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::BitwizeNot);}
|           STAR       Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Derefrence);}
|           AMPERSAND  Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Refrence);}
|			LOGIC_NOT  Expression            { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::LogicalNot);}
|			SUB        Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Negativity);}
|			Expression ROUND_BRACKET_START ExpressionsOption ROUND_BRACKET_END { $$ = new FunctionCallExpression($1,$3);}
|			Expression SQWAR_BRACKET_START Expression SQWAR_BRACKET_END        { $$ = new ArrayAccessExpression($1,$3);}
|           ROUND_BRACKET_START Expression ROUND_BRACKET_END                   { $$ = $2 ;}
;

Expressions: Expression COMA Expressions { $3->push_front($1); $$ = $3;}
|			 Expression                  { $$ = new std::list<Expression*>; $$->push_front($1); }
;

ExpressionsOption: Expressions { $$ = $1 ;}
|                  %empty      { $$ = new std::list<Expression*>;}
;
%%


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#include "src/VertualMachine.cpp"

int main(int argc,char* argv[]) {
	const char *inputFileName = argv[1];

	// Open the input file for reading
	FILE *inputFile = fopen(inputFileName, "rb");
	if (inputFile == NULL) {
		perror("Error opening input file");
		return 1;
	}

	// Determine the size of the input file
	fseek(inputFile, 0, SEEK_END);
	long fileSize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	// Allocate a buffer to hold the file content
	char *inputBuffer = (char *)malloc(fileSize);
	if (inputBuffer == NULL) {
		perror("Error allocating memory");
		fclose(inputFile);
		return 1;
	}

	// Read the content of the input file into the buffer
	size_t bytesRead = fread(inputBuffer, 1, fileSize, inputFile);
	if (bytesRead != fileSize) {
		perror("Error reading file");
		free(inputBuffer);
		fclose(inputFile);
		return 1;
	}

	// Close the input file
	fclose(inputFile);

	// Open the character set conversion descriptor
	iconv_t cd = iconv_open("UTF-8", "UTF-16LE");
	if (cd == (iconv_t)-1) {
		perror("Error opening converter");
		free(inputBuffer);
		return 1;
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
		return 1;
	}

	// Print the converted content to the console
	printf("File Content:\n%s\n", outputBuffer);

	// prepere lib mem
	lib = new Library();

	// prepare the scope stack
	Scopes = new ScopeStack();

	// prepare the symblo table
	Symbol_Tables = new SymbolTableStack();

	// lex
	yy_scan_string(outputBuffer+3);

	// parce
	yyparse();

	// generate the bytecode
	lib->debug(0);
	lib->GenerateByteCode(true);

	int index = 0;
    std::list<Instruction*>* instructions_list = lib->Instructions;
    std::vector<Instruction*>* instructions_vector = new std::vector<Instruction*>(CAPACITY);
	for (std::list<Instruction*>::iterator it = instructions_list->begin(); it != instructions_list->end(); ++it) {
		Instruction* g = *it;
		(*instructions_vector)[index] = g;
		index ++;

	}
	
	Run(instructions_vector,53,index,0x500,false);
	printf("finished\n");

	// Close the character set conversion descriptor
	iconv_close(cd);

	// Free allocated memory
	free(inputBuffer);
	free(outputBuffer);

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: [%s]\n", s);
	exit(1);
}