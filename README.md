# compilador
Compiladores - Compiler
yacc –d bas.y          # create y.tab.h, y.tab.c
lex bas.l              # create lex.yy.c
cc lex.yy.c y.tab.c    # compile/link
