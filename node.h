/** @file node.h
 *  @version 1.2
 */

#ifndef _NODE_H_
#define _NODE_H_

#ifdef __GNUC__
    /* If using gcc, warn about missing sentinel NULLs */
    #define NULL_TERMINATED __attribute__((sentinel))
#else
    #define NULL_TERMINATED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef int Node_type;

/* Serie de constantes que servirao para definir tipos de nos (na arvore). 
 * Essa serie pode ser completada ou alterada a vontade.
 */
#define translation_unit_node       500
#define external_node               501
#define function_node               502
#define declaration_node            503
#define type_node                   504
#define assignment_node             505
#define function_call_node          506
#define array_usage_node            507
#define id_node                     508
#define constant_node               509
#define incr_node                   510
#define decr_node                   511
#define float_node                  512
#define int_node                    513
#define char_node                   514
#define void_node                   515
#define bool_node                   516
#define double_node                 517
#define arg_list_opt_node           518
#define arg_list_node               519
#define arg_node                    520
#define compound_stmt_node          521
#define stmt_list_node              522
#define stmt_node                   523
#define while_stmt_node             524
#define for_stmt_node               525
#define if_stmt_node                526
#define print_func_node             527
#define jump_statement_node         528
#define while_node                  529
#define for_node                    530
#define if_node                     531
#define expr_node                   532
#define else_elif_stmt_node         533
#define elif_node                   534
#define else_stmt_node              535
#define else_node                   536
#define le_node                     537
#define ge_node                     538
#define ne_node                     539
#define eq_node                     540
#define gt_node                     541
#define lt_node                     542
#define and_node                    543
#define or_node                     544
#define continue_node               545
#define break_node                  546
#define return_node                 547
#define printf_node                 548

/** Estrutura de dados parcial para o no da arvore. */
typedef struct node {
   int line_num;                    /**< numero de linha. */
   char* lexeme;                    /**< o lexema retornado pelo analizador lexical. */
   Node_type type;                  /**< Um dos valores definidos acima pelos # defines. */
   void* attribute;                 /**< Qualquer coisa por enquanto. */

   struct node** children;
   unsigned int n_child;

} Node;

extern Node * syntax_tree;



/**
 *  * Node constructor.
 *
 * @param nl: line number where this token was found in the source code.
 * @param t: node type (one of the values #define'd above). Must abort
 *             the program if the type is not correct.
 * @param lexeme: whatever string you want associated to this node.
 * @param attr: a semantical attribute.
 * @param children: NULL-terminated list of pointers to children Node*'s.
 *     See the extra file 'exemplo_func_var_arg.c' for an example.
 *     Callers are expected to pass *only Node pointers* as arguments.
 *     To create a leaf, use just NULL.
 * @return a pointer to a new Node.
 */
NULL_TERMINATED
Node* create_node(int nl, Node_type t,
        char* lexeme,  /* Node* children */ ...);

/** Accessor to the number of children of a Node.
 *  Must abort the program if 'n' is NULL.
 */
int nb_of_children(Node* n);

/** Tests if a Node is a leaf.
 *  Must abort the program if 'n' is NULL.
 *  @return 1 if n is a leaf, 0 else.
 */
int is_leaf(Node* n);

/** accessor to the i'th child of a Node.
 * @param n : the node to be consulted. Must abort the program if 'n' is NULL.
 * @param i : the number of the child that one wants. Given a node degree d,
 *       valid values for i are: 0 <= i < d.
 *       Must abort the program if i is not correct.
 * @return a pointer to a Node.
 */
Node* child(Node* n, int i) ;

/** Destructor of a Node. Deallocates
 * (recursively) all of the tree rooted at 'n'.
 */
int deep_free_node(Node* n) ;

/** returns the height of the tree rooted by 'n'.
 *  The height of a leaf is 1. 
 */
int height(Node *n) ;

/** Prints into a file the lexemes contained in the node rooted by 'n'.
 *  Lexemes must be printed in a depth-first order.
 *  @param outfile : the file to which the lexemes are printed.
 *  @param n : the root node of the tree. Must abort the program if 'n' is NULL.
 *
 */
void uncompile(FILE* outfile, Node *n) ;

void print_node(Node* node) ;


#endif