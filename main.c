#include "src/lib/recipes/recipe.h"
#include <ncurses.h>
#include <stdlib.h>

#define ESCAPE 27

int main() {
	int key;
	Recipes* recipes = load_recipes();

	initscr();
	keypad(stdscr, TRUE);
	noecho();

	do {
		key = getch();

		switch (key) {
			case KEY_LEFT:
				prev_recipe(recipes);
				break;
			case KEY_RIGHT:
				next_recipe(recipes);
				break;
		}

		refresh();
	} while (key != ESCAPE);

	free(recipes);
	endwin();

	return 0;
}
