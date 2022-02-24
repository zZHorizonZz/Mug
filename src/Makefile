CC: gcc
BD: binary_data/native/


all:

compile: main.c compiler.c
	${CC} main.c

main.o: main.c compiler.c
	${CC} main.c

compiler.o: compiler.c lexer.c
	${CC} compiler.c

