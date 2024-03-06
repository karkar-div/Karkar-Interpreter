

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
%token IMPORT 
%token FROM 
%token AS 
%token INT 
%token CHAR

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
%type <Func_Pointer_list> FunctionsOpional
%type <Stmt_Pointer> Statement
%type <Type_Pointer> Type ReturnTypeOptional
%type <Expr_Pointer> Expression
%type <Smbl_Pointer> Parameter
%type <Smbl_Pointer_List> Parameters ParametersOptional
%start File

%%


File: FunctionsOpional {
	lib->Functions = $1 ;
}
;

FunctionsOpional: Function FunctionsOpional                                     { $2->push_front($1); $$ = $2; }
|		 		  IMPORT STRING FROM STRING AS STRING LINE_END FunctionsOpional {
	Global_Dependencies->push_back(new Dependency($4,$2));
	Symbol_Tables->DependencySymbols->push_back(new DependencySymbol(Global_Dependencies->size()-1,$6));
	free($4-1);
	free($2-1);
	free($6-1);
	$$ = $8;
}
|		          %empty                                                        { $$ = new std::list<Function*> ; }
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

Parameter: Type IDENTIFIER { $$ = new Symbol($2,$1);free($1);delete $2;}
;

ReturnTypeOptional: THICK_ARROW Type { $$ = $2 ; }
|                   %empty           { $$ = new VarType();}
;

Type: INT                                                              { $$ = new IntType(); }
|	  CHAR 															   { $$ = new CharType(); }
|     IDENTIFIER                                                       { $$ = new VarType(); }
|     Type SQWAR_BRACKET_START Expression SQWAR_BRACKET_END            { $$ = new VarType(); }
|     Type IS_SMALLER Type IS_GREATER /* angle brackets */             { $$ = new VarType(); }
|     Type STAR                                                        { $$ = new VarType(); }
|     Type STAR SQWAR_BRACKET_START Expression SQWAR_BRACKET_END       { $$ = new VarType(); }
;


StatementsOpional: Statement StatementsOpional
|		           %empty
;



Statement: LINE_END                                { Scopes->Push(new EmptyStatement(),Tab_Num); }
|		   RETURN Expression LINE_END              { Scopes->Push(new ReturnStatement($2),Tab_Num); }
|		   IF Expression TWO_DOTS                  { Scopes->Push(new IfStatement(new std::list<Statement*>,$2),Tab_Num); }
|		   WHILE Expression TWO_DOTS               { Scopes->Push(new WhileStatement(new std::list<Statement*>,$2),Tab_Num); }
|          VAR DeclearationsOpional LINE_END       {  }
|		   Expression LINE_END                     { Scopes->Push(new ExpressionBasedStatement($1),Tab_Num); }
;



DeclearationsOpional: Declearations
|				      %empty 
;

Declearations : Type IDENTIFIER                  { Scopes->Push(new VarDefineStatement($1,$2),Tab_Num); }
|				Type IDENTIFIER EQUAL Expression {
	Scopes->Push(new VarDefineStatement($1,$2),Tab_Num);
	Scopes->Push(
		new ExpressionBasedStatement(
			new BinaryExpression(
				new IdentifierExpression(strdup($2)),
				$4,
				BinaryExpression::Type::Moving)
			),
		Tab_Num
	);
	
}
;

Expression: NUM                              { $$ = new NumberExpression( $1 ); }
|			STRING                           { $$ = new StringExpression( $1 ); }
|			IDENTIFIER                       { $$ = new IdentifierExpression(  $1 );}
|           Expression PLUS       Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Addition);}
|			Expression SUB        Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Subtraction);}
|			Expression DIV        Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Divition);}
|			Expression STAR       Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Multipication);}
|			Expression MODULO     Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Remanider);}
|			Expression EQUAL      Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Moving);}
|			Expression IS_EQUAL   Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::Comparation);}
|           Expression ISNT_EQUAL Expression { $$ = new BinaryExpression( new BinaryExpression($1,$3,BinaryExpression::Type::Comparation),new NumberExpression(0),BinaryExpression::Type::Comparation);}
|			Expression IS_GREATER Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BiggerThanComparation);}
|			Expression IS_SMALLER Expression { $$ = new BinaryExpression( $3 , $1 ,BinaryExpression::Type::BiggerThanComparation);}
|           Expression DOT        Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::MemberAccess);}
|           Expression ARROW      Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::PointerMemberAccess);}
|			Expression LOGIC_AND  Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeAnd);}
|			Expression LOGIC_OR   Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeOr);}
|			Expression AMPERSAND  Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeAnd);}
|			Expression BIT_OR     Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeOr);}
|			Expression BIT_XOR    Expression { $$ = new BinaryExpression( $1 , $3 ,BinaryExpression::Type::BitwizeXor);}
|			BIT_NOT    Expression            { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::BitwizeNot);}
|           STAR       Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Derefrence);}
|           AMPERSAND  Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Refrence);}
|			LOGIC_NOT  Expression            { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::LogicalNot);}
|			SUB        Expression %prec PL   { $$ = new UnaryExpression ( $2 , UnaryExpression::Type::Negativity);}
|			Expression ROUND_BRACKET_START ExpressionsOption ROUND_BRACKET_END           { $$ = new FunctionCallExpression($1,$3);}
|			Expression SQWAR_BRACKET_START Expression SQWAR_BRACKET_END                  { $$ = new ArrayAccessExpression($1,$3);}
|           ROUND_BRACKET_START Expression ROUND_BRACKET_END                             { $$ = $2 ;}
;

Expressions: Expression COMA Expressions { $3->push_front($1); $$ = $3;}
|			 Expression                  { $$ = new std::list<Expression*>; $$->push_front($1); }
;

ExpressionsOption: Expressions { $$ = $1 ;}
|                  %empty      { $$ = new std::list<Expression*>;}
;
%%
