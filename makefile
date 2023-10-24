compiler: lex.yy.c y.tab.c node.c operationHandler.c symbolTable.c comparisonHandler.c
	gcc lex.yy.c y.tab.c node.c operationHandler.c symbolTable.c comparisonHandler.c -o compiler -lm

lex.yy.c: compiler.l
	flex compiler.l

y.tab.c: compiler.y
	yacc -d compiler.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h compiler



.PHONY: clean

