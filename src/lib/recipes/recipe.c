#include "recipe.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LENGTH 150
#define TEXT_LENGTH 5000

typedef struct recipe {
	char title[DEFAULT_LENGTH];
	int total_time;
	char author[DEFAULT_LENGTH];
	float rating;
	int use_count;
	char ingredient[TEXT_LENGTH];
	char directions[TEXT_LENGTH];

	struct recipe* prev;
	struct recipe* next;
} Recipe;

struct recipe_control {
	int total_recipes;
	Recipe* current;
	Recipe* first;
	Recipe* last;
};

void add_in_recipes(Recipes* recipes, Recipe* new_recipe);

Recipes* load_recipes() {
	Recipes* recipes = malloc(sizeof(Recipes));
	Recipe* temp_recipe = NULL;
	Recipe* temp_prev = NULL;
	FILE* fp;
	int i, total_recipes;

	recipes->total_recipes = 0;

	fp = fopen("database.bin", "rb");

	if (fp == NULL) {
		recipes->current = NULL;
		recipes->first = NULL;
		recipes->last = NULL;
		return recipes;
	}

	fread(&total_recipes, sizeof(int), 1, fp);

	for (i = 0; i < total_recipes; i++) {
		temp_recipe = malloc(sizeof(Recipe));

		fread(temp_recipe, sizeof(Recipe), 1, fp);
		add_in_recipes(recipes, temp_recipe);
	}

	fclose(fp);

	recipes->current = recipes->first;

	return recipes;
}

void add_recipe(Recipes* recipes) {
	Recipe* new_recipe = malloc(sizeof(Recipe));
	char temp_title[DEFAULT_LENGTH];
	char temp_char;
	int i = 0;

	move(11, 0);
	clrtobot();
	echo();

	printw("Nome da receita: ");
	getstr(temp_title);

	while (temp_title[i] != '\0') {
		temp_char = toupper(temp_title[i]);

		strcat(new_recipe->title, &temp_char);

		i++;
	}

	printw("Tempo de preparo (minutos): ");
	scanw("%d", &new_recipe->total_time);

	printw("Ingredientes: ");
	getstr(new_recipe->ingredient);

	printw("Modo de preparo: ");
	getstr(new_recipe->directions);

	printw("Nome do criador: ");
	getstr(new_recipe->author);

	printw("Nota da receita: ");
	scanw("%f", &new_recipe->rating);

	new_recipe->use_count = 0;

	add_in_recipes(recipes, new_recipe);

	move(11, 0);
	clrtobot();
	noecho();
}

void remove_recipe(Recipes* recipes) {
	if (recipes->total_recipes > 0) {
		Recipe* deleted = recipes->current;
		Recipe* next = deleted->next;
		Recipe* prev = deleted->prev;

		if (recipes->total_recipes == 1) {
			recipes->current = NULL;
			recipes->first = NULL;
			recipes->last = NULL;
		} else {
			if (deleted == recipes->first) {
				recipes->first = next;
				recipes->first->prev = recipes->last;
				recipes->last->next = recipes->first;
				recipes->current = recipes->first;
			} else if (deleted == recipes->last) {
				recipes->last = prev;
				recipes->first->prev = recipes->last;
				recipes->last->next = recipes->first;
				recipes->current = recipes->last;
			} else {
				recipes->current = next;
				next->prev = deleted->prev;
				prev->next = deleted->next;
			}
		}

		recipes->total_recipes--;

		free(deleted);
	}
}

void edit_recipe(Recipes* recipes) {
	int use_count = recipes->current->use_count;

	remove_recipe(recipes);
	add_recipe(recipes);

	recipes->current->use_count = use_count;
}

void use_recipe(Recipes* recipes) { recipes->current->use_count++; }

void prev_recipe(Recipes* recipes) {
	if (recipes->current != NULL) {
		recipes->current = recipes->current->prev;
	}
}

void next_recipe(Recipes* recipes) {
	if (recipes->current != NULL) {
		recipes->current = recipes->current->next;
	}
}

void show_recipe(Recipes* recipes) {
	if (recipes->current != NULL) {
		printw("Nome da receita: %s\n", recipes->current->title);
		printw("Tempo de preparo: %d minutos\n", recipes->current->total_time);
		printw("Ingredientes: %s\n", recipes->current->ingredient);
		printw("Modo de preparo: %s\n", recipes->current->directions);
		printw("Nome do criador: %s\n", recipes->current->author);
		printw("Nota da receita: %.02f\n", recipes->current->rating);
		printw("Vezes de preparo: %d\n", recipes->current->use_count);
	} else {
		printw("Nao ha receita cadastrada!");
	}
}

void save_recipes(Recipes* recipes) {
	if (recipes->total_recipes > 0) {
		FILE* fp;
		fp = fopen("database.bin", "wb");
		int i;

		if (fp == NULL) {
			printw("Erro ao criar o arquivo database.bin");
			return;
		}

		fwrite(&recipes->total_recipes, sizeof(int), 1, fp);

		for (i = 0; i < recipes->total_recipes; i++) {
			fwrite(recipes->current, sizeof(Recipe), 1, fp);

			if (i == recipes->total_recipes - 1) {
				free(recipes->current);
				break;
			}

			recipes->current = recipes->current->next;

			free(recipes->current->prev);
		}

		fclose(fp);
	}

	free(recipes);
}

void add_in_recipes(Recipes* recipes, Recipe* new_recipe) {
	Recipe* first = recipes->first;
	Recipe* last = recipes->last;
	Recipe* temp_next = NULL;
	Recipe* temp_prev = NULL;

	recipes->current = new_recipe;
	recipes->total_recipes++;

	if (first == NULL) {
		new_recipe->next = new_recipe;
		new_recipe->prev = new_recipe;
		recipes->first = new_recipe;
		recipes->last = new_recipe;

		return;
	}

	if (strcmp(new_recipe->title, first->title) < 0) {
		new_recipe->prev = last;
		new_recipe->next = first;

		first->prev = new_recipe;
		last->next = new_recipe;

		recipes->first = new_recipe;
	} else if (strcmp(new_recipe->title, last->title) > 0) {
		new_recipe->next = first;
		new_recipe->prev = last;

		last->next = new_recipe;
		first->prev = new_recipe;

		recipes->last = new_recipe;
	} else {
		temp_next = recipes->first;

		while (strcmp(new_recipe->title, temp_next->title) > 0) {
			temp_next = temp_next->next;
		}

		temp_prev = temp_next->prev;

		new_recipe->next = temp_next;
		new_recipe->prev = temp_prev;

		temp_prev->next = new_recipe;
		temp_next->prev = new_recipe;
	}
}
