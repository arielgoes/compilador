out: lex.yy.c y.tab.c
	@echo "rule 'out'"
	gcc -w lex.yy.c y.tab.c node.c main.c

lex.yy.c: y.tab.c bas.l
	@echo "rule 'lex.yy.c'..."
	lex bas.l

y.tab.c: bas.y
	@echo "rule 'y.tab.c'..."
	yacc -d bas.y