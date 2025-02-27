%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h" /*table of symbols (linkage between 'lex' and 'yacc')*/
	extern void yyerror(const char *);  /* prints grammar violation message */
	void comment(void);
	void count(void);
	extern int sym_type(const char *);  /* returns type from symbol table */
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
","							{count(); return(',');}
"\("						{count(); return('(');}
"\)"						{count(); return(')');}
"{"							{count(); return('{');}
"}"							{count(); return('}');}
"["							{count(); return('[');}
"]"							{count(); return(']');}

"++"						{count(); yylval.str = strdup(yytext); return(INCR);}
"--"						{count(); yylval.str = strdup(yytext); return(DECR);}
"<="						{count(); yylval.str = strdup(yytext); return(LE);}
">="						{count(); yylval.str = strdup(yytext); return(GE);}
"=="						{count(); yylval.str = strdup(yytext); return(EQ);}
"!="						{count(); yylval.str = strdup(yytext); return(NE);}
">"							{count(); yylval.str = strdup(yytext); return(GT);}
"<"							{count(); yylval.str = strdup(yytext); return(LT);}
"&&"						{count(); yylval.str = strdup(yytext); return(AND);}
"||"						{count(); yylval.str = strdup(yytext); return(OR);}

"printf"					{count(); yylval.str = strdup(yytext); return(PRINTF);}

"while"						{count(); return(WHILE);} 
"for"						{count(); return(FOR);}
"if"						{count(); return(IF);}
"elif"						{count(); return(ELIF);}
"else"						{count(); return(ELSE);}
"break"						{count(); return(BREAK);} 
"continue"					{count(); return(CONTINUE);}
"return"					{count(); return(RETURN);}

"float"						{count(); yylval.str = strdup(yytext); return(FLOAT);}
"double"					{count(); yylval.str = strdup(yytext); return(DOUBLE);}
"int"						{count(); yylval.str = strdup(yytext); return(INT);} 
"char"						{count(); yylval.str = strdup(yytext); return(CHAR);}
"void"						{count(); yylval.str = strdup(yytext); return(VOID);}

L?\'(\\.|[^\\'\n])\'		{count(); yylval.str = strdup(yytext); return(CONSTANT_CHAR);} 		/*char*/
L?\"(\\.|[^\\"\n])*\"		{count(); yylval.str = strdup(yytext); return(CONSTANT_STR);} 		/*string*/
{D}+                   		{count(); yylval.str = strdup(yytext); return(CONSTANT_INT);} 		/*integer*/
{D}*"."{D}+{E}?				{count(); yylval.str = strdup(yytext); return(CONSTANT_FLOAT);} 	/*float*/
{D}+"."{D}*{E}?				{count(); yylval.str = strdup(yytext); return(CONSTANT_FLOAT);} 	/*float*/

{L}({L}|{D})* 				{count(); yylval.str = strdup(yytext); return(ID);} /*identififier (e.g., foo, a, myVar, myFunc)*/ 

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

void comment(void){
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}