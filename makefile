out: lex.yy.c y.tab.c
	@echo "rule 'out'"
	cc lex.yy.c y.tab.c node.c -ll

lex.yy.c: y.tab.c bas.l
	@echo "rule 'lex.yy.c'..."
	lex bas.l

y.tab.c: bas.y
	@echo "rule 'y.tab.c'..."
	yacc -d bas.y