%error-verbose
%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "node.h"
    #include "symbol_table.h"
    #include "lista.h"
    
    #define UNDEFINED_TYPE -9999
    #define FLOAT_TYPE 1
    #define INT_TYPE 2
    #define CHAR_TYPE 3
    #define DOUBLE_TYPE 4

    #define FLOAT_SIZE 4
    #define INT_SIZE 4
    #define CHAR_SIZE 1
    #define DOUBLE_SIZE 8

    extern void yyerror(const char *);  /* prints grammar violation message */
    extern int yylineno;
    extern Node* syntax_tree;
    extern symbol_t symbol_table;

    //extern char yytext[];
    extern int column;

    void yyerror(char const *s){
        fflush(stdout);
        printf("\n%*s\n%*s\n", column, "^", column, s);
    }

    int vars_size = 0;
    int tipo_global = 0;


    char* tac_arg1 = "tac_arg1";
    char* tac_arg2 = "tac_arg2";
    char* tac_op = "tac_op";
    int isTac = 0;
    
    void create_table_entry(char* lexeme){
        if(lookup(symbol_table, lexeme)){
            printf("'%s' symbol defined multiple times. Type: %d.\n", lexeme, tipo_global);
            return;
        }else{
            entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
            printf("\n>>>> New symbol on table: %s, type: %d", lexeme, tipo_global);
            new_entry->name = lexeme;
            switch(tipo_global){
                case FLOAT_TYPE: 
                    vars_size += FLOAT_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = FLOAT_SIZE;
                    new_entry->desloc = vars_size;
                    break; 
                case INT_TYPE:
                    vars_size += INT_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = INT_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                case CHAR_TYPE:
                    vars_size += CHAR_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = CHAR_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                case DOUBLE_TYPE:
                    vars_size += DOUBLE_SIZE;
                    new_entry->type = tipo_global;
                    new_entry->size = DOUBLE_SIZE;
                    new_entry->desloc = vars_size;
                    break;
                default:
                    printf("\n>>>> ERROR: Undefined type '%s' ^\n", lexeme);
                    exit(0);
            }

            if(insert(&symbol_table, new_entry) == -1){
                printf("\n>>>> insert table: ERROR! Cannot allocate %s into 'symbol_table'!\n", lexeme);
                exit(0);
            }else{
                printf("\n>>>> insert table: SUCCESS! value: %s\n", lexeme);
            }

        }
    }

%}

%union{
    struct node* no;
    char *str; 
};

%token <no> WHILE FOR IF ELSE ELIF BREAK CONTINUE RETURN PRINTF
%token <str> FLOAT INT CHAR VOID DOUBLE ID CONSTANT INCR DECR GE LE EQ NE LT GT AND OR NOT
                
%type<no> atree
%type<no> translation_unit       
%type<no> external_declaration               
%type<no> function               
%type<no> declaration
%type<no> declaration_assignment            
%type<no> assignment             
%type<no> function_call           
%type<no> array_usage
%type<no> declaration_array_usage                            
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

%type<str> type relop

%right '='
%left AND OR
%left LE GE EQ NE LT GT
%left '+' '-'
%left '*' '/'  


%start atree
%%

atree
    :translation_unit {$$ = create_node(yylineno, atree_node, "atree", $1, NULL); syntax_tree = $$;
    uncompile(stdout, $1);}
    ;

/* starting point for yacc */
translation_unit
    : external_declaration {$$ = create_node(yylineno, translation_unit_node, "external_declaration", $1, NULL);}
    | external_declaration translation_unit {$$=create_node(yylineno, translation_unit_node, "external_declaration translation_unit", $1, $2, NULL);}
    ;

external_declaration
    : function { $$ = create_node(yylineno, external_declaration_node, "function", $1, NULL); }
    | declaration { $$ = create_node(yylineno, external_declaration_node, "declaration", $1, NULL); }
    ;

/* Declaration section */
declaration
    : type declaration_assignment ';'   {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "type assignment ;", $1, $2, semicollon, NULL);}
    | assignment ';'                    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "assignment ;", $1, semicollon, NULL);}
    | function_call ';'                 {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "function_call ;", $1, semicollon, NULL);} 
    | array_usage ';'                   {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "array_usage ;", $1, semicollon, NULL);}
    | type declaration_array_usage ';'  {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "assignment ;", $1, $2, semicollon, NULL);}
    ;


/* Declaration followed by assignment */
declaration_assignment
    : ID '=' assignment         {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, "ID", NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = assignment", id, eq, $3, NULL);
                                create_table_entry($1);
                                if(isTac == 1){
                                    struct tac* new_tac = create_inst_tac((char *)$1, tac_arg1, tac_op, tac_arg2);
                                    isTac = 0;
                                }}
    | ID '=' function_call      {Node* eq = create_node(yylineno, eq_node, "=", NULL, NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = function_call", $1, eq, $3, NULL);
                                create_table_entry($1);}
    | ID                        {$$ = create_node(yylineno, assignment_node, "ID", $1, NULL);
                                create_table_entry($1);}
    ;                             


/* Assignment section */
assignment
    : ID '=' assignment         {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, "ID", NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = assignment", id, eq, $3, NULL);
                                if(isTac == 1){
                                    struct tac* new_tac = create_inst_tac((char *)$1, tac_arg1, tac_op, tac_arg2);
                                    isTac = 0;
                                }}
    | ID '=' function_call      {Node* eq = create_node(yylineno, eq_node, "=", NULL, NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = function_call", $1, eq, $3, NULL);
                                isTac = 0;}
    | array_usage '=' assignment    {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                    $$ = create_node(yylineno, assignment_node, "array_usage = assignment", $1, eq, $3, NULL);
                                    isTac = 0;}
    | CONSTANT ',' assignment   {Node* collon = create_node(yylineno, collon_node, ",", NULL);
                                $$ = create_node(yylineno, assignment_node, "CONSTANT, assignment", $1, collon, $3, NULL);
                                isTac = 0;}
    | ID '+' assignment     {Node* sum = create_node(yylineno, sum_node, "+", NULL);
                            tac_arg1 = (char*)$1;
                            tac_op = "+";
                            isTac = 1;
                            $$ = create_node(yylineno, assignment_node, "ID + assignment", $1, sum, $3, NULL);}

    | ID '-' assignment     {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                            tac_arg1 = (char*)$1;
                            tac_op = "-";
                            isTac = 1;
                            $$ = create_node(yylineno, assignment_node, "ID - assignment", $1, sub, $3, NULL);}

    | ID '*' assignment     {Node* mult = create_node(yylineno, mult_node, "*", NULL);
                            tac_arg1 = (char*)$1;
                            tac_op = "*";
                            isTac = 1;
                            $$ = create_node(yylineno, assignment_node, "ID * assignment", $1, mult, $3, NULL);}

    | ID '/' assignment     {Node* mult = create_node(yylineno, div_node, "/", NULL);
                            tac_arg1 = (char*)$1;
                            tac_op = "/";
                            isTac = 1;
                            $$ = create_node(yylineno, assignment_node, "ID / assignment", $1, div, $3, NULL);}

    | ID '%' assignment     {Node* mod = create_node(yylineno, mod_node, "%", NULL);
                            tac_arg1 = (char*)$1;
                            tac_op = "%";
                            isTac = 1;
                            $$ = create_node(yylineno, assignment_node, "ID % assignment", $1, mod, $3, NULL);}

    | CONSTANT '+' assignment       {Node* sum = create_node(yylineno, sum_node, "+", NULL);
                                    tac_arg1 = (char*)$1;
                                    tac_op = "+";
                                    isTac = 1;
                                    $$ = create_node(yylineno, assignment_node, "teste", $1, sum, $3, NULL);}
    | CONSTANT '-' assignment       {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                                    tac_arg1 = (char*)$1;
                                    tac_op = "-";
                                    isTac = 1;
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT - assignment", $1, sub, $3), NULL;}
    | CONSTANT '*' assignment       {Node* mult = create_node(yylineno, mult_node, "*", NULL);
                                    tac_arg1 = (char*)$1;
                                    tac_op = "*";
                                    isTac = 1;
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT * assignment", $1, mult, $3, NULL);}
    | CONSTANT '/' assignment       {Node* div = create_node(yylineno, div_node, "/", NULL);
                                    tac_arg1 = (char*)$1;
                                    tac_op = "/";
                                    isTac = 1;
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT / assignment", $1, div, $3, NULL);} 
    | CONSTANT '%' assignment       {Node* mod = create_node(yylineno, mod_node, "%", NULL);
                                    tac_arg1 = (char*)$1;
                                    tac_op = "%";
                                    isTac = 1;
                                    $$ = create_node(yylineno, assignment_node, "CONSTANT % assignment", $1, mod, $3, NULL);
                                    }

    | ID INCR   {$$ = create_node(yylineno, assignment_node, "ID INCR", $1, $2, NULL);
                struct tac* new_tac = create_inst_tac((char *)$1, (char *)$1, "+", "1");
                isTac = 0;}

    | ID DECR   {$$ = create_node(yylineno, assignment_node, "ID DECR", $1, $2, NULL);
                struct tac* new_tac = create_inst_tac((char *)$1, (char *)$1, "-", "1");
                isTac = 0;}

    | '(' assignment ')'    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                            Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                            $$ = create_node(yylineno, assignment_node, "( assignment )", open_round_brac, $2, close_round_brac, NULL);
                            isTac = 0;}
    | '-' '(' assignment ')'    {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                                Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                $$ = create_node(yylineno, assignment_node, "( assignment )", sub, open_round_brac, $3, close_round_brac, NULL);
                                isTac = 0;}
    | '-' CONSTANT  {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                    $$ = create_node(yylineno, assignment_node, "- CONSTANT", sub, $2, NULL);
                    isTac = 0;}
    | '-' ID        {Node* sub = (Node*)malloc(sizeof(Node));
                    $$ = create_node(yylineno, assignment_node, "- ID", sub, $2, NULL);
                    isTac = 0;} 
    | CONSTANT  {$$ = create_node(yylineno, assignment_node, (char *)$1, $1, NULL);
                tac_arg2 = (char *)$1;
                isTac = 0;}
    | ID        {$$ = create_node(yylineno, assignment_node, (char *)$1, $1, NULL);
                tac_arg2 = (char *)$1;
                isTac = 0;}
    ;

/* Array usage */
array_usage
    : ID '[' assignment ']' {Node* open_sqr_brac = create_node(yylineno, open_sqr_brac_node, "[", NULL);
                            Node* close_sqr_brac = create_node(yylineno, close_sqr_brac_node, "]", NULL);
                            $$ = create_node(yylineno, array_usage_node, "ID [ assignment ]", $1, open_sqr_brac, $3, close_sqr_brac, NULL);}
    ;

declaration_array_usage
    : ID '[' assignment ']' {Node* open_sqr_brac = create_node(yylineno, open_sqr_brac_node, "[", NULL);
                            Node* close_sqr_brac = create_node(yylineno, close_sqr_brac_node, "]", NULL);
                            $$ = create_node(yylineno, array_usage_node, "ID [ assignment ]", $1, open_sqr_brac, $3, close_sqr_brac, NULL);
                            create_table_entry($1);}
    ;

/* Type section (does not include string yet) */
type
    : FLOAT     {$$ = create_node(yylineno, type_node, "FLOAT", $1, NULL);
                tipo_global = FLOAT_TYPE;}
    | INT       {$$ = create_node(yylineno, type_node, "INT", $1, NULL);
                tipo_global = INT_TYPE;}
    | CHAR      {$$ = create_node(yylineno, type_node, "CHAR", $1, NULL);
                tipo_global = CHAR_TYPE;}
    | VOID      {$$ = create_node(yylineno, type_node, "VOID", $1, NULL);
                tipo_global = 0;}
    | DOUBLE    {$$ = create_node(yylineno, type_node, "DOUBLE", $1, NULL);
                tipo_global = DOUBLE_TYPE;}
    ;

/* Function call section */
function_call
    : ID '(' ')'                {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                $$ = create_node(yylineno, function_call_node, "ID ( )", $1, open_round_brac, close_round_brac, NULL);}

    | ID '(' assignment ')'     {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                $$ = create_node(yylineno, function_call_node, "ID ( assignment )", $1, open_round_brac, $3, close_round_brac, NULL);}
    ;

/* Function section */
function
    : type ID '(' arg_list_opt ')' compound_stmt    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                    Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                    Node* id = create_node(yylineno, id_node, "ID", NULL);
                                                    $$ = create_node(yylineno, function_node, "type ID ( arg_list_opt ) compound_stmt", 
                                                    $1, id, open_round_brac, $4, close_round_brac, $6, NULL);}  
    ;

arg_list_opt
    : arg_list  {$$ = create_node(yylineno, arg_list_opt_node, "arg_list", $1, NULL);}
    |           {$$ = create_node(yylineno, arg_list_opt_node, "arg_list_opt --> EMPTY", NULL);}
    ;

arg_list
    : arg_list ',' arg  {Node* collon = create_node(yylineno, collon_node, ",", NULL);
                        $$ = create_node(yylineno, arg_list_node, "arg_list , arg", $1, collon, $3, NULL);}

    | arg               {$$ = create_node(yylineno, arg_list_node, "arg", $1, NULL);}
    ;
    
arg
    : type ID   {Node* id = create_node(yylineno, id_node, "ID", NULL);
                $$ = create_node(yylineno, arg_node, "type ID", $1, id, NULL);
                create_table_entry($2);}
    ;

compound_stmt
    : '{' stmt_list '}' {Node* open_curly_brac = create_node(yylineno, open_curly_brac_node, "{", NULL);
                        Node* close_curly_brac = create_node(yylineno, close_curly_brac_node, "}", NULL);
                        $$ = create_node(yylineno, compound_stmt_node, "{ stmt_list }", open_curly_brac, $2, close_curly_brac, NULL);}
    ;

stmt_list
    : stmt_list stmt    {$$ = create_node(yylineno, stmt_list_node, "stmt_list stmt", $1, $2, NULL);}
    |                   {$$ = create_node(yylineno, stmt_list_node, "stmt_list --> EMPTY", NULL);}
    ;
    
stmt
    : while_stmt        {$$ = create_node(yylineno, stmt_node, "while_stmt", $1, NULL);}
    | declaration       {$$ = create_node(yylineno, stmt_node, "declaration", $1, NULL);}
    | for_stmt          {$$ = create_node(yylineno, stmt_node, "for_stmt", $1, NULL);} 
    | if_stmt           {$$ = create_node(yylineno, stmt_node, "if_stmt", $1, NULL);}  
    | print_func        {$$ = create_node(yylineno, stmt_node, "print_func", $1, NULL);} 
    | jump_statement    {$$ = create_node(yylineno, stmt_node, "jump_statement", $1, NULL);}
    | ';'               {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                        $$ = create_node(yylineno, stmt_node, ";", semicollon, NULL);}
    ;


/* Loop section */
while_stmt
    : WHILE '(' expr ')' compound_stmt  {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, "(", NULL);
                                        $$ = create_node(yylineno, while_stmt_node, "WHILE ( expr ) compound_stmt",
                                        $1, open_round_brac, $3, close_round_brac, $5, NULL);}
    ;

/* For section */
for_stmt
    : FOR '(' expr ';' expr ';' expr ')' compound_stmt  {Node* semicollon1 = create_node(yylineno, semicollon_node, ";", NULL);
                                                        Node* semicollon2 = create_node(yylineno, semicollon_node, ";", NULL);
                                                        Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                        $$ = create_node(yylineno, for_stmt_node, "FOR ( expr ; expr ; expr ) compound_stmt",
                                                        $1, open_round_brac, $3, semicollon1, $5, semicollon2, $7, close_round_brac, $9, NULL);}

    | FOR '(' expr ')' compound_stmt    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                        $$ = create_node(yylineno, for_stmt_node, "FOR ( expr ) compound_stmt", 
                                        $1, open_round_brac, $3, close_round_brac, $5, NULL);}
    ;

/* IfStmt Block */
if_stmt 
    : IF '(' expr ')' compound_stmt else_elif_stmt  {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                    Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                    $$ = create_node(yylineno, if_stmt_node, "IF ( expr ) compound_stmt else_elif_stmt", 
                                                    $1, open_round_brac, $3, close_round_brac, $5, $6, NULL);} 
    ;

else_elif_stmt
    : ELIF '(' expr ')' compound_stmt else_elif_stmt    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                        $$ = create_node(yylineno, else_elif_stmt_node, "ELIF '(' expr ')' compound_stmt else_elif_stmt",
                                                        $1, open_round_brac, $3, close_round_brac, $5, $6, NULL);}

    | else_stmt {$$ = create_node(yylineno, else_elif_stmt_node, "else_stmt", $1, NULL);}                          
    |           {$$ = create_node(yylineno, else_elif_stmt_node, "else_stmt --> EMPTY", NULL);}
    ;

else_stmt
    : ELSE compound_stmt    {$$ = create_node(yylineno, else_stmt_node, "ELSE compound_stmt", $1, $2, NULL);}
    ;

/*expression Block*/
expr   
    : expr relop expr  {$$ = create_node(yylineno, expr_node, "expr relop expr", $1, $2, $3, NULL);}
    | assignment    {$$ = create_node(yylineno, expr_node, "assignment", $1, NULL);}
    | array_usage   {$$ = create_node(yylineno, expr_node, "array_usage", $1, NULL);}
    ;

relop
    : LE    {$$ = create_node(yylineno, le_node, "=", NULL);}
    | GE    {$$ = create_node(yylineno, ge_node, ">=", NULL);} 
    | NE    {$$ = create_node(yylineno, ne_node, "!=", NULL);}
    | EQ    {$$ = create_node(yylineno, eq_node, "==", NULL);}
    | GT    {$$ = create_node(yylineno, gt_node, ">", NULL);}
    | LT    {$$ = create_node(yylineno, lt_node, "<", NULL);}
    | AND   {$$ = create_node(yylineno, and_node, "&&", NULL);}
    | OR    {$$ = create_node(yylineno, or_node, "||", NULL);}
    ;

/* Jump statements */
jump_statement
    : CONTINUE ';'  {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    $$ = create_node(yylineno, jump_statement_node, "CONTINUE ;", $1, semicollon, NULL);}

    | BREAK ';'     {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    $$ = create_node(yylineno, jump_statement_node, "BREAK ;", $1, semicollon, NULL);}

    | RETURN ';'    {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                    $$ = create_node(yylineno, jump_statement_node, "RETURN ;", $1, semicollon, NULL);}

    | RETURN expr ';'   {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                        $$ = create_node(yylineno, jump_statement_node, "RETURN expr ;", $1, $2, semicollon, (char *)NULL);}
    ;

/* Print Function */
print_func 
    : PRINTF '(' expr ')' ';'   {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
    							Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
    							Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
    							$$ = create_node(yylineno, print_func_node, "PRINTF ( expr ) ;", $1, open_round_brac, $3, close_round_brac, semicollon, NULL);}
    ;
%%
