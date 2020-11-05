#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"


extern int vars_size;
extern int temps_size;
int tac_line = 0;
struct node_tac** code;

void append_inst_tac(struct node_tac** code, struct tac* inst){

    //creates a new instance of tac instruction
    struct node_tac* new_inst = (struct node_tac*)malloc(sizeof(struct node_tac));

    if(new_inst == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }

    if(tac_line > 999){
        printf("ERROR: Too many TACs in the list!\n");
        exit(0);
    }

    new_inst->inst = inst;
    new_inst->next = NULL;
    tac_line++;
    new_inst->number = tac_line;

    if(code[0] == NULL){ //funciona essa parte?
        code[0] = new_inst;
        new_inst->prev = NULL;
    }else{
        struct node_tac* tac_pointer;
        tac_pointer = code[0];
        while(tac_pointer->next != NULL){
            tac_pointer = tac_pointer->next;
        }
        tac_pointer->next = new_inst;
    }
}


struct tac* create_inst_tac(const char* res, const char* arg1,
                            const char* op, const char* arg2){
    
    struct tac* new_tac = (struct tac *)malloc(sizeof(struct tac));
    if(new_tac == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }
    
    new_tac->op = (char *)malloc(sizeof(char) * (strlen(op) + 1)); // len + 1, because of the '\0'
    if(new_tac->op == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }else{
        strcpy(new_tac->op, op);
    }

    new_tac->res = (char *)malloc(sizeof(char) * (strlen(res) + 1)); // len + 1, because of the '\0' 
    if(new_tac->res == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }else{
        strcpy(new_tac->res, res);
    }
    if(arg1 == NULL){
        new_tac->arg1 = NULL;
    }else{
        new_tac->arg1 = (char *)malloc(sizeof(char) * (strlen(arg1) + 1)); // len + 1, because of the '\0' 
        if(new_tac->arg1 == NULL){
            printf("ERROR: Failed to allocate enough memory!\n");
            exit(0);
        }else{
            strcpy(new_tac->arg1, arg1);
        }
    }

    if(arg2 == NULL){
        new_tac->arg2 = NULL;
    }else{
        new_tac->arg2 = (char *)malloc(sizeof(char) * (strlen(arg2) + 1)); // len + 1, because of the '\0' 
        if(new_tac->arg2 == NULL){
            printf("ERROR: Failed to allocate enough memory!\n");
            exit(0);
        }else{
            strcpy(new_tac->arg2, arg2);
        }
    }

    //debugging
    //printf("\n>>> res: '%s' | arg1: '%s' | op: '%s' | arg2: '%s'\n", new_tac->res, new_tac->arg1, new_tac->op, new_tac->arg2);

    return new_tac;
}


void print_inst_tac(FILE* out, struct tac* i){
    if(i->arg2 == NULL){
        printf("\n%s := %s\n", i->res, i->arg1);
    }else if(i->arg1 == NULL){
        printf("\n%s := %s %s", i->res, i->op, i->arg2);
    }else{
        printf("\n%s := %s %s %s\n", i->res, i->arg1, i->op, i->arg2);
    }
}


void print_tac(FILE* out, struct node_tac* code){
    printf("\n\n\t THREE ADDRESS CODE\n\n");
    while(1){
        if(code->next == NULL){
            printf("%s := %s\n", code->inst->arg1, code->inst->arg2);
            break;
        }else{
            printf("%s := %s %s %s\n", code->inst->res, code->inst->arg1, code->inst->op, code->inst->arg2);
            code = code->next;
        }
    }
}


void cat_tac(struct node_tac** code_a, struct node_tac** code_b){
    if(code_a[0] == NULL){
        code_a[0] == code_b[0];
    }else{
        if(code_b[0]){
            struct node_tac* tac_pointer;
            tac_pointer = code_a[0];

            while(tac_pointer->next){
                tac_pointer = tac_pointer->next;
            }

            tac_pointer->next = code_b[0];
            code_b[0]->prev = tac_pointer;
        }
    }
}


