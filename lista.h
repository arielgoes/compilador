/** @file lista.h
 */

#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int vars_size;
extern int temps_size;


/**
 * Estrutura de dados (que implementa uma intrucao TAC, ver Etapa 4), a ser
 * encadeada na lista. Por enquanto, o que representa é irrelevante.
 */
struct tac {
   char* op;   /* "+", "-", ":=", "if", etc... */
   char* res;  /* "TMP100" */
   char* arg1; /* "TMP0"   */
   char* arg2; /* "TMP1"   */
};

/** \brief  Construtor de Instrucao TAC
 *
 * Para testes, pode-se usar qualquer string em argumentos.
 * @param res um char*.
 * @param arg1 um char*.
 * @param op um char*.
 * @param arg2 um char*.
 * @ return um ponteiro sobre uma 'struct tac'.
 */
struct tac* create_inst_tac(const char* res, const char* arg1,
                 const char* op, const char* arg2);

/** \brief Funcao que imprime o conteudo de uma instrucao TAC
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a instrucao.
 * @param i a instrucao a ser impressa.
 */
void print_inst_tac(FILE* out, struct tac* i);

/** Um elemento basico da lista. O campo 'inst' aponta para a informacao a ser
 * armazenada em um elemento da lista. O campo 'number' serve para numerar
 * as entradas: a primeira da lista deve valer 1, a segunda 2, etc.
 * O resto dos campos serve para implementar a lista
 * e seus metodos.
 */
struct node_tac {
   int number;
   struct tac * inst;
   struct node_tac* next;
   struct node_tac* prev;
};

/** \brief Imprime no arquivo apontado por 'out' o conteudo da lista apontada
 * por 'code'.
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a lista (uma linha por elemento).
 * @param code o ponteiro para a lista a ser impressa.
 *
 * Obs.: cada linha impressa no arquivo deve comecar por um numero inteiro
 * (3 digitos) seguido de ':'. O numero deve ser o numero da linha.
 * Exemplo:
 *   001:  instrucao_qualquer
 *   002:  outra_instrucao
 *    .....
 *   999:  ultima_instrucao
 *   000:  agora_tem_instrucao_demais
 */
void print_tac(FILE* out, struct node_tac* code);

/** Insere no fim da lista 'code' o elemento 'inst'.
 * @param code lista (possivelmente vazia) inicial, em entrada. Na saida, contem *         a mesma lista, com mais um elemento inserido no fim.
 * @inst  o elemento inserido no fim da lista.
 */
void append_inst_tac(struct node_tac** code, struct tac* inst);

/** Concatena a lista 'code_a' com a lista 'code_b'.
 * @param code_a lista (possivelmente vazia) inicial, em entrada. Na saida, contem
 *         a mesma lista concatenada com 'code_b'.
 * @param code_b a lista concatenada com 'code_a'.
 */
void cat_tac(struct node_tac ** code_a, struct node_tac ** code_b);

#endif
