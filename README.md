# compilador
Compiladores - Compiler
yacc –d bas.y          # create y.tab.h, y.tab.c\n
lex bas.l              # create lex.yy.c\n
cc lex.yy.c y.tab.c    # compile/link\n
