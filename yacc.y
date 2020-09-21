%token INCR DECR IDENTIFIER CONSTANT 
%token GE LE EQ NE LT GT ASSIGNMENT AND OR NOT
%token OPEN_PAR CLOSE_PAR OPEN_BRACKET CLOSE_BRACKET SEMI_COLLON
%token QUOTE WHILE FOR IF ELSE BREAK CONTINUE RETURN SWITCH CASE DEFAULT
%token FLOAT INT CHAR VOID STRING_LITERAL BOOL DOUBLE

%right '='
%left AND OR
%left LE GE EQ NE LT GT

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
	: IDENTIFIER '=' assignment
	| IDENTIFIER '=' function_call
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
	: IDENTIFIER '(' assignment ')'
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
    | IDENTIFIER '(' assignment ')'
    ;

/* Function section */
function: type IDENTIFIER '(' ArgListOpt ')' CompoundStmt
    ;
ArgListOpt: ArgList
    |
    ;
ArgList:  ArgList ',' Arg
    | Arg
    ;
Arg:    Type ID
    ;
CompoundStmt:   '{' StmtList '}'
    ;
StmtList:   StmtList Stmt
    |
    ;
Stmt: WhileStmt
    | Declaration
    | ForStmt
    | IfStmt
    | PrintFunc
    | ';'
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