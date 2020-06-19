seed: seed.o recipe.o
	gcc -lncurses -o seed seed.o recipe.o
seed.o: seed.c
	gcc -c seed.c
recipe.o: ../src/lib/recipes/recipe.c
	gcc -c ../src/lib/recipes/recipe.c
