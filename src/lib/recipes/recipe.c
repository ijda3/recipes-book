#include "recipe.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LENGTH 100
#define TEXT_LENGTH 500

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

Recipes* load_recipes() {
	Recipes* recipes = malloc(sizeof(Recipes));
	Recipe* R1 = malloc(sizeof(Recipe));
	Recipe* R2 = malloc(sizeof(Recipe));
	Recipe* R3 = malloc(sizeof(Recipe));
	recipes->total_recipes = 3;
	recipes->current = R1;
	recipes->first = R1;
	recipes->last = R3;

	strcpy(R1->title, "Bolo");
	R1->total_time = 7200;
	strcpy(R1->author, "Senhor Barriga");
	R1->rating = 7.75;
	R1->use_count = 3;
	strcpy(R1->ingredient, "1 saco de trigo, 1 duzia de ovos");
	strcpy(R1->directions, "Jogar o trigo e os ovos fora e pedir pelo iFood");
	R1->prev = R3;
	R1->next = R2;

	strcpy(R2->title, "Suco de Tamarindo");
	R2->total_time = 1500;
	strcpy(R2->author, "Chaves");
	R2->rating = 3.75;
	R2->use_count = 12;
	strcpy(R2->ingredient, "1 saco de tamarindos, 1 balde de sorvete");
	strcpy(R2->directions, "Espremer os tamarindos, Adicionar agua, Dormir no barril");
	R2->prev = R1;
	R2->next = R3;

	strcpy(R3->title, "Miojo");
	R3->total_time = 180;
	strcpy(R3->author, "Ana Maria Braga");
	R3->rating = 10;
	R3->use_count = 82;
	strcpy(R3->ingredient, "1 saco de trigo, 1 duzia de ovos");
	strcpy(R3->directions, "Jogar o trigo e os ovos fora e pedir pelo iFood");
	R3->prev = R2;
	R3->next = R1;

	return recipes;
}

void add_recipe(Recipes* recipes) { printw("Add"); }

void remove_recipe(Recipes* recipes) {
	if (recipes->total_recipes > 0) {
		Recipe* temp_current = recipes->current;
		// if only 1 recipe saved, fix pointers of recipe_control
		if (recipes->total_recipes == 1) {
			recipes->current = NULL;
			recipes->first = NULL;
			recipes->last = NULL;
		} else {
			// set pointers of prev and next recipes
			recipes->current = recipes->current->next;
			recipes->current->prev = temp_current->prev;
			temp_current->prev->next = recipes->current;
			// set recipe_control pointers if current is first or last
			if (temp_current == recipes->first) {
				recipes->first = recipes->current;
			} else if (temp_current == recipes->last) {
				recipes->last = recipes->current;
			}
		}

		recipes->total_recipes--;
		free(temp_current);
	}
}

void edit_recipe(Recipes* recipes) { printw("edit"); }

void use_recipe(Recipes* recipes) { printw("use"); }

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
		printw("Vezes de preparo: %d\n", recipes->current->use_count);
		printw("Nota da receita: %.02f\n", recipes->current->rating);
	} else {
		printw("Nao ha receita cadastrada!");
	}
}

void save_recipes(Recipes* recipes) {
	FILE* fp;
	fp = fopen("database.bin", "wb");
	int i;
	// check if file was created
	if (fp == NULL) {
		printw("Erro ao criar o arquivo database.bin");
		return;
	}
	// save total_recipes at the start of the file to make loading it easier
	fwrite(&recipes->total_recipes, sizeof(int), 1, fp);
	// write and free each recipe
	for (i = 0; i < recipes->total_recipes; i++) {
		fwrite(recipes->current, sizeof(Recipe), 1, fp);
		// check if it's the last recipe
		if (i == recipes->total_recipes - 1) {
			free(recipes->current);
			break;
		}
		recipes->current = recipes->current->next;
		free(recipes->current->prev);
	}
	free(recipes);
	fclose(fp);
}
