#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"
#include "symbol_table.h"


extern int vars_size;
extern int temp_size;
extern symbol_t symbol_table;
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

    if(code == NULL){
        printf("\n\"append_inst_tac\": NULL case!\n");
    }

    new_inst->inst = inst;
    new_inst->next = NULL;
    tac_line++;
    new_inst->number = tac_line;

    if(code[0] == NULL){
        code[0] = new_inst; //set header
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
        entry_t* result_res = lookup(symbol_table, i->res);
        entry_t* result_arg1 = lookup(symbol_table, i->arg1);
        if(result_res && result_arg1){
            int mem_pos = result_res->desloc - result_res->size;
            int mem_pos_arg1 = result_arg1->desloc - result_arg1->size;
            printf("%03d(SP) := %03d(SP)\n", mem_pos, mem_pos_arg1);
        }else if(result_res != NULL){
            int mem_pos = result_res->desloc - result_res->size; 
            printf("%03d(SP) := %s\n", mem_pos, i->arg1);
        }else{
            printf("%s := %s\n", i->res, i->arg1);
        }
    }else if(i->arg1 == NULL){
        entry_t* result = lookup(symbol_table, i->arg2);
        if(result != NULL){
            int mem_pos = result->desloc - result->size; 
            printf("%s := %s %03d(SP)\n",i->res, i->op, mem_pos);
        }else{
            printf("%s := %s %s\n", i->res, i->op, i->arg2);
        }
    }else{
        entry_t* result_arg1 = lookup(symbol_table, i->arg1);
        entry_t* result_arg2 = lookup(symbol_table, i->arg2);
        if(result_arg1 && result_arg2){
            int mem_pos_arg1 = result_arg1->desloc - result_arg1->size;
            int mem_pos_arg2 = result_arg2->desloc - result_arg2->size;
            printf("%s := %03d(SP) %s %03d(SP)\n", i->res, mem_pos_arg1, i->op, mem_pos_arg2);
        }else if(result_arg1){
            int mem_pos_arg1 = result_arg1->desloc - result_arg1->size;
            printf("%s := %03d(SP) %s %s\n", i->res, mem_pos_arg1, i->op, i->arg2);
        }else if(result_arg2){
            int mem_pos_arg2 = result_arg2->desloc - result_arg2->size;
            printf("%s := %s %s %03d(SP)\n", i->res, i->arg1, i->op, mem_pos_arg2);
        }else{
            printf("%s := %s %s %s\n", i->res, i->arg1, i->op, i->arg2);
        }
    }
}


void print_tac(FILE* out, struct node_tac* code){
    printf("\n\n\t THREE ADDRESS CODE\n\n");
    if(code == NULL){
        printf("TAC List is empty.\n\n");
        return;
    }

    printf("\n%d", vars_size);
    printf("\n%d\n", temp_size);
    
    struct node_tac* tac_pointer = (struct node_tac *)malloc(sizeof(struct node_tac));
    tac_pointer->inst = code->inst;
    tac_pointer->next = code->next;
    tac_pointer->prev = code->prev;
    tac_pointer->number = code->number;

     

    while(1){
        printf("%03d: ", tac_pointer->number);
        print_inst_tac(out, tac_pointer->inst);
        if(tac_pointer->next == NULL){
            printf("\n\n\t END ADDRESS CODE\n\n");
            break;
        }else{
            tac_pointer = tac_pointer->next;
        }
    }
}


void cat_tac(struct node_tac** code_a, struct node_tac** code_b){
    if(code_a[0] == NULL){
        code_a[0] = code_b[0];
    }else{
        if(code_b[0]){
            struct node_tac* tac_pointer;
            tac_pointer = code_a[0];

            while(tac_pointer->next != NULL){
                tac_pointer = tac_pointer->next;
            }

            tac_pointer->next = code_b[0];
            code_b[0]->prev = tac_pointer;
        }
    }
}


