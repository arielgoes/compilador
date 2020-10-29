/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 87 "bas.y" /* yacc.c:1909  */

    struct node* no;
    char *str; 

#line 117 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
