out: lex.yy.c y.tab.c
	@echo "rule 'out'"
	gcc -w lex.yy.c y.tab.c node.c main.c symbol_table.c lista.c

lex.yy.c: y.tab.c bas.l
	@echo "rule 'lex.yy.c'..."
	lex bas.l

y.tab.c: bas.y
	@echo "rule 'y.tab.c'..."
	yacc -td bas.y