/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LINE_END = 258,                /* LINE_END  */
    TWO_DOTS = 259,                /* TWO_DOTS  */
    ROUND_BRACKET_START = 260,     /* ROUND_BRACKET_START  */
    ROUND_BRACKET_END = 261,       /* ROUND_BRACKET_END  */
    SQWAR_BRACKET_START = 262,     /* SQWAR_BRACKET_START  */
    SQWAR_BRACKET_END = 263,       /* SQWAR_BRACKET_END  */
    COMA = 264,                    /* COMA  */
    AMPERSAND = 265,               /* AMPERSAND  */
    THICK_ARROW = 266,             /* THICK_ARROW  */
    FUNCTION = 267,                /* FUNCTION  */
    RETURN = 268,                  /* RETURN  */
    IF = 269,                      /* IF  */
    WHILE = 270,                   /* WHILE  */
    VAR = 271,                     /* VAR  */
    ELSE = 272,                    /* ELSE  */
    INT = 273,                     /* INT  */
    NUM = 274,                     /* NUM  */
    IDENTIFIER = 275,              /* IDENTIFIER  */
    STRING = 276,                  /* STRING  */
    PLUS = 277,                    /* PLUS  */
    SUB = 278,                     /* SUB  */
    DIV = 279,                     /* DIV  */
    STAR = 280,                    /* STAR  */
    MODULO = 281,                  /* MODULO  */
    IS_EQUAL = 282,                /* IS_EQUAL  */
    ISNT_EQUAL = 283,              /* ISNT_EQUAL  */
    IS_GREATER = 284,              /* IS_GREATER  */
    IS_SMALLER = 285,              /* IS_SMALLER  */
    LOGIC_AND = 286,               /* LOGIC_AND  */
    LOGIC_OR = 287,                /* LOGIC_OR  */
    LOGIC_NOT = 288,               /* LOGIC_NOT  */
    EQUAL = 289,                   /* EQUAL  */
    BIT_OR = 290,                  /* BIT_OR  */
    BIT_XOR = 291,                 /* BIT_XOR  */
    BIT_NOT = 292,                 /* BIT_NOT  */
    POINTER_STUFF = 293,           /* POINTER_STUFF  */
    PL = 294,                      /* PL  */
    DOT = 295,                     /* DOT  */
    ARROW = 296                    /* ARROW  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 122 "src/parser.y"

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

#line 121 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
