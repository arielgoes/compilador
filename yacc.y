%token COMMENT INCR DECR GREATER SMALLER
%token GREATER_EQUAL SMALLER_EQUAL EQUAL DIFF ASSIGNMENT AND OR
%token OPEN_PAR CLOSE_PAR OPEN_BRACKET CLOSE_BRACKET SEMI_COLLON
%token QUOTE WHILE FOR IF ELSE BREAK CONTINUE RETURN SWITCH CASE
%token DEFAULT FLOAT INT CHAR VOID STRING_LITERALL CONSTANT BOOL

%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	| '(' expression ')'
	;


postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression INCR
	| postfix_expression DECR
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
    : postfix_expression
    | INCR unary_expression
    | DECR unary_expression
    | NOT cast_expression
    ;

unary_operator 
    : '&' 
    | '*'
    | '+' 
    | '-'  
    | '!'
    ;

assignment_operator
        : '='
        ;

type_specifier
        : INT
        | FLOAT
        | CHAR
        | VOID
        | BOOL
        ;
        
jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;


multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;



%%


#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
