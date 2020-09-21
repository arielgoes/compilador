%{
#include <stdio.h>
#include <stdlib.h>
%}

D      	  [0-9]
L		  [a-zA-Z_]
E         ([Ee][+-]?{D}+)

L?#(\\.|[^\\"\n])* 			{count(); return(COMMENT);}

"+"							{count(); return('+');}
"-"							{count(); return('-');}
"*"							{count(); return('*');}
"/"							{count(); return('/');}
"!"							{count(); return('!');}
"%"							{count(); return('%');}
"&"							{count(); return('&');}
";"							{count(); return(';');}
"="							{count(); return('=');}
">"							{count(); return('>');}
"<"							{count(); return('<');}
"\("						{count(); return('(');}
"\)"						{count(); return(')');}
"{"							{count(); return('{');}
"}"							{count(); return('}');}
"["							{count(); return('[');}
"]"							{count(); return(']');}

"++"						{count(); return(INCR);}
"--"						{count(); return(DECR);}
">="						{count(); return(GREATER_EQUAL);}
"<="						{count(); return(SMALLER_EQUAL);}
"=="						{count(); return(EQUAL);}
"!="						{count(); return(DIFF);}
"&&"						{count(); return(AND);}
"||"						{count(); return(OR);}
"while"						{count(); return(WHILE);} 
"for"						{count(); return(FOR);}
"if"						{count(); return(IF);}
"else"						{count(); return(ELSE);}
"break"						{count(); return(BREAK);} 
"continue"					{count(); return(CONTINUE);}
"return"					{count(); return(RETURN);}
"switch"					{count(); return(SWITCH);}
"case"						{count(); return(CASE);} 
"default"					{count(); return(DEFAULT);}

L?'(\\.|[^\\'\n])'			{count(); return(CONSTANT);} /*char*/
L?\"(\\.|[^\\"\n])*\"		{count(); return(STRING_LITERAL);} /*string*/

"float"						{count(); return(FLOAT);}
"double"					{count(); return(DOUBLE);}
"int"						{count(); return(INT);} 
"char"						{count(); return(CHAR);}
"void"						{count(); return(VOID);}
"bool"						{count(); return(BOOL);}

{D}+                   		{count(); return(CONSTANT);} /*integer*/
{D}*"."{D}+{E}?				{count(); return(CONSTANT);} /*float*/
{D}+"."{D}*{E}?				{count(); return(CONSTANT);} /*float*/

[ \t\r\n]					{count();}
.							{printf("Invalid character!");}

%%
%%

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

int main(){
	yyin = fopen("text.txt", "r");
	yylex();
	printf("\n");
	fclose(yyin);
	return 0;
}