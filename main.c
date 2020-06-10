#include "src/lib/recipes/recipe.h"
#include <ncurses.h>
#include <stdlib.h>

#define ESCAPE 27
#define KEY_USE 42
#define KEY_EDIT 97
#define KEY_REMOVE 33
#define KEY_ADD 43
#define KEY_SAIR 83

void menu() {
	mvprintw(0, 0, "LIVRO DE RECEITAS");
	mvprintw(2, 0, "Opções:");
	mvprintw(3, 0, "< > - Navegar");
	mvprintw(4, 0, "* - Marcar como usada");
	mvprintw(5, 0, "a - Alterar");
	mvprintw(6, 0, "! - Apagar receita");
	mvprintw(7, 0, "+ - Inserir receita");
	mvprintw(8, 0, "S - Sair do livro de receitas");
	move(11, 0);
}

int main() {
	int key;
	Recipes* recipes = load_recipes();

	initscr();
	keypad(stdscr, TRUE);
	noecho();

	menu();

	show_recipe(recipes);

	do {
		key = getch();
		move(11, 0);
		clrtoeol();

		switch (key) {
			case KEY_LEFT:
				prev_recipe(recipes);
				break;
			case KEY_RIGHT:
				next_recipe(recipes);
				break;
			case KEY_ADD:
				add_recipe(recipes);
				break;
			case KEY_REMOVE:
				remove_recipe(recipes);
				break;
			case KEY_EDIT:
				edit_recipe(recipes);
				break;
			case KEY_USE:
				use_recipe(recipes);
				break;
		}
	} while (key != KEY_SAIR);

	save_recipes(recipes);

	free(recipes);
	endwin();

	return 0;
}
