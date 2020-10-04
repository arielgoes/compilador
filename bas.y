%{
    #include <stdlib.h>
    #include "node.h"
    extern Node * syntax_tree;
    extern void yyerror(const char *);  /* prints grammar violation message */
%}
%token INCR DECR
%token GE LE EQ NE LT GT AND OR NOT
%token PRINTF
%token WHILE FOR IF ELSE ELIF BREAK CONTINUE RETURN
%token FLOAT INT CHAR VOID BOOL DOUBLE
%token CONSTANT
%token ID

%union{
    struct node* no;
    char* lexeme;
};

%right '='
%left AND OR
%left LE GE EQ NE LT GT
%left '+' '-'
%left '*' '/' 


%token<no> translation_unit       
%token<no> external               
%token<no> function               
%token<no> declaration            
%token<no> type                   
%token<no> assignment             
%token<no> functioncall           
%token<no> array_usage            
%token<no> id                     
%token<no> constant               
%token<no> incr                   
%token<no> decr                   
%token<no> float                  
%token<no> int                    
%token<no> char                   
%token<no> void                   
%token<no> bool                   
%token<no> double                 
%token<no> arg_list_opt           
%token<no> arg_list               
%token<no> arg                    
%token<no> compound_stmt          
%token<no> stmt_list              
%token<no> stmt                   
%token<no> while_stmt             
%token<no> for_stmt               
%token<no> if_stmt                
%token<no> print_func             
%token<no> jump_statement         
%token<no> while                  
%token<no> for                    
%token<no> if                     
%token<no> expr                   
%token<no> else_elif_stmt         
%token<no> elif                   
%token<no> else_stmt              
%token<no> else                   
%token<no> le                     
%token<no> ge                     
%token<no> ne                     
%token<no> eq                     
%token<no> gt                     
%token<no> lt                     
%token<no> and                    
%token<no> or                     
%token<no> continue               
%token<no> break                  
%token<no> return                 
%token<no> printf                 


%start translation_unit

%%


/* starting point for yacc */
translation_unit
	: external_declaration 
	| external_declaration translation_unit
	;

external_declaration
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
    | ID '%' assignment
    | CONSTANT '+' assignment
    | CONSTANT '-' assignment
    | CONSTANT '*' assignment
    | CONSTANT '/' assignment
    | CONSTANT '%' assignment
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
    : type ID '(' arg_list_opt ')' compound_stmt
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
    | jump_statement
    | ';'
    ;


/* Loop section */
while_stmt
    : WHILE '(' expr ')' compound_stmt
    ;

/* For section */
for_stmt
    : FOR '(' expr ';' expr ';' expr ')' compound_stmt
    | FOR '(' expr ')' compound_stmt
    ;

/* IfStmt Block */
if_stmt 
    : IF '(' expr ')' compound_stmt else_elif_stmt
    ;

else_elif_stmt
    : ELIF '(' expr ')' compound_stmt else_elif_stmt
    | else_stmt
    |
    ;

else_stmt
    : ELSE compound_stmt
    ;

/*expression Block*/
expr   
    : expr LE expr
    | expr GE expr
    | expr NE expr
    | expr EQ expr
    | expr GT expr 
    | expr LT expr
    | expr AND expr
    | expr OR expr
    | assignment
    | array_usage
    ;

/* Jump statements */
jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expr ';'
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
    printf("Parsing Completed!\n");
	return 0;
}