out: lex.yy.c y.tab.c
	cc lex.yy.c y.tab.c

lex.yy.c: y.tab.c bas.l
	lex bas.l

y.tab.c: bas.y
	yacc -d bas.y

clean: 
	rm -rf lex.yy.c y.tab.c y.tab.h out out.dSYM