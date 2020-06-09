main: main.o recipe.o
	gcc -lncurses -o main main.o recipe.o
main.o: main.c
	gcc -c main.c
recipe.o: src/lib/recipes/recipe.c
	gcc -c src/lib/recipes/recipe.c
