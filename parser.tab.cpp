/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"


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


#line 132 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LINE_END = 3,                   /* LINE_END  */
  YYSYMBOL_TWO_DOTS = 4,                   /* TWO_DOTS  */
  YYSYMBOL_ROUND_BRACKET_START = 5,        /* ROUND_BRACKET_START  */
  YYSYMBOL_ROUND_BRACKET_END = 6,          /* ROUND_BRACKET_END  */
  YYSYMBOL_SQWAR_BRACKET_START = 7,        /* SQWAR_BRACKET_START  */
  YYSYMBOL_SQWAR_BRACKET_END = 8,          /* SQWAR_BRACKET_END  */
  YYSYMBOL_COMA = 9,                       /* COMA  */
  YYSYMBOL_AMPERSAND = 10,                 /* AMPERSAND  */
  YYSYMBOL_THICK_ARROW = 11,               /* THICK_ARROW  */
  YYSYMBOL_FUNCTION = 12,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_VAR = 16,                       /* VAR  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_INT = 18,                       /* INT  */
  YYSYMBOL_NUM = 19,                       /* NUM  */
  YYSYMBOL_IDENTIFIER = 20,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 21,                    /* STRING  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_SUB = 23,                       /* SUB  */
  YYSYMBOL_DIV = 24,                       /* DIV  */
  YYSYMBOL_STAR = 25,                      /* STAR  */
  YYSYMBOL_MODULO = 26,                    /* MODULO  */
  YYSYMBOL_IS_EQUAL = 27,                  /* IS_EQUAL  */
  YYSYMBOL_ISNT_EQUAL = 28,                /* ISNT_EQUAL  */
  YYSYMBOL_IS_GREATER = 29,                /* IS_GREATER  */
  YYSYMBOL_IS_SMALLER = 30,                /* IS_SMALLER  */
  YYSYMBOL_LOGIC_AND = 31,                 /* LOGIC_AND  */
  YYSYMBOL_LOGIC_OR = 32,                  /* LOGIC_OR  */
  YYSYMBOL_LOGIC_NOT = 33,                 /* LOGIC_NOT  */
  YYSYMBOL_EQUAL = 34,                     /* EQUAL  */
  YYSYMBOL_BIT_OR = 35,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 36,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 37,                   /* BIT_NOT  */
  YYSYMBOL_POINTER_STUFF = 38,             /* POINTER_STUFF  */
  YYSYMBOL_PL = 39,                        /* PL  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_ARROW = 41,                     /* ARROW  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_File = 43,                      /* File  */
  YYSYMBOL_Functions = 44,                 /* Functions  */
  YYSYMBOL_Function = 45,                  /* Function  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_ParametersOptional = 47,        /* ParametersOptional  */
  YYSYMBOL_Parameters = 48,                /* Parameters  */
  YYSYMBOL_Parameter = 49,                 /* Parameter  */
  YYSYMBOL_ReturnTypeOptional = 50,        /* ReturnTypeOptional  */
  YYSYMBOL_Type = 51,                      /* Type  */
  YYSYMBOL_StatementsOpional = 52,         /* StatementsOpional  */
  YYSYMBOL_Statement = 53,                 /* Statement  */
  YYSYMBOL_Expression = 54,                /* Expression  */
  YYSYMBOL_Expressions = 55,               /* Expressions  */
  YYSYMBOL_ExpressionsOption = 56          /* ExpressionsOption  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   635

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   153,   153,   159,   160,   163,   163,   176,   177,   180,
     181,   184,   187,   188,   191,   192,   193,   194,   195,   196,
     200,   201,   204,   205,   206,   207,   208,   209,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   242,   243,   246,   247
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LINE_END", "TWO_DOTS",
  "ROUND_BRACKET_START", "ROUND_BRACKET_END", "SQWAR_BRACKET_START",
  "SQWAR_BRACKET_END", "COMA", "AMPERSAND", "THICK_ARROW", "FUNCTION",
  "RETURN", "IF", "WHILE", "VAR", "ELSE", "INT", "NUM", "IDENTIFIER",
  "STRING", "PLUS", "SUB", "DIV", "STAR", "MODULO", "IS_EQUAL",
  "ISNT_EQUAL", "IS_GREATER", "IS_SMALLER", "LOGIC_AND", "LOGIC_OR",
  "LOGIC_NOT", "EQUAL", "BIT_OR", "BIT_XOR", "BIT_NOT", "POINTER_STUFF",
  "PL", "DOT", "ARROW", "$accept", "File", "Functions", "Function", "$@1",
  "ParametersOptional", "Parameters", "Parameter", "ReturnTypeOptional",
  "Type", "StatementsOpional", "Statement", "Expression", "Expressions",
  "ExpressionsOption", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -11,   -18,    10,   -40,   -11,    15,   -40,   -40,    -9,   -40,
     -40,    16,    14,   -40,    -1,    36,    -9,   598,   -40,    20,
      -9,    -9,    46,   -40,   598,   598,   -40,   -40,   -40,   598,
     598,   598,   598,   210,   598,    -4,    41,   -40,   242,    11,
      11,    11,    11,    11,   598,   598,   -40,   598,   598,   598,
     598,   598,   598,   598,   598,   598,   598,   598,   598,   598,
     598,   598,   598,   598,   279,   -40,   579,   -40,   316,   -40,
      49,   353,   524,   110,   110,    11,    11,    11,   537,   537,
     550,   550,   444,   417,   385,   471,   498,   -40,   -40,   -40,
     -40,   598,   598,   598,    -9,   -40,   579,    58,   598,   -40,
     -40,    97,   135,   173,    47,   -40,   -40,   -40,   -40,   -40,
     -40,    50,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     1,     3,     8,    14,
      15,     0,     7,    10,     0,    13,     0,     0,    11,    18,
       0,     0,     0,     9,     0,     0,    28,    30,    29,     0,
       0,     0,     0,     0,     0,     0,    12,     5,     0,    50,
      52,    49,    51,    48,    59,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    21,    55,    57,    58,
       0,     0,    45,    31,    32,    33,    34,    35,    37,    38,
      39,    40,    43,    44,    36,    46,    47,    41,    42,    19,
      22,     0,     0,     0,     0,     6,    21,     0,     0,    53,
      54,     0,     0,     0,     0,    20,    27,    56,    23,    24,
      25,     0,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,    52,   -40,   -40,   -40,   -40,    42,   -40,   -16,
     -39,   -40,   -17,   -38,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    66,    11,    12,    13,    22,    14,
      95,    96,    68,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      33,     1,     5,    17,    35,    36,    17,    38,    39,     9,
       6,    10,    40,    41,    42,    43,    44,    64,    45,    18,
       8,    19,    15,    16,    19,    65,    20,    34,    71,    20,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    21,    17,    97,
      37,    62,    63,   112,    17,    99,     7,   105,    23,     0,
     107,   106,     0,    44,     0,    45,    19,   111,    47,     0,
       0,    20,    19,     0,   101,   102,   103,    20,   104,    97,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     0,    59,    60,    61,     0,     0,     0,    62,    63,
     108,     0,    44,     0,    45,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,    44,     0,    45,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       0,    59,    60,    61,    50,    51,    52,    62,    63,   109,
      44,     0,    45,     0,     0,    47,     0,     0,     0,     0,
      62,    63,     0,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,    59,
      60,    61,     0,     0,     0,    62,    63,   110,    44,     0,
      45,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,     0,    59,    60,    61,
       0,     0,     0,    62,    63,    44,     0,    45,    46,     0,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,    59,    60,    61,    44,    67,    45,
      62,    63,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,    59,    60,    61,     0,
       0,     0,    62,    63,    44,     0,    45,    89,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,    59,    60,    61,     0,     0,     0,    62,
      63,    44,     0,    45,     0,    98,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     0,
      59,    60,    61,     0,     0,     0,    62,    63,    44,     0,
      45,   100,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,     0,    59,    60,    61,
      44,     0,    45,    62,    63,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,    59,
      60,    61,    44,     0,    45,    62,    63,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    44,
       0,    45,    60,    61,    47,     0,     0,    62,    63,     0,
       0,     0,     0,     0,     0,     0,    48,    49,    50,    51,
      52,    53,    54,    55,    56,     0,    44,     0,    45,    60,
      61,    47,     0,     0,    62,    63,     0,     0,     0,     0,
       0,     0,     0,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     0,    44,     0,    45,     0,    61,    47,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,     0,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    44,
       0,    45,     0,     0,     0,     0,     0,     0,    62,    63,
       0,     0,    44,     0,    45,     0,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    44,     0,    45,     0,    48,
      49,    50,    51,    52,    62,    63,    55,    56,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    62,    63,     0,
       0,     0,    90,     0,    24,     0,     0,     0,     0,    25,
      62,    63,    91,    92,    93,    94,     0,     0,    26,    27,
      28,     0,    29,    24,    30,     0,     0,     0,    25,     0,
       0,     0,    31,     0,     0,     0,    32,    26,    27,    28,
       0,    29,     0,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,    32
};

static const yytype_int8 yycheck[] =
{
      17,    12,    20,     7,    20,    21,     7,    24,    25,    18,
       0,    20,    29,    30,    31,    32,     5,    34,     7,    20,
       5,    25,     6,     9,    25,    29,    30,     7,    45,    30,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    11,     7,    66,
       4,    40,    41,     3,     7,     6,     4,    96,    16,    -1,
      98,     3,    -1,     5,    -1,     7,    25,    20,    10,    -1,
      -1,    30,    25,    -1,    91,    92,    93,    30,    94,    96,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    -1,    -1,    -1,    40,    41,
       3,    -1,     5,    -1,     7,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,     7,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    24,    25,    26,    40,    41,     4,
       5,    -1,     7,    -1,    -1,    10,    -1,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    -1,    -1,    -1,    40,    41,     4,     5,    -1,
       7,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      -1,    -1,    -1,    40,    41,     5,    -1,     7,     8,    -1,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,     5,     6,     7,
      40,    41,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      -1,    -1,    40,    41,     5,    -1,     7,     8,    -1,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    -1,    -1,    40,
      41,     5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    -1,    -1,    40,    41,     5,    -1,
       7,     8,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
       5,    -1,     7,    40,    41,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,     5,    -1,     7,    40,    41,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     5,
      -1,     7,    35,    36,    10,    -1,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,     5,    -1,     7,    35,
      36,    10,    -1,    -1,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,     5,    -1,     7,    -1,    36,    10,    -1,
      -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     5,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,    -1,     5,    -1,     7,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     5,    -1,     7,    -1,    22,
      23,    24,    25,    26,    40,    41,    29,    30,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    40,    41,    -1,
      -1,    -1,     3,    -1,     5,    -1,    -1,    -1,    -1,    10,
      40,    41,    13,    14,    15,    16,    -1,    -1,    19,    20,
      21,    -1,    23,     5,    25,    -1,    -1,    -1,    10,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    37,    19,    20,    21,
      -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    43,    44,    45,    20,     0,    44,     5,    18,
      20,    47,    48,    49,    51,     6,     9,     7,    20,    25,
      30,    11,    50,    49,     5,    10,    19,    20,    21,    23,
      25,    33,    37,    54,     7,    51,    51,     4,    54,    54,
      54,    54,    54,    54,     5,     7,     8,    10,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    34,
      35,    36,    40,    41,    54,    29,    46,     6,    54,    55,
      56,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,     8,
       3,    13,    14,    15,    16,    52,    53,    54,     9,     6,
       8,    54,    54,    54,    51,    52,     3,    55,     3,     4,
       4,    20,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    46,    45,    47,    47,    48,
      48,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     0,     9,     1,     0,     3,
       1,     2,     2,     0,     1,     1,     4,     4,     2,     5,
       2,     0,     1,     3,     3,     3,     4,     2,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     4,     4,     3,     3,     1,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* File: Functions  */
#line 153 "src/parser.y"
                {
	lib->Functions = (yyvsp[0].Func_Pointer_list) ;

}
#line 1353 "parser.tab.cpp"
    break;

  case 3: /* Functions: Function Functions  */
#line 159 "src/parser.y"
                              { (yyvsp[0].Func_Pointer_list)->push_front((yyvsp[-1].Func_Pointer)); (yyval.Func_Pointer_list) = (yyvsp[0].Func_Pointer_list); }
#line 1359 "parser.tab.cpp"
    break;

  case 4: /* Functions: %empty  */
#line 160 "src/parser.y"
                          { (yyval.Func_Pointer_list) = new std::list<Function*> ; }
#line 1365 "parser.tab.cpp"
    break;

  case 5: /* $@1: %empty  */
#line 163 "src/parser.y"
                                                                                                                   {
	
	Temperory_Function_Pointer = new Function((yyvsp[-5].String),(yyvsp[-1].Type_Pointer),new CompoundStatement(new std::list<Statement*>),(yyvsp[-3].Smbl_Pointer_List));
	Scopes->Push(Temperory_Function_Pointer->MainStatement,0);
}
#line 1375 "parser.tab.cpp"
    break;

  case 6: /* Function: FUNCTION IDENTIFIER ROUND_BRACKET_START ParametersOptional ROUND_BRACKET_END ReturnTypeOptional TWO_DOTS $@1 StatementsOpional  */
#line 167 "src/parser.y"
                   {
	/*the last statement doesn't get collabs*/
	(yyval.Func_Pointer) = Temperory_Function_Pointer; 
	Scopes->flat(1);
	delete Scopes;
	Scopes = new ScopeStack();
}
#line 1387 "parser.tab.cpp"
    break;

  case 7: /* ParametersOptional: Parameters  */
#line 176 "src/parser.y"
                               { (yyval.Smbl_Pointer_List) = (yyvsp[0].Smbl_Pointer_List); }
#line 1393 "parser.tab.cpp"
    break;

  case 8: /* ParametersOptional: %empty  */
#line 177 "src/parser.y"
                           { (yyval.Smbl_Pointer_List) = new std::list<Symbol*>; }
#line 1399 "parser.tab.cpp"
    break;

  case 9: /* Parameters: Parameters COMA Parameter  */
#line 180 "src/parser.y"
                                      { (yyvsp[-2].Smbl_Pointer_List)->push_back((yyvsp[0].Smbl_Pointer)); (yyval.Smbl_Pointer_List) = (yyvsp[-2].Smbl_Pointer_List); }
#line 1405 "parser.tab.cpp"
    break;

  case 10: /* Parameters: Parameter  */
#line 181 "src/parser.y"
                                  { (yyval.Smbl_Pointer_List) = new std::list<Symbol*>; (yyval.Smbl_Pointer_List)->push_back((yyvsp[0].Smbl_Pointer)); }
#line 1411 "parser.tab.cpp"
    break;

  case 11: /* Parameter: Type IDENTIFIER  */
#line 184 "src/parser.y"
                           { (yyval.Smbl_Pointer) = new Symbol((yyvsp[0].String),(yyvsp[-1].Type_Pointer));}
#line 1417 "parser.tab.cpp"
    break;

  case 12: /* ReturnTypeOptional: THICK_ARROW Type  */
#line 187 "src/parser.y"
                                     { (yyval.Type_Pointer) = (yyvsp[0].Type_Pointer) ; }
#line 1423 "parser.tab.cpp"
    break;

  case 13: /* ReturnTypeOptional: %empty  */
#line 188 "src/parser.y"
                                     { (yyval.Type_Pointer) = new VarType();}
#line 1429 "parser.tab.cpp"
    break;

  case 14: /* Type: INT  */
#line 191 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new IntType(); }
#line 1435 "parser.tab.cpp"
    break;

  case 15: /* Type: IDENTIFIER  */
#line 192 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new VarType(); }
#line 1441 "parser.tab.cpp"
    break;

  case 16: /* Type: Type SQWAR_BRACKET_START Expression SQWAR_BRACKET_END  */
#line 193 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new VarType(); }
#line 1447 "parser.tab.cpp"
    break;

  case 17: /* Type: Type IS_SMALLER Type IS_GREATER  */
#line 194 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new VarType(); }
#line 1453 "parser.tab.cpp"
    break;

  case 18: /* Type: Type STAR  */
#line 195 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new VarType(); }
#line 1459 "parser.tab.cpp"
    break;

  case 19: /* Type: Type STAR SQWAR_BRACKET_START Expression SQWAR_BRACKET_END  */
#line 196 "src/parser.y"
                                                                       { (yyval.Type_Pointer) = new VarType(); }
#line 1465 "parser.tab.cpp"
    break;

  case 22: /* Statement: LINE_END  */
#line 204 "src/parser.y"
                                         { Scopes->Push(new EmptyStatement(),Tab_Num); }
#line 1471 "parser.tab.cpp"
    break;

  case 23: /* Statement: RETURN Expression LINE_END  */
#line 205 "src/parser.y"
                                                 { Scopes->Push(new ReturnStatement((yyvsp[-1].Expr_Pointer)),Tab_Num); }
#line 1477 "parser.tab.cpp"
    break;

  case 24: /* Statement: IF Expression TWO_DOTS  */
#line 206 "src/parser.y"
                                                 { Scopes->Push(new IfStatement(new std::list<Statement*>,(yyvsp[-1].Expr_Pointer)),Tab_Num); }
#line 1483 "parser.tab.cpp"
    break;

  case 25: /* Statement: WHILE Expression TWO_DOTS  */
#line 207 "src/parser.y"
                                                 { Scopes->Push(new WhileStatement(new std::list<Statement*>,(yyvsp[-1].Expr_Pointer)),Tab_Num); }
#line 1489 "parser.tab.cpp"
    break;

  case 26: /* Statement: VAR Type IDENTIFIER LINE_END  */
#line 208 "src/parser.y"
                                         { Scopes->Push(new VarDefineStatement((yyvsp[-2].Type_Pointer),(yyvsp[-1].String)),Tab_Num); }
#line 1495 "parser.tab.cpp"
    break;

  case 27: /* Statement: Expression LINE_END  */
#line 209 "src/parser.y"
                                                 { Scopes->Push(new ExpressionBasedStatement((yyvsp[-1].Expr_Pointer)),Tab_Num); }
#line 1501 "parser.tab.cpp"
    break;

  case 28: /* Expression: NUM  */
#line 212 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new NumberExpression( (yyvsp[0].Integer) ); }
#line 1507 "parser.tab.cpp"
    break;

  case 29: /* Expression: STRING  */
#line 213 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new StringExpression( (yyvsp[0].String) ); }
#line 1513 "parser.tab.cpp"
    break;

  case 30: /* Expression: IDENTIFIER  */
#line 214 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new IdentifierExpression(  (yyvsp[0].String) );}
#line 1519 "parser.tab.cpp"
    break;

  case 31: /* Expression: Expression PLUS Expression  */
#line 215 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Addition);}
#line 1525 "parser.tab.cpp"
    break;

  case 32: /* Expression: Expression SUB Expression  */
#line 216 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Subtraction);}
#line 1531 "parser.tab.cpp"
    break;

  case 33: /* Expression: Expression DIV Expression  */
#line 217 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Divition);}
#line 1537 "parser.tab.cpp"
    break;

  case 34: /* Expression: Expression STAR Expression  */
#line 218 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Multipication);}
#line 1543 "parser.tab.cpp"
    break;

  case 35: /* Expression: Expression MODULO Expression  */
#line 219 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Remanider);}
#line 1549 "parser.tab.cpp"
    break;

  case 36: /* Expression: Expression EQUAL Expression  */
#line 220 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Moving);}
#line 1555 "parser.tab.cpp"
    break;

  case 37: /* Expression: Expression IS_EQUAL Expression  */
#line 221 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Comparation);}
#line 1561 "parser.tab.cpp"
    break;

  case 38: /* Expression: Expression ISNT_EQUAL Expression  */
#line 222 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new BinaryExpression( new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::Comparation) , (yyval.Expr_Pointer) = new NumberExpression( 0 ) ,BinaryExpression::Type::Comparation);}
#line 1567 "parser.tab.cpp"
    break;

  case 39: /* Expression: Expression IS_GREATER Expression  */
#line 223 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BiggerThanComparation);}
#line 1573 "parser.tab.cpp"
    break;

  case 40: /* Expression: Expression IS_SMALLER Expression  */
#line 224 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[0].Expr_Pointer) , (yyvsp[-2].Expr_Pointer) ,BinaryExpression::Type::BiggerThanComparation);}
#line 1579 "parser.tab.cpp"
    break;

  case 41: /* Expression: Expression DOT Expression  */
#line 225 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::MemberAccess);}
#line 1585 "parser.tab.cpp"
    break;

  case 42: /* Expression: Expression ARROW Expression  */
#line 226 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::PointerMemberAccess);}
#line 1591 "parser.tab.cpp"
    break;

  case 43: /* Expression: Expression LOGIC_AND Expression  */
#line 227 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BitwizeAnd);}
#line 1597 "parser.tab.cpp"
    break;

  case 44: /* Expression: Expression LOGIC_OR Expression  */
#line 228 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BitwizeOr);}
#line 1603 "parser.tab.cpp"
    break;

  case 45: /* Expression: Expression AMPERSAND Expression  */
#line 229 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BitwizeAnd);}
#line 1609 "parser.tab.cpp"
    break;

  case 46: /* Expression: Expression BIT_OR Expression  */
#line 230 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BitwizeOr);}
#line 1615 "parser.tab.cpp"
    break;

  case 47: /* Expression: Expression BIT_XOR Expression  */
#line 231 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new BinaryExpression( (yyvsp[-2].Expr_Pointer) , (yyvsp[0].Expr_Pointer) ,BinaryExpression::Type::BitwizeXor);}
#line 1621 "parser.tab.cpp"
    break;

  case 48: /* Expression: BIT_NOT Expression  */
#line 232 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new UnaryExpression ( (yyvsp[0].Expr_Pointer) , UnaryExpression::Type::BitwizeNot);}
#line 1627 "parser.tab.cpp"
    break;

  case 49: /* Expression: STAR Expression  */
#line 233 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new UnaryExpression ( (yyvsp[0].Expr_Pointer) , UnaryExpression::Type::Derefrence);}
#line 1633 "parser.tab.cpp"
    break;

  case 50: /* Expression: AMPERSAND Expression  */
#line 234 "src/parser.y"
                                             { (yyval.Expr_Pointer) = new UnaryExpression ( (yyvsp[0].Expr_Pointer) , UnaryExpression::Type::Refrence);}
#line 1639 "parser.tab.cpp"
    break;

  case 51: /* Expression: LOGIC_NOT Expression  */
#line 235 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new UnaryExpression ( (yyvsp[0].Expr_Pointer) , UnaryExpression::Type::LogicalNot);}
#line 1645 "parser.tab.cpp"
    break;

  case 52: /* Expression: SUB Expression  */
#line 236 "src/parser.y"
                                                         { (yyval.Expr_Pointer) = new UnaryExpression ( (yyvsp[0].Expr_Pointer) , UnaryExpression::Type::Negativity);}
#line 1651 "parser.tab.cpp"
    break;

  case 53: /* Expression: Expression ROUND_BRACKET_START ExpressionsOption ROUND_BRACKET_END  */
#line 237 "src/parser.y"
                                                                                           { (yyval.Expr_Pointer) = new FunctionCallExpression((yyvsp[-3].Expr_Pointer),(yyvsp[-1].Expr_Pointer_List));}
#line 1657 "parser.tab.cpp"
    break;

  case 54: /* Expression: Expression SQWAR_BRACKET_START Expression SQWAR_BRACKET_END  */
#line 238 "src/parser.y"
                                                                                           { (yyval.Expr_Pointer) = new ArrayAccessExpression((yyvsp[-3].Expr_Pointer),(yyvsp[-1].Expr_Pointer));}
#line 1663 "parser.tab.cpp"
    break;

  case 55: /* Expression: ROUND_BRACKET_START Expression ROUND_BRACKET_END  */
#line 239 "src/parser.y"
                                                                               { (yyval.Expr_Pointer) = (yyvsp[-1].Expr_Pointer) ;}
#line 1669 "parser.tab.cpp"
    break;

  case 56: /* Expressions: Expression COMA Expressions  */
#line 242 "src/parser.y"
                                         { (yyvsp[0].Expr_Pointer_List)->push_front((yyvsp[-2].Expr_Pointer)); (yyval.Expr_Pointer_List) = (yyvsp[0].Expr_Pointer_List);}
#line 1675 "parser.tab.cpp"
    break;

  case 57: /* Expressions: Expression  */
#line 243 "src/parser.y"
                                                     { (yyval.Expr_Pointer_List) = new std::list<Expression*>; (yyval.Expr_Pointer_List)->push_front((yyvsp[0].Expr_Pointer)); }
#line 1681 "parser.tab.cpp"
    break;

  case 58: /* ExpressionsOption: Expressions  */
#line 246 "src/parser.y"
                               { (yyval.Expr_Pointer_List) = (yyvsp[0].Expr_Pointer_List) ;}
#line 1687 "parser.tab.cpp"
    break;

  case 59: /* ExpressionsOption: %empty  */
#line 247 "src/parser.y"
                               { (yyval.Expr_Pointer_List) = new std::list<Expression*>;}
#line 1693 "parser.tab.cpp"
    break;


#line 1697 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 249 "src/parser.y"



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
