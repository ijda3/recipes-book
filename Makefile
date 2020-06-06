main: main.o
	gcc -lncurses -o main main.o
main.o: main.c
	gcc -c main.c
