%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <list>

#define YY_DECL int yylex()

#include "parser.tab.hpp"

int Tab_Num = 0;
int Line_Index = 1;

%}

%%

\t           {Tab_Num++;}
\n           {Tab_Num = 0; Line_Index++;}

";"          {return LINE_END;}
":"          {return TWO_DOTS;}
"("          {return ROUND_BRACKET_START;}
")"          {return ROUND_BRACKET_END;}
"["          {return SQWAR_BRACKET_START;}
"]"          {return SQWAR_BRACKET_END;}
","          {return COMA;}
"."          {return DOT;}
"->"         {return ARROW;}
"=>"         {return THICK_ARROW;}

"+"          {return PLUS;}
"-"          {return SUB;}
"\\"         {return DIV;}
"*"          {return STAR;}
"%"          {return MODULO;}

"=="         {return IS_EQUAL;}
"!="         {return ISNT_EQUAL;}
">"          {return IS_GREATER;}
"<"          {return IS_SMALLER;}

"و"          {return LOGIC_AND;}
"او"         {return LOGIC_OR;}
"ليس"        {return LOGIC_NOT;}
"and"        {return LOGIC_AND;}
"or"         {return LOGIC_OR;}
"not"        {return LOGIC_NOT;}

"="          {return EQUAL;}

"&"          {return AMPERSAND;}
"|"          {return BIT_OR;}
"^"          {return BIT_XOR;}
"~"          {return BIT_NOT;}


"function"   {return FUNCTION;} 
"return"     {return RETURN;} 
"if"         {return IF;}
"while"      {return WHILE;}
"else"       {return ELSE;}
"var"        {return VAR;}
"int"        {return INT;}
"import"     {return IMPORT;} 
"from"       {return FROM;}
"as"         {return AS;} 
"الوظيفة"    {return FUNCTION;} 
"ارجع"       {return RETURN;} 
"لو"         {return IF;}
"طالما"      {return WHILE;}
"غير"        {return ELSE;}
"عرف"        {return VAR;}
"الرقم"      {return INT;}
"استورد"     {return IMPORT;} 
"من"         {return FROM;}
"ك"          {return AS;} 

"الرئيسية"                                {yylval.String  = strdup("main");return IDENTIFIER;}
[0-9]+                                    {yylval.Integer = atoi(yytext);  return NUM;}
[ء-ي]+                                    {yylval.String  = strdup(yytext);return IDENTIFIER;} 
[ضصثقفغعهخحجدشسيبلاتنمكطئءؤرﻻىةوزظﻹإﻷأﻵآ_]+ {yylval.String  = strdup(yytext);return IDENTIFIER;}
[a-zA-Z_]+                                {yylval.String  = strdup(yytext);return IDENTIFIER;}
\"[^\"]*\"  {
    char* str = strdup(yytext);
    str++;
    str[strlen(str) - 1] = '\0';
    yylval.String = str;
    return STRING;
}
\'.\' {
    char* str = strdup(yytext);
    yylval.Integer = str[1];
    return NUM;
}


.           {}
#.+         {}

%%
