%{
    #include <stdlib.h>
    #include "node.h"
    extern Node * syntax_tree;
    extern void yyerror(const char *);  /* prints grammar violation message */
    extern int yylex();
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

%type<no> atree
%type<no> translation_unit       
%type<no> external_declaration               
%type<no> function               
%type<no> declaration            
%type<no> type                   
%type<no> assignment             
%type<no> function_call           
%type<no> array_usage            
%type<no> ID                     
%type<no> CONSTANT               
%type<no> INCR                   
%type<no> DECR                   
%type<no> FLOAT                  
%type<no> INT                    
%type<no> CHAR                   
%type<no> VOID                   
%type<no> BOOL                   
%type<no> DOUBLE                 
%type<no> arg_list_opt           
%type<no> arg_list               
%type<no> arg                    
%type<no> compound_stmt          
%type<no> stmt_list              
%type<no> stmt                   
%type<no> while_stmt             
%type<no> for_stmt               
%type<no> if_stmt                
%type<no> print_func             
%type<no> jump_statement         
%type<no> WHILE                  
%type<no> FOR                   
%type<no> IF                     
%type<no> expr                   
%type<no> else_elif_stmt         
%type<no> ELIF                   
%type<no> else_stmt              
%type<no> ELSE                   
%type<no> LE                     
%type<no> GE                     
%type<no> NE                     
%type<no> EQ                     
%type<no> GT                     
%type<no> LT                     
%type<no> AND                    
%type<no> OR                     
%type<no> CONTINUE               
%type<no> BREAK                  
%type<no> RETURN                 
%type<no> PRINTF                 


%start atree
%%

atree:
    translation_unit /*{print_node($1);}*/
    ; 

/* starting point for yacc */
translation_unit
	: external_declaration /*{$$ = $1;}*/
	| external_declaration translation_unit {$$=create_node(yylineno, translation_unit_node, NULL, $1, $2);}
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