#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "node.h"

Node* syntax_tree;

Node* create_node(int nl, Node_type t, char* lexeme, /*Node children*/ ...){
    Node* new_node = (Node *)malloc(sizeof(Node));

    new_node->line_num = nl;
    new_node->type = t;
    new_node->lexeme = lexeme;

    va_list ap; //list of arguments (from <stdarg.h>)
    va_start(ap, lexeme);
    int n_args = 0;
    Node* arg = (Node *)malloc(sizeof(Node));

    for(arg = va_arg(ap, Node*); arg != NULL; arg = va_arg(ap, Node*)){
        //printf("Received: '%s'\n", arg->lexeme);
        n_args++;
    }
    va_end(ap);

    new_node->children = (Node**)malloc(sizeof(Node*)*n_args);

    va_start(ap, lexeme);
    for(int i = 0; i < n_args; i++){
        new_node->children[i] = va_arg(ap, Node*);
    }
    va_end(ap);

    return new_node;
}


int nb_of_children(Node* n){
    if(n == NULL){
        printf("ERROR: nb_of_children is NULL!\n");
        return -1;
    }
    
    return n->n_child;
}


int is_leaf(Node* n){
    if(n == NULL){
        printf("ERROR: is_leaf is NULL!\n");
        return -1;
    }
    
    return n->n_child == 0;
}


Node* child(Node* n, int i){
    if(n == NULL){
        printf("ERROR: child is NULL!\n");
        return NULL;
    }else if(0 <= i && (unsigned int)i < n->n_child){
        printf("ERROR: child is NULL!\n");
        return NULL;
    }

    return n->children[i];
}


int deep_free_node(Node* n){ //revisar... ta meio errado

    if(n == NULL){
        return 0;
    }
    
    int numChildren = sizeof(n->children)/sizeof(n->children[0]);
    for(int i = 0; i < numChildren; i++){
        deep_free_node(n->children[i]);
        free(n);
    }

    return 1;
}


int max(int *p){
	int i = 0;
	int aux = -1;
	for(int i = 0; i < sizeof(p)/sizeof(int); i++){
		if(p[i] > aux){
			aux = p[i];
		} 
	}

	return aux;
}


int height(Node* n){
	assert(n != NULL);
	int h = 0;
	int *p;
	if(n->n_child != 0){
		int i = 0;
		for(i = 0; n->children[i] != NULL; n = n->children[i++]){
			//h = height(n->children[i]);
			p[i] = height(n->children[i]); 
		}

		h + max(p);
	}
	return h + 1;
}


void uncompile(FILE* outfile, Node *n){ //fazer...
	if(n != NULL){
		printf("n->lexeme: %s\n", n->lexeme); 
        for(int i = 0; i < n->n_child; i++){
            uncompile(outfile, n->children[i]);
        }
	}
    return;
}

void print_node(Node* node){
            printf("line_num=\"%d\" type=\"%d\" lexeme=\"%s\"",
                node->line_num,
                node->type,
                node->lexeme);
}
