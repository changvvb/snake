CFLAGS := -lcurses -g

snack : snake.o function.o
	gcc -o snake snake.o function.o $(CFLAGS)

snack.o : snake.c
	gcc -c -o snake.o snake.c $(CFLAGS)

function.o : function.c
	gcc -c -o function.o function.c $(CFLAGS)

clean :
	rm function.o snake.o snake

install:
	mv snake /usr/bin
