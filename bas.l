
%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h" /*table of symbols (linkage between 'lex' and 'yacc')*/
extern void yyerror(const char *);  /* prints grammar violation message */
void count(void);
%}

D      	  [0-9]
L		  [a-zA-Z_]
E         ([Ee][+-]?{D}+)

%%

"//"[^\n]*				 	
"/*"						{comment(); }
"+"							{count(); return('+');}
"-"							{count(); return('-');}
"*"							{count(); return('*');}
"/"							{count(); return('/');}
"!"							{count(); return('!');}
"%"							{count(); return('%');}
"&"							{count(); return('&');}
";"							{count(); return(';');}
"="							{count(); return('=');}

"\("						{count(); return('(');}
"\)"						{count(); return(')');}
"{"							{count(); return('{');}
"}"							{count(); return('}');}
"["							{count(); return('[');}
"]"							{count(); return(']');}

"++"						{count(); return(INCR);}
"--"						{count(); return(DECR);}
"<="						{count(); return(LE);}
">="						{count(); return(GE);}
"=="						{count(); return(EQ);}
"!="						{count(); return(NE);}
">"							{count(); return(GT);}
"<"							{count(); return(LT);}
"&&"						{count(); return(AND);}
"||"						{count(); return(OR);}

"printf"					{count(); return(PRINTF);}

"while"						{count(); return(WHILE);} 
"for"						{count(); return(FOR);}
"if"						{count(); return(IF);}
"elif"						{count(); return(ELIF);}
"else"						{count(); return(ELSE);}
"break"						{count(); return(BREAK);} 
"continue"					{count(); return(CONTINUE);}
"return"					{count(); return(RETURN);}

L?\'(\\.|[^\\'\n])\'		{count(); return(CONSTANT);}
L?\"(\\.|[^\\"\n])*\"		{count(); return(CONSTANT);}


"float"						{count(); return(FLOAT);}
"double"					{count(); return(DOUBLE);}
"int"						{count(); return(INT);} 
"char"						{count(); return(CHAR);}
"void"						{count(); return(VOID);}
"bool"						{count(); return(BOOL);}

{D}+                   		{count(); return(CONSTANT);} /*integer*/
{D}*"."{D}+{E}?				{count(); return(CONSTANT);} /*float*/
{D}+"."{D}*{E}?				{count(); return(CONSTANT);} /*float*/
{L}({L}|{D})* 				{count(); return(ID);} /*identififier (e.g., foo, a, myVar, myFunc)*/ 

[ \t\v\n\f]					{count();}
.							

%%

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}

int column = 0;
void count(void){
	int i;

	for (i = 0; yytext[i] != '\0'; i++){
		if (yytext[i] == '\n'){
			column = 0;
		}
		
		else if (yytext[i] == '\t'){
			column += 8 - (column % 8);
		}
		else{
			column++;
		}
	}
	ECHO;
}

void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}