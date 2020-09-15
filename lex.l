
%{
#include <stdio.h>
#include <stdlib.h>
#define ECHO fwrite(yytext, yyleng, 1, yyout)
%}

/*NÚMEROS*/

digit      	  [0-9]
integer       {digit}+
float    	  ([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)

/*CARACTERES ESPECIAS*/
comment 	    "#"{characters}"#"
sum		        "+"
sub		        "-"
mult		    "*"
div		        "/"
incr 		    "++"
decr 		    "--"
greater		    ">"
smaller		    "<"
greater_equal   ">="
smaller_equal   "<="
equal		    "=="
diff		    "/="
and		        "&&"
or		        "||"
not		        "!"
open_par	    "\("
close_par	    "\)"
open_bracket	"{"
close_bracket	"}"
quote		    "\""
if		        "if"
while		    "while"
for		        "for"
space		    "\n"|" "|"\t"

/* STRING */

characters	[A-Za-z0-9!-/:-@[-`{-~´ç{space}]+
string		  {quote}{characters}{quote}

/*caracteres aceitos "!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvxwyz[\]^_`´ç\n"*/

/*OPERAÇÕES MATEMÁTICAS*/

binary_operators	{sum}|{sub}|{mult}|{div}
incr_operation 		({integer}{incr})|({float}{decr})
decr_operation		({integer}{decr})|({float}{decr})
operations		    ({integer}|{float}){binary_operators}({integer}|{float})

/*OPERAÇÕES LÓGICAS*/

math_logic      	{integer}({smaller}|{greater}|{equal}|{diff}|{greater_equal}|{smaller_equal}){integer}|{float}({smaller}|{greater}|{equal}|{diff}|{greater_equal}|{smaller_equal}){float}
binary_logic	    {and}|{or}
unary_logic		       {not}





/*ESTRUTURAS*/

%%
{digit}		        printf("digit: %s, length: %d\n", yytext, yyleng);
{integer}           printf("integer number: %s, length: %d\n", yytext, yyleng);
{sum}               printf("sum: %s, length: %d\n", yytext, yyleng);
{float} 		    printf("float number: %s, length: %d\n", yytext, yyleng);
{comment}   		printf("comment: %s, length: %d\n", yytext, yyleng);
{open_bracket}		printf("open_bracket: %s, length: %d\n", yytext, yyleng);
{close_bracket}		printf("close_bracket: %s, length: %d\n", yytext, yyleng);
{open_par}	        printf("open_par: %s, length: %d\n", yytext, yyleng);
{close_par}	        printf("close_par: %s, length: %d\n", yytext, yyleng);
{operations}	    printf("operation: %s, length: %d\n", yytext, yyleng);
{math_logic}       	printf("math_logic: %s, length: %d\n", yytext, yyleng);
{binary_logic}  	printf("binary_logic: %s, length: %d\n", yytext, yyleng);
{unary_logic} 	    printf("unary_operator: %s, length: %d\n", yytext, yyleng);
{incr_operation}	printf("incr_operation: %s, length: %d\n", yytext, yyleng);
{decr_operation}   	printf("decr_operation: %s, length: %d\n", yytext, yyleng);
{string}		    printf("string: %s, length: %d\n", yytext, yyleng);
{characters}        printf("characters: %s, length: %d\n", yytext, yyleng);
.			        printf("NaN, length: %d\n", yyleng);
%%
