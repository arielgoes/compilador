
%{
#include <stdio.h>
#include <stdlib.h>

%}

/*NÚMEROS*/

digit      	  [0-9]
integer       {digit}+
float    	    {integer}"."{integer}

/*CARACTERES ESPECIAS*/
comment 	    "#"{characters}"#"
sum		        "+"
sub		        "-"
mult		      "*"
div		        "/"
incr 		      "++"
decr 		      "--"
greater		    ">"
smaller		    "<"
greater_equal ">="
smaller_equal "<="
equal		      "=="
diff		      "/="
and		        "&&"
or		        "||"
not		        "!"
open_par	    "\("
close_par	    "\)"
open_bracket	"{"
close_bracket	"}"
quote		      "\""
if		        "if"
while		      "while"
for		        "for"
space		      "\n"|" "|"\t"

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
unitary_logic		  {not}





/*ESTRUTURAS*/

%%
{digit}		          printf("digit: %s\n", yytext);
{integer}           printf("integer number: %s\n", yytext);
{sum}               printf("sum: %s\n", yytext);
{float} 		        printf("float number: %s\n", yytext);
{comment}   		    printf("comment: %s\n", yytext);
{open_bracket}		  printf("open_bracket: %s\n", yytext);
{close_bracket}		  printf("close_bracket: %s\n", yytext);
{open_par}	        printf("open_par: %s\n", yytext);
{close_par}	        printf("close_par: %s\n", yytext);
{operations}	      printf("operation: %s\n", yytext);
{math_logic}       	printf("logica_matematicas: %s\n", yytext);
{binary_logic}  	  printf("logica_binary: %s\n", yytext);
{unitary_logic} 	  printf("logica_unitaria: %s\n", yytext);
{incr_operation}	  printf("operacao_incremento: %s\n", yytext);
{decr_operation}   	printf("operacao_decremento: %s\n", yytext);
{string}		        printf("string: %s\n", yytext);
{characters}        printf("characters: %s\n", yytext);

.			              printf("NaN\n");
%%
