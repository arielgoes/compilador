%{
    #define YYDEBUG 1
%}

%token INCR DECR ID CONSTANT PRINTF
%token GE LE EQ NE LT GT ASSIGNMENT AND OR NOT
%token WHILE FOR IF ELSE BREAK CONTINUE RETURN
%token FLOAT INT CHAR VOID BOOL DOUBLE

%right '='
%left AND OR
%left LE GE EQ NE LT GT
%left '+' '-'
%left '*' '/' 

%start begin

%%

/* starting point for yacc */
begin
	: function
	| declaration
	;

/* Declaration section */
declaration
	: type assignment ';'
	| assignment ';'
	| function_call ';'
	| array_usage ';'
	| type array_usage ';'
	;

/* Assignment section */
assignment
	: ID '=' assignment
	| ID '=' function_call
	| array_usage '=' assignment
    | ID ',' assignment
    | CONSTANT ',' assignment
    | ID '+' assignment
    | ID '-' assignment
    | ID '*' assignment
    | ID '/' assignment
    | CONSTANT '+' assignment
    | CONSTANT '-' assignment
    | CONSTANT '*' assignment
    | CONSTANT '/' assignment
    | ID INCR
    | ID DECR
    | '\'' assignment '\''
    | '(' assignment ')'
    | '-' '(' assignment ')'
    | '-' CONSTANT
    | '-' ID
    | CONSTANT
    | ID
    ;

/* Array usage */
array_usage
	: ID '[' assignment ']'
	;

/* Type section (does not include string yet) */
type
	: FLOAT
	| INT
	| CHAR
	| VOID
	| BOOL
	| DOUBLE
	;

/* Function call section */
function_call : ID '(' ')'
    | ID '(' assignment ')'
    ;

/* Function section */
function
    :type ID '(' arg_list_opt ')' compound_stmt
    ;

arg_list_opt
    : arg_list
    |
    ;

arg_list
    : arg_list ',' arg
    | arg
    ;
    
arg
    : type ID
    ;

compound_stmt
    : '{' stmt_list '}'
    ;

stmt_list
    : stmt_list stmt
    |
    ;
    
stmt
    : while_stmt
    | declaration
    | for_stmt
    | if_stmt
    | print_func
    | ';'
    ;

/* Loop section */
while_stmt
    : WHILE '(' expr ')' stmt
    | WHILE '(' expr ')' compound_stmt
    ;

/* For section */
for_stmt
    : FOR '(' expr ';' expr ';' expr ')' stmt
    | FOR '(' expr ';' expr ';' expr ')' compound_stmt
    | FOR '(' expr ')' stmt
    | FOR '(' expr ')' compound_stmt
    ;

/* IfStmt Block */
if_stmt 
    : IF '(' expr ')'
    | IF '(' expr ')' compound_stmt
    ;

/*expression Block*/
expr   
    : expr LE expr
    | expr GE expr
    | expr NE expr
    | expr EQ expr
    | expr GT expr
    | expr LT expr
    | assignment
    | array_usage
    ;

/* Print Function */
print_func 
    : PRINTF '(' expr ')' ';'
    ;
%%

#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int main(void) {
	yyparse();
	return 0;
}