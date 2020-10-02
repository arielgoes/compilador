#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "node.h"


extern Node* syntax_tree;

Node* create_node(int nl, Node_type t, char& lexeme, /*Node children*/ ...){
    Node* new_node = (Node *)malloc(sizeof(Node));

    new_node->line_num = nl;
    new_node->type = t;
    new_node->lexeme = lexeme;

    va_list ap; //list of arguments (from library <stdarg.h>)
    va_start(ap, lexeme);
    int n_args = 0;
    Node* arg = (Node *)malloc(sizeof(Node));
    
    for(; arg != NULL; va_arg(ap, Node*)){
        printf("Received: '%s'\n", arg->lexeme);
        n_args++;
    }
    va_end(ap);

    va_start(ap, lexeme);
    for(int i = 0; i < n_args; i++){
        new_node->children[i] = va_arg(ap, Node*);
    }
    va_end(ap);

    return new_node;

}


