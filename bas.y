%error-verbose
%{
    #include <stdlib.h>
    #include "node.h"
    extern void yyerror(const char *);  /* prints grammar violation message */
    extern int yylex();
    extern int yylineno;
    extern Node* syntax_tree;
    char* floating = "float";
    char* integer = "int";
    char* doubling = "double";
%}

%union{
    struct node* no;
    char* lexeme;
};

%token INCR DECR
%token GE LE EQ NE LT GT AND OR NOT
%token PRINTF
%token WHILE FOR IF ELSE ELIF BREAK CONTINUE RETURN
%token FLOAT INT CHAR VOID BOOL DOUBLE
%token CONSTANT
%token ID

                
%type<no> atree
%type<no> translation_unit       
%type<no> external_declaration               
%type<no> function               
%type<no> declaration            
/*%type<no> type          */
%type<no> assignment             
%type<no> function_call           
%type<no> array_usage                            
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
%type<no> expr                   
%type<no> else_elif_stmt         
%type<no> else_stmt              

%right '='
%left AND OR
%left LE GE EQ NE LT GT
%left '+' '-'
%left '*' '/'  


%start atree
%%

atree
    :translation_unit {$$ = $1; syntax_tree = $$;}
    ; 

/* starting point for yacc */
translation_unit
    : external_declaration {$$ = $1;}
    | external_declaration translation_unit {$$=create_node(yylineno, translation_unit_node, "external_declaration translation_unit", $1, $2);}
    ;

external_declaration
    : function { $$ = create_node(yylineno, external_declaration_node, "function", $1); }
    | declaration { $$ = create_node(yylineno, external_declaration_node, "declaration", $1); }
    ;

/* Declaration section */
declaration
    : type assignment ';'   {Node* semicollon = (Node*)malloc(sizeof(Node));
                            semicollon->lexeme = ";";
                            $$ = create_node(yylineno, declaration_node, "type assignment ;", $1, $2, semicollon);}
    | assignment ';'        {Node* semicollon = (Node*)malloc(sizeof(Node));
                            semicollon->lexeme = ";";
                            $$ = create_node(yylineno, declaration_node, "assignment ;", $1, semicollon);}
    | function_call ';'     {Node* semicollon = (Node*)malloc(sizeof(Node));
                            semicollon->lexeme = ";";
                            $$ = create_node(yylineno, declaration_node, "function_call ;", $1, semicollon);} 
    | array_usage ';'       {Node* semicollon = (Node*)malloc(sizeof(Node));
                            semicollon->lexeme = ";";
                            $$ = create_node(yylineno, declaration_node, "array_usage ;", $1, semicollon);}
    | type array_usage ';'  {Node* semicollon = (Node*)malloc(sizeof(Node));
                            semicollon->lexeme = ";";
                            $$ = create_node(yylineno, declaration_node, "assignment ;", $1, $2, semicollon);}
    ;

/* Assignment section */
assignment
    : ID '=' assignment         {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* float = create_node(yylineno, float_node, "FLOAT", NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = assignment", float, eq, $3);}
    | ID '=' function_call      { Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                $$ = create_node(yylineno, eq_node, "ID = function_call", $1, eq, $3);}
    | array_usage '=' assignment    { Node* eq = (Node *)malloc(sizeof(Node));
                                    eq->lexeme = "=";
                                    $$ = create_node(yylineno, assignment_node, "array_usage = assignment", $1, eq, $3);}
    | ID ',' assignment         {Node* collon = (Node *)malloc(sizeof(Node));
                                collon->lexeme = ",";
                                $$ = create_node(yylineno, assignment_node, "ID , assignment", $1, collon, $3);}
    | CONSTANT ',' assignment   {Node* collon = (Node *)malloc(sizeof(Node));
                                collon->lexeme = ",";
                                $$ = create_node(yylineno, assignment_node, "CONSTANT, assignment", $1, collon, $3);}
    | ID '+' assignment     {Node* sum = (Node *)malloc(sizeof(Node));
                            sum->lexeme = "+";
                            Node* id = (Node *)malloc(sizeof(Node));
                            id->lexeme = "ID";
                            $$ = create_node(yylineno, assignment_node, "ID + assignment", id, sum, $3);}

    | ID '-' assignment     {Node* id = (Node *)malloc(sizeof(Node));
                            id->lexeme = "ID"; 
                            Node* sub = (Node *)malloc(sizeof(Node));
                            sub->lexeme = "-";
                            $$ = create_node(yylineno, assignment_node, "ID - assignment", id, sub, $3);}

    | ID '*' assignment     {Node* id = (Node *)malloc(sizeof(Node));
                            id->lexeme = "ID";
                            Node* mult = (Node *)malloc(sizeof(Node));
                            mult->lexeme = "*";
                            $$ = create_node(yylineno, assignment_node, "ID * assignment", id, mult, $3);}

    | ID '/' assignment     {Node* id = (Node *)malloc(sizeof(Node));
                            id->lexeme = "ID"; 
                            Node* div = (Node *)malloc(sizeof(Node));
                            div->lexeme = "/";
                            $$ = create_node(yylineno, assignment_node, "ID / assignment", id, div, $3);}

    | ID '%' assignment     {Node* id = (Node *)malloc(sizeof(Node));
                            id->lexeme = "ID";
                            Node* mod = (Node *)malloc(sizeof(Node));
                            mod->lexeme = "%";
                            $$ = create_node(yylineno, assignment_node, "ID % assignment", id, mod, $3);}

    | CONSTANT '+' assignment       {Node* sum = (Node *)malloc(sizeof(Node));
                                    sum->lexeme = "+";
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT + assignment", $1, sum, $3);}
    | CONSTANT '-' assignment       {Node* sub = (Node *)malloc(sizeof(Node));
                                    sub->lexeme = "-";
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT - assignment", $1, sub, $3);}
    | CONSTANT '*' assignment       {Node* mult = (Node *)malloc(sizeof(Node));
                                    mult->lexeme = "*";
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT * assignment", $1, mult, $3);}
    | CONSTANT '/' assignment       {Node* div = (Node *)malloc(sizeof(Node));
                                    div->lexeme = "/";
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT / assignment", $1, div, $3);} 
    | CONSTANT '%' assignment       {Node* mod = (Node *)malloc(sizeof(Node));
                                    mod->lexeme = "%";
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT % assignment", $1, mod, $3);}

    | ID INCR   {Node* id = create_node(yylineno, id_node, "ID", NULL); 
                $$ = create_node(yylineno, assignment_node, "ID INCR", id, $2);}

    | ID DECR   {Node* id = create_node(yylineno, id_node, "ID", NULL);
                $$ = create_node(yylineno, assignment_node, "ID DECR", id, $2);}

    | '(' assignment ')'    {Node* open_brac = (Node *)malloc(sizeof(Node));
                            open_brac->lexeme = "(";
                            Node* close_brac = (Node *)malloc(sizeof(Node));
                            close_brac->lexeme = ")";
                            $$ = create_node(yylineno, assignment_node, "( assignment )", open_brac, $2, close_brac);}
    | '-' '(' assignment ')'    {Node* sub = (Node *)malloc(sizeof(Node));
                                sub->lexeme = "-";
                                Node* open_brac = (Node*)malloc(sizeof(Node));
                                open_brac->lexeme = "(";
                                Node* close_brac = (Node *)malloc(sizeof(Node));
                                close_brac->lexeme = "(";
                                $$ = create_node(yylineno, assignment_node, "( assignment )", sub, open_brac, $3, close_brac);}
    | '-' CONSTANT {Node* sub = (Node*)malloc(sizeof(Node));
                    sub->lexeme = "-";
                    $$ = create_node(yylineno, assignment_node, "- CONSTANT", sub, $2);}
    | '-' ID        {Node* sub = (Node*)malloc(sizeof(Node));
                    sub->lexeme = "-";
                    $$ = create_node(yylineno, assignment_node, "- ID", sub, $2);} 
    | CONSTANT  {$$ = create_node(yylineno, assignment_node, "CONSTANT", $1);}
    | ID        {$$ = create_node(yylineno, assignment_node, "ID", $1);}
    ;

/* Array usage */
array_usage
    : ID '[' assignment ']' {Node* open_sqr_brac = (Node *)malloc(sizeof(Node));
                            open_sqr_brac->lexeme = "[";
                            Node* close_sqr_brac = (Node *)malloc(sizeof(Node));
                            close_sqr_brac->lexeme = "]";
                            $$ = create_node(yylineno, array_usage_node, "ID [ assignment ]", $1, open_sqr_brac, $3, close_sqr_brac);}
    ;

/* Type section (does not include string yet) */
type
    : FLOAT     {$$ = floating;}
    | INT       {$$ = $1;}
    | CHAR      {$$ = create_node(yylineno, type_node, "CHAR", NULL);}
    | VOID      {$$ = create_node(yylineno, type_node, "VOID", NULL);}
    | BOOL      {$$ = create_node(yylineno, type_node, "BOOL", NULL);}
    | DOUBLE    {$$ = doubling;}
    ;

/* Function call section */
function_call
    : ID '(' ')'                {Node* open_brac = (Node *)malloc(sizeof(Node));
                                open_brac->lexeme = "(";
                                Node* close_brac = (Node *)malloc(sizeof(Node));
                                close_brac->lexeme = ")";
                                $$ = create_node(yylineno, function_call_node, "ID ( )", $1, open_brac, close_brac);}

    | ID '(' assignment ')'     {Node* open_brac = (Node *)malloc(sizeof(Node));
                                open_brac->lexeme = "(";
                                Node* close_brac = (Node *)malloc(sizeof(Node));
                                close_brac->lexeme = ")";
                                $$ = create_node(yylineno, function_call_node, "ID ( assignment )", $1, open_brac, $3, close_brac);}
    ;

/* Function section */
function
    : type ID '(' arg_list_opt ')' compound_stmt    {Node* open_brac = (Node *)malloc(sizeof(Node));
                                                    open_brac->lexeme = "(";
                                                    Node* close_brac = (Node *)malloc(sizeof(Node));
                                                    close_brac->lexeme = ")";
                                                    $$ = create_node(yylineno, function_node, "type ID ( arg_list_opt ) compound_stmt", 
                                                    $1, $2, open_brac, $4, close_brac, $6);}  
    ;

arg_list_opt
    : arg_list  {$$ = create_node(yylineno, arg_list_opt_node, "arg_list", $1);}
    |           {$$ = create_node(yylineno, arg_list_opt_node, "arg_list_opt --> EMPTY", NULL);}
    ;

arg_list
    : arg_list ',' arg  {Node* collon = (Node *)malloc(sizeof(Node));
                        collon->lexeme = ",";
                        $$ = create_node(yylineno, arg_list_node, "arg_list , arg", $1, collon, $3);}

    | arg               {$$ = create_node(yylineno, arg_list_node, "arg", $1);}
    ;
    
arg
    : type ID   {$$ = create_node(yylineno, arg_node, "type ID", $1, $2);}
    ;

compound_stmt
    : '{' stmt_list '}' {Node* open_curly_brac = (Node *)malloc(sizeof(Node));
                        open_curly_brac->lexeme = "{";
                        Node* close_curly_brac = (Node *)malloc(sizeof(Node));
                        close_curly_brac->lexeme = "}";
                        $$ = create_node(yylineno, compound_stmt_node, "{ stmt_list }", open_curly_brac, $2, close_curly_brac);}
    ;

stmt_list
    : stmt_list stmt    {$$ = create_node(yylineno, stmt_list_node, "stmt_list stmt", $1, $2);}
    |                   {$$ = create_node(yylineno, stmt_list_node, "stmt_list --> EMPTY", NULL);}
    ;
    
stmt
    : while_stmt        {$$ = create_node(yylineno, stmt_node, "while_stmt", $1);}
    | declaration       {$$ = create_node(yylineno, stmt_node, "declaration", $1);}
    | for_stmt          {$$ = create_node(yylineno, stmt_node, "for_stmt", $1);} 
    | if_stmt           {$$ = create_node(yylineno, stmt_node, "if_stmt", $1);}  
    | print_func        {$$ = create_node(yylineno, stmt_node, "print_func", $1);} 
    | jump_statement    {$$ = create_node(yylineno, stmt_node, "jump_statement", $1);} 
    | ';'               {Node* semicollon = (Node *)malloc(sizeof(Node));
                        semicollon->lexeme = ";";
                        $$ = create_node(yylineno, stmt_node, ";", semicollon);}
    ;


/* Loop section */
while_stmt
    : WHILE '(' expr ')' compound_stmt  {Node* open_brac = (Node *)malloc(sizeof(Node));
                                        open_brac->lexeme = "(";
                                        Node* close_brac = (Node *)malloc(sizeof(Node));
                                        close_brac->lexeme = ")";
                                        $$ = create_node(yylineno, while_stmt_node, "WHILE ( expr ) compound_stmt",
                                        $1, open_brac, $3, close_brac, $5);}
    ;

/* For section */
for_stmt
    : FOR '(' expr ';' expr ';' expr ')' compound_stmt  {Node* semicollon1 = (Node *)malloc(sizeof(Node));
                                                        semicollon1->lexeme = ";";
                                                        Node* semicollon2 = (Node *)malloc(sizeof(Node));
                                                        semicollon2->lexeme = ";";
                                                        Node* open_brac = (Node *)malloc(sizeof(Node));
                                                        open_brac->lexeme = "(";
                                                        Node* close_brac = (Node *)malloc(sizeof(Node));
                                                        close_brac->lexeme = ")";
                                                        $$ = create_node(yylineno, for_stmt_node, "FOR ( expr ; expr ; expr ) compound_stmt",
                                                        $1, open_brac, $3, semicollon1, $5, semicollon2, $7, close_brac, $9);}

    | FOR '(' expr ')' compound_stmt    {Node* open_brac = (Node *)malloc(sizeof(Node));
                                        open_brac->lexeme = "(";
                                        Node* close_brac = (Node *)malloc(sizeof(Node));
                                        close_brac->lexeme = ")";
                                        $$ = create_node(yylineno, for_stmt_node, "FOR ( expr ) compound_stmt", 
                                        $1, open_brac, $3, close_brac, $5);}
    ;

/* IfStmt Block */
if_stmt 
    : IF '(' expr ')' compound_stmt else_elif_stmt  {Node* open_brac = (Node *)malloc(sizeof(Node));
                                                    open_brac->lexeme = "(";
                                                    Node* close_brac = (Node *)malloc(sizeof(Node));
                                                    close_brac->lexeme = ")";
                                                    $$ = create_node(yylineno, if_stmt_node, "IF ( expr ) compound_stmt else_elif_stmt", 
                                                    $1, open_brac, $3, close_brac, $5, $6);} 
    ;

else_elif_stmt
    : ELIF '(' expr ')' compound_stmt else_elif_stmt    {Node* open_brac = (Node *)malloc(sizeof(Node));
                                                        open_brac->lexeme = "(";
                                                        Node* close_brac = (Node *)malloc(sizeof(Node));
                                                        close_brac->lexeme = ")";
                                                        $$ = create_node(yylineno, else_elif_stmt_node, "ELIF '(' expr ')' compound_stmt else_elif_stmt",
                                                        $1, open_brac, $3, close_brac, $5, $6);}

    | else_stmt {$$ = create_node(yylineno, else_elif_stmt_node, "else_stmt", $1);}                          
    |           {$$ = create_node(yylineno, else_elif_stmt_node, "else_stmt --> EMPTY", NULL);}
    ;

else_stmt
    : ELSE compound_stmt    {$$ = create_node(yylineno, else_stmt_node, "ELSE compound_stmt", $1, $2);}
    ;

/*expression Block*/
expr   
    : expr relop expr  {$$ = create_node(yylineno, expr_node, "expr relop expr", $1, $2, $3);}
    | assignment    {$$ = create_node(yylineno, expr_node, "assignment", $1);}
    | array_usage   {$$ = create_node(yylineno, expr_node, "array_usage", $1);}
    ;

relop
    : LE    {$$ = create_node(yylineno, le_node, "LE", NULL);}
    | GE    {$$ = $1;} 
    | NE    {$$ = "!=";}
    | EQ    {$$ = "==";}
    | GT    {$$ = ">";}
    | LT    {$$ = "<";}
    | AND   {$$ = "&&";}
    | OR    {$$ = "||";}
    ;

/* Jump statements */
jump_statement
    : CONTINUE ';'  {Node* semicollon = (Node *)malloc(sizeof(Node));
                    semicollon->lexeme = ";";
                    $$ = create_node(yylineno, jump_statement_node, "CONTINUE ;", $1, semicollon);}

    | BREAK ';'     {Node* semicollon = (Node *)malloc(sizeof(Node));
                    semicollon->lexeme = ";";
                    $$ = create_node(yylineno, jump_statement_node, "BREAK ;", $1, semicollon);}

    | RETURN ';'    {Node* semicollon = (Node *)malloc(sizeof(Node));
                    semicollon->lexeme = ";";
                    $$ = create_node(yylineno, jump_statement_node, "RETURN ;", $1, semicollon);}

    | RETURN expr ';'   {Node* semicollon = (Node *)malloc(sizeof(Node));
                        semicollon->lexeme = ";";
                        $$ = create_node(yylineno, jump_statement_node, "RETURN expr ;", $1, $2, semicollon);}
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