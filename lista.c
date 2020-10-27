#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"


extern int vars_size;
extern int temps_size;
int tac_line = 0;


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

    new_tac->arg1 = (char *)malloc(sizeof(char) * (strlen(arg1) + 1)); // len + 1, because of the '\0' 
    if(new_tac->arg1 == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }else{
        strcpy(new_tac->arg1, arg1);
    }

    new_tac->arg2 = (char *)malloc(sizeof(char) * (strlen(arg2) + 1)); // len + 1, because of the '\0' 
    if(new_tac->arg2 == NULL){
        printf("ERROR: Failed to allocate enough memory!\n");
        exit(0);
    }else{
        strcpy(new_tac->arg2, arg2);
    }

    //debugging
    printf("instrucao: %s = %s %s %s\n", new_tac->res, new_tac->arg1, new_tac->op, new_tac->arg2);

    return new_tac;
}


void print_inst_tac(FILE* out, struct tac i){
    printf("instrucao: %s = %s %s %s\n", i.res, i.arg1, i.op, i.arg2);
}


void print_tac(FILE* out, struct node_tac * code){

}

