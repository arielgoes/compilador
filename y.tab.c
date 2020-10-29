/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "bas.y" /* yacc.c:339  */

    #include <stdlib.h>
    #include <stdio.h>
    #include "node.h"
    #include "symbol_table.h"
    #include "lista.h"
    
    #define UNDEFINED_TYPE -9999
    #define FLOAT_TYPE 1
    #define INT_TYPE 2
    #define CHAR_TYPE 3
    #define DOUBLE_TYPE 4

    #define FLOAT_SIZE 4
    #define INT_SIZE 4
    #define CHAR_SIZE 1
    #define DOUBLE_SIZE 8

    extern void yyerror(const char *);  /* prints grammar violation message */
    extern int yylineno;
    extern Node* syntax_tree;
    extern symbol_t symbol_table;

    //extern char yytext[];
    extern int column;

    void yyerror(char const *s){
        fflush(stdout);
        printf("\n%*s\n%*s\n", column, "^", column, s);
    }

    int vars_size = 0;
    int tipo_global = 0;

    
    void create_table_entry(char* lexeme){
        if(lookup(symbol_table, lexeme)){
            printf("'%s' symbol defined multiple times. Type: %d.\n", lexeme, tipo_global);
            return;
        }else{
            entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
            printf("\n>>>> New symbol on table: %s, type: %d\n", lexeme, tipo_global);
            new_entry->name = lexeme;
            switch(tipo_global){
                case FLOAT_TYPE: 
                    vars_size += FLOAT_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = FLOAT_SIZE;
                    new_entry->desloc = vars_size;
                    break; 
                case INT_TYPE:
                    vars_size += INT_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = INT_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                case CHAR_TYPE:
                    vars_size += CHAR_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = CHAR_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                case DOUBLE_TYPE:
                    vars_size += DOUBLE_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = DOUBLE_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                default:
                    printf("\n>>>> ERROR: Undefined type '%s' ^\n", lexeme);
                    exit(0);
            }

            if(insert(&symbol_table, new_entry) == -1){
                printf("\n>>>> insert table: ERROR! Cannot allocate %s into 'symbol_table'!\n", lexeme);
                exit(0);
            }else{
                printf("\n>>>> insert table: SUCCESS! value: %s\n", lexeme);
            }

        }
    }


#line 151 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHILE = 258,
    FOR = 259,
    IF = 260,
    ELSE = 261,
    ELIF = 262,
    BREAK = 263,
    CONTINUE = 264,
    RETURN = 265,
    PRINTF = 266,
    FLOAT = 267,
    INT = 268,
    CHAR = 269,
    VOID = 270,
    DOUBLE = 271,
    ID = 272,
    CONSTANT = 273,
    INCR = 274,
    DECR = 275,
    GE = 276,
    LE = 277,
    EQ = 278,
    NE = 279,
    LT = 280,
    GT = 281,
    AND = 282,
    OR = 283,
    NOT = 284
  };
#endif
/* Tokens.  */
#define WHILE 258
#define FOR 259
#define IF 260
#define ELSE 261
#define ELIF 262
#define BREAK 263
#define CONTINUE 264
#define RETURN 265
#define PRINTF 266
#define FLOAT 267
#define INT 268
#define CHAR 269
#define VOID 270
#define DOUBLE 271
#define ID 272
#define CONSTANT 273
#define INCR 274
#define DECR 275
#define GE 276
#define LE 277
#define EQ 278
#define NE 279
#define LT 280
#define GT 281
#define AND 282
#define OR 283
#define NOT 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 87 "bas.y" /* yacc.c:355  */

    struct node* no;
    char *str; 

#line 254 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   297

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      38,    39,    33,    31,    36,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
       2,    30,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   139,   140,   144,   145,   150,   152,   154,
     156,   158,   165,   169,   172,   179,   182,   184,   186,   188,
     192,   195,   198,   201,   204,   207,   209,   211,   213,   216,
     218,   220,   223,   227,   229,   231,   232,   237,   243,   251,
     253,   255,   257,   259,   265,   269,   276,   284,   285,   289,
     292,   296,   302,   308,   309,   313,   314,   315,   316,   317,
     318,   319,   326,   334,   341,   349,   356,   361,   362,   366,
     371,   372,   373,   377,   378,   379,   380,   381,   382,   383,
     384,   389,   392,   395,   398,   404
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "FOR", "IF", "ELSE", "ELIF",
  "BREAK", "CONTINUE", "RETURN", "PRINTF", "FLOAT", "INT", "CHAR", "VOID",
  "DOUBLE", "ID", "CONSTANT", "INCR", "DECR", "GE", "LE", "EQ", "NE", "LT",
  "GT", "AND", "OR", "NOT", "'='", "'+'", "'-'", "'*'", "'/'", "';'",
  "','", "'%'", "'('", "')'", "'['", "']'", "'{'", "'}'", "$accept",
  "atree", "translation_unit", "external_declaration", "declaration",
  "declaration_assignment", "assignment", "array_usage",
  "declaration_array_usage", "type", "function_call", "function",
  "arg_list_opt", "arg_list", "arg", "compound_stmt", "stmt_list", "stmt",
  "while_stmt", "for_stmt", "if_stmt", "else_elif_stmt", "else_stmt",
  "expr", "relop", "jump_statement", "print_func", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      61,    43,    45,    42,    47,    59,    44,    37,    40,    41,
      91,    93,   123,   125
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -74,   -74,   -74,   -74,   -74,   110,   186,    -2,   138,
       7,   -74,    39,   -74,   -24,   -27,     3,   -17,   -74,   -74,
     -74,   140,   138,   138,   138,   138,   138,    49,   138,   138,
     138,   138,   138,   138,   138,   -74,   -74,   138,   134,     4,
      14,   -74,   -74,   -74,   138,   -74,   -21,    11,    12,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    10,    17,
     -74,   -74,   -74,   -74,   -74,   -74,    20,   -74,   -74,   140,
     147,   138,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    43,
      29,    33,   -74,    35,   -74,    32,   147,   -74,   -74,   -74,
     -74,    90,    40,    41,    46,    50,    51,    99,    52,   -74,
     -74,   -74,    72,   -74,   -74,   -74,   -74,   -74,   -74,   138,
     138,   138,   -74,   -74,   -74,   -74,    14,   239,   138,   -26,
     177,   158,   185,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   138,   204,    32,   138,    32,    32,   269,    61,
     -74,   254,   -74,    -1,   -74,   138,    32,    74,   -74,   -74,
     212,   -74,   138,    32,   231,   -74,    32,    -1,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    39,    40,    41,    42,    43,    36,    35,     0,     0,
       0,     2,     3,     6,     0,     0,     0,     0,     5,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    33,     0,    36,     0,
       0,     1,     4,     8,     0,    10,    14,     0,     0,     9,
      15,    16,    19,    20,    21,    22,    23,    44,     0,     0,
      24,    25,    26,    27,    18,    28,     0,    31,    17,     0,
      48,     0,     7,    11,    45,    37,    32,    12,    13,     0,
       0,    47,    50,     0,    51,     0,     0,    38,    54,    46,
      49,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      52,    56,     0,    53,    55,    57,    58,    60,    59,     0,
       0,     0,    82,    81,    83,    71,    72,     0,     0,    14,
       0,     0,     0,    74,    73,    76,    75,    78,    77,    79,
      80,    84,     0,     0,     0,     0,     0,     0,    70,     0,
      62,     0,    64,    68,    85,     0,     0,     0,    65,    67,
       0,    69,     0,     0,     0,    63,     0,    68,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   101,   -74,    23,   -74,     1,     0,   -74,   -49,
     -19,   -74,   -74,   -74,    34,   -73,   -74,   -74,   -74,   -74,
     -74,   -42,   -74,   -70,   -74,   -74,   -74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    47,   115,    40,    48,    16,
      17,    18,    80,    81,    82,    89,    91,   103,   104,   105,
     106,   148,   149,   117,   132,   107,   108
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,    14,    51,    44,    69,   146,   147,    41,    45,    69,
      39,    43,    15,    14,    71,    35,    36,    70,    49,    71,
      46,    79,    50,    52,    53,    54,    55,    56,    58,    59,
      60,    61,    62,    63,    64,    65,    37,    79,    66,   120,
     121,   122,   102,    67,    44,    68,    72,    73,   133,    74,
      78,     1,     2,     3,     4,     5,     6,     7,    75,    76,
      84,   140,   138,   142,   143,   141,    38,     7,    85,    86,
      77,     8,    83,   151,    88,   150,    87,     9,   109,   110,
     155,     8,   154,   157,   111,   112,   113,     9,    57,   119,
     118,    15,    14,    92,    93,    94,   144,   116,    95,    96,
      97,    98,     1,     2,     3,     4,     5,     6,     7,   116,
     116,   116,   152,    42,   101,   158,    38,     7,   116,     0,
      90,     0,     8,     0,     0,    99,     0,     0,     9,    19,
      20,     8,   116,   100,   114,   116,     0,     9,     0,     0,
      21,    22,    23,    24,    25,   116,     0,    26,    27,     0,
      28,     0,   116,    19,    20,    38,     7,     6,     7,     1,
       2,     3,     4,     5,    21,    22,    23,    24,    25,     0,
       8,    26,     8,     0,    28,     0,     9,     0,     9,   123,
     124,   125,   126,   127,   128,   129,   130,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,   136,   123,   124,
     125,   126,   127,   128,   129,   130,   123,   124,   125,   126,
     127,   128,   129,   130,     0,     0,   134,    29,    30,    31,
      32,     0,    33,    34,   137,   123,   124,   125,   126,   127,
     128,   129,   130,   123,   124,   125,   126,   127,   128,   129,
     130,     0,     0,   139,     0,     0,     0,     0,     0,     0,
       0,   153,   123,   124,   125,   126,   127,   128,   129,   130,
     123,   124,   125,   126,   127,   128,   129,   130,     0,     0,
     156,     0,     0,     0,   131,   123,   124,   125,   126,   127,
     128,   129,   130,     0,     0,     0,     0,     0,     0,   145,
     123,   124,   125,   126,   127,   128,   129,   130
};

static const yytype_int16 yycheck[] =
{
       0,     0,    21,    30,    30,     6,     7,     0,    35,    30,
       9,    35,    12,    12,    40,    17,    18,    38,    35,    40,
      17,    70,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    38,    86,    37,   109,
     110,   111,    91,    39,    30,    44,    35,    35,   118,    39,
      69,    12,    13,    14,    15,    16,    17,    18,    41,    39,
      17,   134,   132,   136,   137,   135,    17,    18,    39,    36,
      69,    32,    71,   146,    42,   145,    41,    38,    38,    38,
     153,    32,   152,   156,    38,    35,    35,    38,    39,    17,
      38,    91,    91,     3,     4,     5,    35,    97,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   109,
     110,   111,    38,    12,    91,   157,    17,    18,   118,    -1,
      86,    -1,    32,    -1,    -1,    35,    -1,    -1,    38,    19,
      20,    32,   132,    43,    35,   135,    -1,    38,    -1,    -1,
      30,    31,    32,    33,    34,   145,    -1,    37,    38,    -1,
      40,    -1,   152,    19,    20,    17,    18,    17,    18,    12,
      13,    14,    15,    16,    30,    31,    32,    33,    34,    -1,
      32,    37,    32,    -1,    40,    -1,    38,    -1,    38,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    39,    21,    22,
      23,    24,    25,    26,    27,    28,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    39,    31,    32,    33,
      34,    -1,    36,    37,    39,    21,    22,    23,    24,    25,
      26,    27,    28,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    21,    22,    23,    24,    25,    26,    27,    28,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      39,    -1,    -1,    -1,    35,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      21,    22,    23,    24,    25,    26,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    32,    38,
      45,    46,    47,    48,    50,    51,    53,    54,    55,    19,
      20,    30,    31,    32,    33,    34,    37,    38,    40,    31,
      32,    33,    34,    36,    37,    17,    18,    38,    17,    50,
      51,     0,    46,    35,    30,    35,    17,    49,    52,    35,
      50,    54,    50,    50,    50,    50,    50,    39,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    39,    50,    30,
      38,    40,    35,    35,    39,    41,    39,    50,    54,    53,
      56,    57,    58,    50,    17,    39,    36,    41,    42,    59,
      58,    60,     3,     4,     5,     8,     9,    10,    11,    35,
      43,    48,    53,    61,    62,    63,    64,    69,    70,    38,
      38,    38,    35,    35,    35,    50,    51,    67,    38,    17,
      67,    67,    67,    21,    22,    23,    24,    25,    26,    27,
      28,    35,    68,    67,    39,    35,    39,    39,    67,    39,
      59,    67,    59,    59,    35,    35,     6,     7,    65,    66,
      67,    59,    38,    39,    67,    59,    39,    59,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    48,
      48,    48,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    51,    52,    53,
      53,    53,    53,    53,    54,    54,    55,    56,    56,    57,
      57,    58,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    62,    63,    63,    64,    65,    65,    65,    66,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    69,    69,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     2,
       2,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     2,     2,     1,     1,     4,     4,     1,
       1,     1,     1,     1,     3,     4,     6,     1,     0,     3,
       1,     2,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     5,     9,     5,     6,     6,     1,     0,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     3,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 133 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, atree_node, "atree", (yyvsp[0].no), NULL); syntax_tree = (yyval.no);
    uncompile(stdout, (yyvsp[0].no));}
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 139 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, translation_unit_node, "external_declaration", (yyvsp[0].no), NULL);}
#line 1490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 140 "bas.y" /* yacc.c:1646  */
    {(yyval.no)=create_node(yylineno, translation_unit_node, "external_declaration translation_unit", (yyvsp[-1].no), (yyvsp[0].no), NULL);}
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 144 "bas.y" /* yacc.c:1646  */
    { (yyval.no) = create_node(yylineno, external_declaration_node, "function", (yyvsp[0].no), NULL); }
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 145 "bas.y" /* yacc.c:1646  */
    { (yyval.no) = create_node(yylineno, external_declaration_node, "declaration", (yyvsp[0].no), NULL); }
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 150 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        (yyval.no) = create_node(yylineno, declaration_node, "type assignment ;", (yyvsp[-2].str), (yyvsp[-1].no), semicollon, NULL);}
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        (yyval.no) = create_node(yylineno, declaration_node, "assignment ;", (yyvsp[-1].no), semicollon, NULL);}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 154 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        (yyval.no) = create_node(yylineno, declaration_node, "function_call ;", (yyvsp[-1].no), semicollon, NULL);}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 156 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        (yyval.no) = create_node(yylineno, declaration_node, "array_usage ;", (yyvsp[-1].no), semicollon, NULL);}
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 158 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        (yyval.no) = create_node(yylineno, declaration_node, "assignment ;", (yyvsp[-2].str), (yyvsp[-1].no), semicollon, NULL);}
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 165 "bas.y" /* yacc.c:1646  */
    {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, "ID", NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "ID = assignment", id, eq, (yyvsp[0].no), NULL);
                                create_table_entry((yyvsp[-2].str));}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 169 "bas.y" /* yacc.c:1646  */
    {Node* eq = create_node(yylineno, eq_node, "=", NULL, NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "ID = function_call", (yyvsp[-2].str), eq, (yyvsp[0].no), NULL);
                                create_table_entry((yyvsp[-2].str));}
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 172 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, assignment_node, "ID", (yyvsp[0].str), NULL);
                                create_table_entry((yyvsp[0].str));}
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 179 "bas.y" /* yacc.c:1646  */
    {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, "ID", NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "ID = assignment", id, eq, (yyvsp[0].no), NULL);}
#line 1575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 182 "bas.y" /* yacc.c:1646  */
    {Node* eq = create_node(yylineno, eq_node, "=", NULL, NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "ID = function_call", (yyvsp[-2].str), eq, (yyvsp[0].no), NULL);}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 184 "bas.y" /* yacc.c:1646  */
    {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, "array_usage = assignment", (yyvsp[-2].no), eq, (yyvsp[0].no), NULL);}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 186 "bas.y" /* yacc.c:1646  */
    {Node* collon = create_node(yylineno, collon_node, ",", NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "CONSTANT, assignment", (yyvsp[-2].str), collon, (yyvsp[0].no), NULL);}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 188 "bas.y" /* yacc.c:1646  */
    {Node* sum = create_node(yylineno, sum_node, "+", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "ID + assignment", (yyvsp[-2].str), sum, (yyvsp[0].no), NULL);
                            struct tac* new_tac = create_inst_tac((yyval.no)->lexeme, (yyvsp[-2].str), "+", (yyvsp[0].no)->lexeme);}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 192 "bas.y" /* yacc.c:1646  */
    {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "ID - assignment", (yyvsp[-2].str), sub, (yyvsp[0].no), NULL);}
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 195 "bas.y" /* yacc.c:1646  */
    {Node* mult = create_node(yylineno, mult_node, "*", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "ID * assignment", (yyvsp[-2].str), mult, (yyvsp[0].no), NULL);}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 198 "bas.y" /* yacc.c:1646  */
    {Node* mult = create_node(yylineno, div_node, "/", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "ID / assignment", (yyvsp[-2].str), div, (yyvsp[0].no), NULL);}
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 201 "bas.y" /* yacc.c:1646  */
    {Node* mod = create_node(yylineno, mod_node, "%", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "ID % assignment", (yyvsp[-2].str), mod, (yyvsp[0].no), NULL);}
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "bas.y" /* yacc.c:1646  */
    {Node* sum = create_node(yylineno, sum_node, "+", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, (char *)(yyval.no), (yyvsp[-2].str), sum, (yyvsp[0].no), NULL);
                                    struct tac* new_tac = create_inst_tac((yyval.no)->lexeme, (yyvsp[-2].str), "+", (yyvsp[0].no)->lexeme);}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 207 "bas.y" /* yacc.c:1646  */
    {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, "CONSTANT - assignment", (yyvsp[-2].str), sub, (yyvsp[0].no)), NULL;}
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 209 "bas.y" /* yacc.c:1646  */
    {Node* mult = create_node(yylineno, mult_node, "*", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, "CONSTANT * assignment", (yyvsp[-2].str), mult, (yyvsp[0].no), NULL);}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 211 "bas.y" /* yacc.c:1646  */
    {Node* div = create_node(yylineno, div_node, "/", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, "CONSTANT / assignment", (yyvsp[-2].str), div, (yyvsp[0].no), NULL);}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 213 "bas.y" /* yacc.c:1646  */
    {Node* mod = create_node(yylineno, mod_node, "%", NULL);
                                    (yyval.no) = create_node(yylineno, assignment_node, "CONSTANT % assignment", (yyvsp[-2].str), mod, (yyvsp[0].no), NULL);}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 216 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, assignment_node, "ID INCR", (yyvsp[-1].str), (yyvsp[0].str), NULL);}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 218 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, assignment_node, "ID DECR", (yyvsp[-1].str), (yyvsp[0].str), NULL);}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 220 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                            Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                            (yyval.no) = create_node(yylineno, assignment_node, "( assignment )", open_round_brac, (yyvsp[-1].no), close_round_brac, NULL);}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 223 "bas.y" /* yacc.c:1646  */
    {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                                Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                (yyval.no) = create_node(yylineno, assignment_node, "( assignment )", sub, open_round_brac, (yyvsp[-1].no), close_round_brac, NULL);}
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 227 "bas.y" /* yacc.c:1646  */
    {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                    (yyval.no) = create_node(yylineno, assignment_node, "- CONSTANT", sub, (yyvsp[0].str), NULL);}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 229 "bas.y" /* yacc.c:1646  */
    {Node* sub = (Node*)malloc(sizeof(Node));
                    (yyval.no) = create_node(yylineno, assignment_node, "- ID", sub, (yyvsp[0].str), NULL);}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 231 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, assignment_node, (char *)(yyvsp[0].str), (yyvsp[0].str), NULL);}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 232 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, assignment_node, "ID", (yyvsp[0].str), NULL);}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 237 "bas.y" /* yacc.c:1646  */
    {Node* open_sqr_brac = create_node(yylineno, open_sqr_brac_node, "[", NULL);
                            Node* close_sqr_brac = create_node(yylineno, close_sqr_brac_node, "]", NULL);
                            (yyval.no) = create_node(yylineno, array_usage_node, "ID [ assignment ]", (yyvsp[-3].str), open_sqr_brac, (yyvsp[-1].no), close_sqr_brac, NULL);}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 243 "bas.y" /* yacc.c:1646  */
    {Node* open_sqr_brac = create_node(yylineno, open_sqr_brac_node, "[", NULL);
                            Node* close_sqr_brac = create_node(yylineno, close_sqr_brac_node, "]", NULL);
                            (yyval.no) = create_node(yylineno, array_usage_node, "ID [ assignment ]", (yyvsp[-3].str), open_sqr_brac, (yyvsp[-1].no), close_sqr_brac, NULL);
                            create_table_entry((yyvsp[-3].str));}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 251 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, type_node, "FLOAT", (yyvsp[0].str), NULL);
                tipo_global = FLOAT_TYPE;}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 253 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, type_node, "INT", (yyvsp[0].str), NULL);
                tipo_global = INT_TYPE;}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 255 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, type_node, "CHAR", (yyvsp[0].str), NULL);
                tipo_global = CHAR_TYPE;}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 257 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, type_node, "VOID", (yyvsp[0].str), NULL);
                tipo_global = 0;}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 259 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, type_node, "DOUBLE", (yyvsp[0].str), NULL);
                tipo_global = DOUBLE_TYPE;}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 265 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                (yyval.no) = create_node(yylineno, function_call_node, "ID ( )", (yyvsp[-2].str), open_round_brac, close_round_brac, NULL);}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 269 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                (yyval.no) = create_node(yylineno, function_call_node, "ID ( assignment )", (yyvsp[-3].str), open_round_brac, (yyvsp[-1].no), close_round_brac, NULL);}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 276 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                    Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                    Node* id = create_node(yylineno, id_node, "ID", NULL);
                                                    (yyval.no) = create_node(yylineno, function_node, "type ID ( arg_list_opt ) compound_stmt", 
                                                    (yyvsp[-5].str), id, open_round_brac, (yyvsp[-2].no), close_round_brac, (yyvsp[0].no), NULL);}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 284 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, arg_list_opt_node, "arg_list", (yyvsp[0].no), NULL);}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 285 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, arg_list_opt_node, "arg_list_opt --> EMPTY", NULL);}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 289 "bas.y" /* yacc.c:1646  */
    {Node* collon = create_node(yylineno, collon_node, ",", NULL);
                        (yyval.no) = create_node(yylineno, arg_list_node, "arg_list , arg", (yyvsp[-2].no), collon, (yyvsp[0].no), NULL);}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 292 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, arg_list_node, "arg", (yyvsp[0].no), NULL);}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 296 "bas.y" /* yacc.c:1646  */
    {Node* id = create_node(yylineno, id_node, "ID", NULL);
                (yyval.no) = create_node(yylineno, arg_node, "type ID", (yyvsp[-1].str), id, NULL);
                create_table_entry((yyvsp[0].str));}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 302 "bas.y" /* yacc.c:1646  */
    {Node* open_curly_brac = create_node(yylineno, open_curly_brac_node, "{", NULL);
                        Node* close_curly_brac = create_node(yylineno, close_curly_brac_node, "}", NULL);
                        (yyval.no) = create_node(yylineno, compound_stmt_node, "{ stmt_list }", open_curly_brac, (yyvsp[-1].no), close_curly_brac, NULL);}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 308 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_list_node, "stmt_list stmt", (yyvsp[-1].no), (yyvsp[0].no), NULL);}
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 309 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_list_node, "stmt_list --> EMPTY", NULL);}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 313 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "while_stmt", (yyvsp[0].no), NULL);}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 314 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "declaration", (yyvsp[0].no), NULL);}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 315 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "for_stmt", (yyvsp[0].no), NULL);}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 316 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "if_stmt", (yyvsp[0].no), NULL);}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 317 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "print_func", (yyvsp[0].no), NULL);}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 318 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, stmt_node, "jump_statement", (yyvsp[0].no), NULL);}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 319 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                        (yyval.no) = create_node(yylineno, stmt_node, ";", semicollon, NULL);}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 326 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, "(", NULL);
                                        (yyval.no) = create_node(yylineno, while_stmt_node, "WHILE ( expr ) compound_stmt",
                                        (yyvsp[-4].no), open_round_brac, (yyvsp[-2].no), close_round_brac, (yyvsp[0].no), NULL);}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 334 "bas.y" /* yacc.c:1646  */
    {Node* semicollon1 = create_node(yylineno, semicollon_node, ";", NULL);
                                                        Node* semicollon2 = create_node(yylineno, semicollon_node, ";", NULL);
                                                        Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                        (yyval.no) = create_node(yylineno, for_stmt_node, "FOR ( expr ; expr ; expr ) compound_stmt",
                                                        (yyvsp[-8].no), open_round_brac, (yyvsp[-6].no), semicollon1, (yyvsp[-4].no), semicollon2, (yyvsp[-2].no), close_round_brac, (yyvsp[0].no), NULL);}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 341 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                        (yyval.no) = create_node(yylineno, for_stmt_node, "FOR ( expr ) compound_stmt", 
                                        (yyvsp[-4].no), open_round_brac, (yyvsp[-2].no), close_round_brac, (yyvsp[0].no), NULL);}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 349 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                    Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                    (yyval.no) = create_node(yylineno, if_stmt_node, "IF ( expr ) compound_stmt else_elif_stmt", 
                                                    (yyvsp[-5].no), open_round_brac, (yyvsp[-3].no), close_round_brac, (yyvsp[-1].no), (yyvsp[0].no), NULL);}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 356 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                        (yyval.no) = create_node(yylineno, else_elif_stmt_node, "ELIF '(' expr ')' compound_stmt else_elif_stmt",
                                                        (yyvsp[-5].no), open_round_brac, (yyvsp[-3].no), close_round_brac, (yyvsp[-1].no), (yyvsp[0].no), NULL);}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 361 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, else_elif_stmt_node, "else_stmt", (yyvsp[0].no), NULL);}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 362 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, else_elif_stmt_node, "else_stmt --> EMPTY", NULL);}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 366 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, else_stmt_node, "ELSE compound_stmt", (yyvsp[-1].no), (yyvsp[0].no), NULL);}
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 371 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, expr_node, "expr relop expr", (yyvsp[-2].no), (yyvsp[-1].str), (yyvsp[0].no), NULL);}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 372 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, expr_node, "assignment", (yyvsp[0].no), NULL);}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 373 "bas.y" /* yacc.c:1646  */
    {(yyval.no) = create_node(yylineno, expr_node, "array_usage", (yyvsp[0].no), NULL);}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 377 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, le_node, "=", NULL);}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 378 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, ge_node, ">=", NULL);}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 379 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, ne_node, "!=", NULL);}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 380 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, eq_node, "==", NULL);}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 381 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, gt_node, ">", NULL);}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 382 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, lt_node, "<", NULL);}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 383 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, and_node, "&&", NULL);}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 384 "bas.y" /* yacc.c:1646  */
    {(yyval.str) = create_node(yylineno, or_node, "||", NULL);}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 389 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    (yyval.no) = create_node(yylineno, jump_statement_node, "CONTINUE ;", (yyvsp[-1].no), semicollon, NULL);}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 392 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    (yyval.no) = create_node(yylineno, jump_statement_node, "BREAK ;", (yyvsp[-1].no), semicollon, NULL);}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 395 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    (yyval.no) = create_node(yylineno, jump_statement_node, "RETURN ;", (yyvsp[-1].no), semicollon, NULL);}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 398 "bas.y" /* yacc.c:1646  */
    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                        (yyval.no) = create_node(yylineno, jump_statement_node, "RETURN expr ;", (yyvsp[-2].no), (yyvsp[-1].no), semicollon, (char *)NULL);}
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 404 "bas.y" /* yacc.c:1646  */
    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
    							Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
    							Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
    							(yyval.no) = create_node(yylineno, print_func_node, "PRINTF ( expr ) ;", (yyvsp[-4].no), open_round_brac, (yyvsp[-2].no), close_round_brac, semicollon, NULL);}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2069 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 409 "bas.y" /* yacc.c:1906  */

