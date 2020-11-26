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
    #define STR_TYPE 5

    #define FLOAT_SIZE 4
    #define INT_SIZE 4
    #define CHAR_SIZE 1
    #define DOUBLE_SIZE 8

    extern void yyerror(const char *);  /* prints grammar violation message */
    extern int yylineno;
    extern Node* syntax_tree;
    extern symbol_t symbol_table;
    extern symbol_t temp_table;
    extern struct node_tac* code = NULL;
    struct node_tac* temp_tac = NULL; //list of tacs

    int vars_size = 0;
    int temp_size = 0;
    
    //extern char yytext[];
    extern int column;

    void yyerror(char const *s){
        fflush(stdout);
        printf("\n%*s\n%*s\n", column, "^", column, s);
    }

    int tipo_global = 0;
    int temp_tipo_global = 0;


    int temp_reg = 0; //t1, t2, t3,...

    int label_number = 0;

    int aninhamento = 0;
    int max_aninhamento = 0;

    
    void create_table_entry(char* lexeme){
        if(lookup(symbol_table, lexeme)){
            printf("'%s' symbol defined multiple times. Type: '%d'.\n", lexeme, tipo_global);
            return;
        }else{
            entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
            //printf("\n>>>> New symbol: '%s', type: '%d'", lexeme, tipo_global);
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
                /*printf("\n>>>> insert table: SUCCESS! value: %s\n", lexeme);*/
            }

        }
    }

    void create_temp_table(char* temp, int type){
        if(lookup(temp_table, temp)){
            printf("'%s' symbol defined multiple times. Type: '%d'.\n", temp, type);
            return;
        }else{
            entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
            //printf("\n>>>> New symbol: '%s', type: '%d'", lexeme, tipo_global);
            new_entry->name = temp;
            switch(type){
                case FLOAT_TYPE: 
                    temp_size += FLOAT_SIZE;
                    new_entry->type = type;
                    new_entry->size = FLOAT_SIZE;
                    new_entry->desloc = temp_size;
                    break; 
                case INT_TYPE:
                    temp_size += INT_SIZE;
                    new_entry->type = type;
                    new_entry->size = INT_SIZE;
                    new_entry->desloc = temp_size;
                    break;
                case CHAR_TYPE:
                    temp_size += CHAR_SIZE;
                    new_entry->type = type;
                    new_entry->size = CHAR_SIZE;
                    new_entry->desloc = temp_size;
                    break;
                default:
                    printf("\n>>>> ERROR: Undefined type '%s' ^\n", temp);
                    exit(0);
            }

            if(insert(&temp_table, new_entry) == -1){
                printf("\n>>>> insert table: ERROR! Cannot allocate %s into 'symbol_table'!\n", temp);
                exit(0);
            }else{
                /*printf("\n>>>> insert table: SUCCESS! value: %s\n", temp);*/
            }
        }
    }

    int check_types(Node* node1, Node* node2){
        int temp_tipo = 0;
        if(lookup(symbol_table, node1->lexeme)){
            temp_tipo = lookup(symbol_table, node1->lexeme)->type;
        }else if(lookup(temp_table, node1->lexeme)){
            temp_tipo = lookup(temp_table, node1->lexeme)->type;
        }else{
            switch(node1->type){
            case 562:
                temp_tipo = CHAR_TYPE;
                break;
            case 563:
                temp_tipo = INT_TYPE;
                break;
            case 564:
                temp_tipo = FLOAT_TYPE;
                break;
            default:
                printf("\nLookup Error!\n");
                exit(0);
            }
        }
        int temp_tipo2 = 0;
        if(lookup(symbol_table, node2->lexeme)){
            temp_tipo2 = lookup(symbol_table, node2->lexeme)->type;
        }else if(lookup(temp_table, node2->lexeme)){
            temp_tipo2 = lookup(temp_table, node2->lexeme)->type;
        }else{
            switch(node2->type){
            case 562:
                temp_tipo2 = CHAR_TYPE;
                break;
            case 563:
                temp_tipo2 = INT_TYPE;
                break;
            case 564:
                temp_tipo2 = FLOAT_TYPE;
                break;
            default:
                printf("\nLookup Error!\n");
                exit(0);
            }
        }
        if(temp_tipo != temp_tipo2){
            printf("\n\nCONFLICTING TYPES IN '%s + %s'\n\n", node1->lexeme, node2->lexeme);
            exit(0);
        }else{
            return temp_tipo;
        }
    }

%}

%union{
    struct node* no;
    char *str; 
};

%token <no> WHILE FOR IF ELSE ELIF BREAK CONTINUE RETURN PRINTF
%token <str> FLOAT INT CHAR VOID DOUBLE ID CONSTANT INCR DECR GE LE EQ NE LT GT AND OR NOT
%token <str> CONSTANT_STR CONSTANT_CHAR CONSTANT_INT CONSTANT_FLOAT
                
%type<no> atree
%type<no> translation_unit       
%type<no> external_declaration               
%type<no> function               
%type<no> declaration
%type<no> declaration_assignment            
%type<no> assignment          
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
%type<no> conditional_if             
%type<no> if_stmt                
%type<no> print_func             
%type<no> jump_statement                         
%type<no> expr                   
%type<no> elif_stmt         
%type<no> else_stmt
%type<no> relop
%type<no> type

%right '='
%left AND OR
%left LE GE EQ NE LT GT
%left '-' '+'
%left '*' '/' '%' 
%left '~'


%start atree
%%

atree
    :translation_unit {$$ = create_node(yylineno, atree_node, "atree", $1, NULL); syntax_tree = $$;
    /*uncompile(stdout, $1);*/}
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
    | array_usage ';'                   {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "array_usage ;", $1, semicollon, NULL);}
    | type declaration_array_usage ';'  {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                                        $$ = create_node(yylineno, declaration_node, "assignment ;", $1, $2, semicollon, NULL);}
    ;


/* Declaration followed by assignment */
declaration_assignment
    : ID '=' assignment         {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, (char*)$1, NULL);
                                $$ = create_node(yylineno, assignment_node, "ID = assignment", id, eq, $3, NULL);
                                create_table_entry($1);
                                if(lookup(symbol_table, (char *)$1) == NULL){
                                    printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                                    exit(0);
                                }
                                check_types(id, $3);
                                struct tac* new_tac = create_inst_tac($1, $3->lexeme, "=", NULL);
                                $$ = create_node(yylineno, assignment_node, $1, id, eq, $3, ";", NULL);
                                append_inst_tac(&temp_tac, new_tac);
                                cat_tac(&code, &temp_tac);
                                temp_tac = NULL;
                                /*print_tac(stdout, code);*/}
    | ID                        {$$ = create_node(yylineno, assignment_node, "ID", $1, NULL);
                                create_table_entry($1);}
    ;                             


/* Assignment section */
assignment
    : assignment '+' assignment     {Node* sum = create_node(yylineno, sum_node, "+", NULL);
                                    int temp_tipo = check_types($1, $3);
                                    char res[7];
                                    sprintf(res, "%03d(Rx)", temp_size);
                                    create_temp_table(res, temp_tipo);
                                    $$ = create_node(yylineno, assignment_node, res, $1, sum, $3, NULL);
                                    struct tac* new_tac = create_inst_tac(res, $1->lexeme, "SUM", $3->lexeme);
                                    append_inst_tac(&temp_tac, new_tac);}
    | assignment '-' assignment     {Node* sub = create_node(yylineno, sub_node, "-", NULL);
                                    int temp_tipo = check_types($1, $3);
                                    char res[7];
                                    sprintf(res, "%03d(Rx)", temp_size);
                                    create_temp_table(res, temp_tipo);
                                    $$ = create_node(yylineno, assignment_node, res, $1, sub, $3, NULL);
                                    struct tac* new_tac = create_inst_tac(res, $1->lexeme, "SUB", $3->lexeme);
                                    append_inst_tac(&temp_tac, new_tac);}
    | assignment '*' assignment     {Node* mult = create_node(yylineno, mult_node, "*", NULL);
                                    int temp_tipo = check_types($1, $3);
                                    char res[7];
                                    sprintf(res, "%03d(Rx)", temp_size);
                                    create_temp_table(res, temp_tipo);
                                    $$ = create_node(yylineno, assignment_node, res, $1, mult, $3, NULL);
                                    struct tac* new_tac = create_inst_tac(res, $1->lexeme, "MULT", $3->lexeme);
                                    append_inst_tac(&temp_tac, new_tac);}
    | assignment '/' assignment     {Node* div = create_node(yylineno, div_node, "/", NULL);
                                    int temp_tipo = check_types($1, $3);
                                    
                                    char res[7];
                                    sprintf(res, "%03d(Rx)", temp_size);
                                    create_temp_table(res, temp_tipo);
                                    $$ = create_node(yylineno, assignment_node, res, $1, div, $3, NULL);
                                    struct tac* new_tac = create_inst_tac(res, $1->lexeme, "DIV", $3->lexeme);
                                    append_inst_tac(&temp_tac, new_tac);}
    | assignment '%' assignment     {Node* mod = create_node(yylineno, mod_node, "%", NULL);
                                    int temp_tipo = check_types($1, $3);

                                    char res[7];
                                    sprintf(res, "%03d(Rx)", temp_size);
                                    create_temp_table(res, temp_tipo);
                                    $$ = create_node(yylineno, assignment_node, res, $1, mod, $3, NULL);
                                    struct tac* new_tac = create_inst_tac(res, $1->lexeme, "MOD", $3->lexeme);
                                    append_inst_tac(&temp_tac, new_tac);}
    | '(' assignment ')'    {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                            Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                            $$ = create_node(yylineno, assignment_node, $2->lexeme, open_round_brac, $2, close_round_brac, NULL);}
    | '-' assignment    {Node* sub = create_node(yylineno, sub_node, "-", NULL);                 
                        int temp_tipo = check_types($2, $2);
                        char res[7];
                        sprintf(res, "%03d(Rx)", temp_size);
                        create_temp_table(res, temp_tipo);
                        $$ = create_node(yylineno, assignment_node, res, sub, $2, NULL);
                        struct tac* new_tac = create_inst_tac(res, NULL, "UMINUS", $2->lexeme);
                        append_inst_tac(&temp_tac, new_tac);}
    | CONSTANT_CHAR  {$$ = create_node(yylineno, constant_char_node, (char *)$1, $1, NULL);}
    | CONSTANT_INT   {$$ = create_node(yylineno, constant_int_node, (char *)$1, $1, NULL);}
    | CONSTANT_FLOAT {$$ = create_node(yylineno, constant_float_node, (char *)$1, $1, NULL);}
    | ID        {entry_t* id_entry = lookup(symbol_table, (char *)$1);
                if(id_entry == NULL){
                    printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                    exit(0);
                }else{
                    $$ = create_node(yylineno, assignment_node, (char *)$1, $1, NULL);
                }}
    ;

    
/* Array usage */
array_usage
    : ID '[' assignment ']' {Node* open_sqr_brac = create_node(yylineno, open_sqr_brac_node, "[", NULL);
                            Node* close_sqr_brac = create_node(yylineno, close_sqr_brac_node, "]", NULL);
                            $$ = create_node(yylineno, array_usage_node, "ID [ assignment ]", $1, open_sqr_brac, $3, close_sqr_brac, NULL);
                            if(lookup(symbol_table, (char *)$1) == NULL){
                                printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                                exit(0);
                            }}
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
    : while_stmt        {$$ = create_node(yylineno, stmt_node, "while_stmt", $1, NULL);
                        if(aninhamento == 0){
                            label_number += max_aninhamento;
                            max_aninhamento = 0;
                        }}
    | declaration       {$$ = create_node(yylineno, stmt_node, "declaration", $1, NULL);}
    | for_stmt          {$$ = create_node(yylineno, stmt_node, "for_stmt", $1, NULL);} 
    | conditional_if    {$$ = create_node(yylineno, stmt_node, "if_stmt", $1, NULL);
                        if(aninhamento == 0){
                            label_number += max_aninhamento;
                            max_aninhamento = 0;
                        }}  
    | print_func        {$$ = create_node(yylineno, stmt_node, "print_func", $1, NULL);} 
    | jump_statement    {$$ = create_node(yylineno, stmt_node, "jump_statement", $1, NULL);}
    | ID '=' assignment ';'     {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                Node* id = create_node(yylineno, id_node, (char*)$1, NULL);
                                if(lookup(symbol_table, (char *)$1) == NULL){
                                    printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                                    exit(0);
                                }
                                check_types(id, $3);
                                struct tac* new_tac = create_inst_tac($1, $3->lexeme, "=", NULL);
                                $$ = create_node(yylineno, assignment_node, $1, id, eq, $3, ";", NULL);
                                append_inst_tac(&temp_tac, new_tac);
                                cat_tac(&code, &temp_tac);
                                temp_tac = NULL;
                                /*print_tac(stdout, code);*/}
    | ID DECR   {$$ = create_node(yylineno, assignment_node, "ID DECR", $1, $2, NULL);
                if(lookup(symbol_table, (char *)$1) == NULL){
                    printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                    exit(0);
                }
                struct tac* new_tac = create_inst_tac((char *)$1, (char *)$1, "-", "1");
                append_inst_tac(&temp_tac, new_tac);
                cat_tac(&code, &temp_tac);
                temp_tac = NULL;
                /*print_tac(stdout, code);*/}
    | ID INCR   {$$ = create_node(yylineno, assignment_node, "ID INCR", $1, $2, NULL);
                if(lookup(symbol_table, (char *)$1) == NULL){
                    printf("\n\nVariable '%s' not found.\n\n", (char *)$1);
                    exit(0);
                }
                struct tac* new_tac = create_inst_tac((char *)$1, (char *)$1, "+", "1");
                append_inst_tac(&temp_tac, new_tac);
                cat_tac(&code, &temp_tac);
                temp_tac = NULL;
                /*print_tac(stdout, code);*/}
    | array_usage '=' assignment ';'    {Node* eq = create_node(yylineno, eq_node, "=", NULL);
                                        $$ = create_node(yylineno, assignment_node, "array_usage = assignment", $1, eq, $3, ";", NULL);
                                        }
    | ';'                   {Node* semicollon = create_node(yylineno, semicollon_node, ";", NULL);
                            $$ = create_node(yylineno, stmt_node, ";", semicollon, NULL);}
    ;


/* Loop section */
while_stmt
    : WHILE '(' {int label_n = label_number + aninhamento;
                char label[10];
                sprintf(label, "label%d", label_n);
                struct tac* new_tac = create_inst_tac(NULL, "label", "", label);
                append_inst_tac(&code, new_tac);
                }  
                
    expr    {char label[15];
        
            sprintf(label, "GOTO label%d", label_number + aninhamento + 1);
            struct tac* new_tac = create_inst_tac(NULL, "IF", $4->lexeme, label);
            append_inst_tac(&code, new_tac);

            char end_label[15];
            int label_n = label_number + aninhamento + 2;

            sprintf(end_label, "GOTO label%d", label_n);
            struct tac* tac_end = create_inst_tac(NULL, "", "", end_label);
            append_inst_tac(&code, tac_end);

            char label_name[10];
            sprintf(label_name, "label%d", label_number + aninhamento + 1);
            struct tac* tac_label = create_inst_tac(NULL, "label", "", label_name);
            append_inst_tac(&code, tac_label);

            aninhamento += 3;
            if(aninhamento > max_aninhamento){
                max_aninhamento = aninhamento;
            }
            } 
    
      ')' compound_stmt     {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                            Node* close_round_brac = create_node(yylineno, close_round_brac_node, "(", NULL);
                            $$ = create_node(yylineno, while_stmt_node, "WHILE ( expr ) compound_stmt",
                            $1, open_round_brac, $4, close_round_brac, $7, NULL);
                            
                            aninhamento -= 3;
                            char label[15];
                            sprintf(label, "GOTO label%d", label_number + aninhamento);
                            struct tac* new_tac = create_inst_tac(NULL, "", "", label);
                            append_inst_tac(&code, new_tac);

                            char label_name[10];
                            sprintf(label_name, "label%d", label_number + aninhamento + 2);
                            struct tac* tac_label = create_inst_tac(NULL, "label", "", label_name);
                            append_inst_tac(&code, tac_label);
                            }
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

conditional_if
    : if_stmt                           {                                        }
    | if_stmt else_stmt                 {printf("Label fora do if-else\n");}
    | if_stmt elif_stmt {}
    | if_stmt elif_stmt else_stmt {}
    ;


if_stmt 
    : IF '(' expr   {char label[15];

                    int label_n = label_number + aninhamento;
                    sprintf(label, "GOTO label%d", label_n);
                    struct tac* new_tac = create_inst_tac(NULL, "IF", $3->lexeme, label);
                    append_inst_tac(&code, new_tac);
                    
                    int next_label_n = label_number + aninhamento + 1;
                    char next_label[15];
                    sprintf(next_label, "GOTO label%d", next_label_n);
                    printf(next_label);
                    struct tac* _tac = create_inst_tac(NULL, "", "", next_label);
                    append_inst_tac(&code, _tac);


                    char label_name[10];
                    sprintf(label_name, "label%d", label_n);
                    struct tac* tac_ = create_inst_tac(NULL, "label", "", label_name);
                    append_inst_tac(&code, tac_);
                    aninhamento += 2;
                    if(aninhamento > max_aninhamento){
                        max_aninhamento = aninhamento;
                    }
                    }
                    
    ')' compound_stmt       {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                            Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                            $$ = create_node(yylineno, if_stmt_node, "IF ( expr ) compound_stmt else_elif_stmt", 
                            $1, open_round_brac, $3, close_round_brac, $6, NULL);
                            
                            aninhamento -= 2;
                            char label_name[10];
                            sprintf(label_name, "label%d", label_number + aninhamento + 1);
                            struct tac* tac_ = create_inst_tac(NULL, "label", "", label_name);
                            append_inst_tac(&code, tac_);
                            } 
    ;

elif_stmt
    : ELIF '(' expr ')' compound_stmt elif_stmt         {Node* open_round_brac = create_node(yylineno, open_round_brac_node, "(", NULL);
                                                        Node* close_round_brac = create_node(yylineno, close_round_brac_node, ")", NULL);
                                                        $$ = create_node(yylineno, else_elif_stmt_node, "ELIF '(' expr ')' compound_stmt else_elif_stmt",
                                                        $1, open_round_brac, $3, close_round_brac, $5, $6, NULL);}                        
    |           {$$ = create_node(yylineno, else_elif_stmt_node, "else_stmt --> EMPTY", NULL);
                printf("label dentro do else\n");}
    ;

else_stmt
    : ELSE compound_stmt    {$$ = create_node(yylineno, else_stmt_node, "ELSE compound_stmt", $1, $2, NULL);
                            
                            }
    ;

/*expression Block*/
expr   
    : expr relop expr  {printf("\n\n %s  %s  %s\n\n", $1->lexeme, $2->lexeme, $3->lexeme);
                        int temp_tipo = check_types($1, $3);
                        char res[7];
                        sprintf(res, "%03d(Rx)", temp_size);
                        create_temp_table(res, temp_tipo);
                        $$ = create_node(yylineno, expr_node, res, $1, $2, $3, NULL);
                        struct tac* new_tac = create_inst_tac(res, $1->lexeme, $2->lexeme, $3->lexeme);
                        append_inst_tac(&temp_tac, new_tac);
                        cat_tac(&code, &temp_tac);
                        temp_tac = NULL;
                        /*print_tac(stdout, code);*/}
    | assignment    {$$ = create_node(yylineno, expr_node, $1->lexeme, $1, NULL);}
    ;

relop
    : LE    {$$ = create_node(yylineno, le_node, "<=", NULL);}
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

