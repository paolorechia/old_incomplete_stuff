lex: time.l
	lex time.l
yacc: time.y
	yacc -d time.y
out: lex.yy.c
	gcc lex.yy.c y.tab.c 
all: lex yacc out
