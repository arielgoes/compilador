
%{
#include <stdio.h>
#include <stdlib.h>
%}

/*NÚMEROS*/
digit      	  [0-9]
letter		  [a-zA-Z_]
exp           ([Ee][+-]?{digit}+)

/*CARACTERES ESPECIAS*/
comment 	    L?#(\\.|[^\\"\n])*
sum		        "+"
sub		        "-"
mult		    "*"
div		        "/"
mod             "%"
incr 		    "++"
decr 		    "--"
greater		    ">"
smaller		    "<"
greater_equal   ">="
smaller_equal   "<="
equal		    "=="
diff		    "/="
assignment      "="
and		        "&&"
or		        "||"
not		        "!"
open_par	    "\("
close_par	    "\)"
open_bracket	"{"
close_bracket	"}"
quote		    "\""
while           "while"
for             "for"
if              "if"
else            "else"
break           "break"
continue        "continue"
float           "float"
int             "int"
switch          "switch"
case            "case"
double          "double"



/*OPERAÇÕES MATEMÁTICAS*/

/*binary_operators	{sum}|{sub}|{mult}|{div}*/
/*incr_operation      {digit}{incr}*/
/*decr_operation      {digit}{decr}*/
/*operations          {digit}{binary_operators}{digit}*/

/*OPERAÇÕES LÓGICAS*/

/*math_logic      	{digit}({smaller}|{greater}|{equal}|{diff}|{greater_equal}|{smaller_equal}){digit}*/
/*binary_logic	    {and}|{or}*/
/*unary_logic		{not}*/

/*ESTRUTURAS*/

%%
{digit} 	        printf("digit: %s, length: %d\n", yytext, yyleng);
{int}               printf("int: %s, length: %d\n", yytext, yyleng);
{for}               printf("for: %s, length: %d\n", yytext, yyleng);
{exp}               printf("exp: %s, length: %d\n", yytext, yyleng);
{sum}               printf("sum: %s, length: %d\n", yytext, yyleng);
{comment}   		printf("comment: %s, length: %d\n", yytext, yyleng);
{open_bracket}		printf("open_bracket: %s, length: %d\n", yytext, yyleng);
{close_bracket}		printf("close_bracket: %s, length: %d\n", yytext, yyleng);
{open_par}	        printf("open_par: %s, length: %d\n", yytext, yyleng);
{close_par}	        printf("close_par: %s, length: %d\n", yytext, yyleng);
.
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
	return 0;
}
