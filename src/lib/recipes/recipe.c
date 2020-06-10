#include "recipe.h"
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

void show_recipe(Recipes* recipes);

Recipes* load_recipes() {
	Recipes* recipes = malloc(sizeof(Recipes));
	Recipe* R1 = malloc(sizeof(Recipe));
	Recipe* R2 = malloc(sizeof(Recipe));
	Recipe* R3 = malloc(sizeof(Recipe));
	recipes->total_recipes = 0;
	recipes->current = R1;
	recipes->first = R1;
	recipes->last = R3;

	strcpy(R1->title, "Bolo");
	R1->total_time = 7200;
	strcpy(R1->author, "Senhor Barriga\n");
	R1->rating = 7.75;
	R1->use_count = 3;
	strcpy(R1->ingredient, "1 saco de trigo\n1 duzia de ovos\n");
	strcpy(R1->directions, "Jogar o trigo e os ovos fora e ligar chamar pelo iFood\n");
	R1->prev = R3;
	R1->next = R2;

	strcpy(R2->title, "Suco de Tamarindo\n");
	R2->total_time = 1500;
	strcpy(R2->author, "Chaves\n");
	R2->rating = 3.75;
	R1->use_count = 12;
	strcpy(R2->ingredient, "1 saco de tamarindos\n1 balde de sorvete\n");
	strcpy(R2->directions, "Espremer os tamarindos\nAdicionar agua\nDormir no barril\n");
	R2->prev = R1;
	R2->next = R3;

	strcpy(R3->title, "Miojo\n");
	R1->total_time = 180;
	strcpy(R3->author, "Ana Maria Braga\n");
	R1->rating = 10;
	R1->use_count = 82;
	strcpy(R3->ingredient, "1 saco de trigo\n1 duzia de ovos");
	strcpy(R3->directions, "Jogar o trigo e os ovos fora e ligar chamar pelo iFood");
	R3->prev = R2;
	R3->next = R1;

	return recipes;
}

void add_recipe(Recipes* recipes) {}

void remove_recipe(Recipes* recipes) {}

void edit_recipe(Recipes* recipes) {}

void use_recipe(Recipes* recipes) {}

void prev_recipe(Recipes* recipes) {
	recipes->current = recipes->current->prev;
	show_recipe(recipes);
}

void next_recipe(Recipes* recipes) {
	recipes->current = recipes->current->next;
	show_recipe(recipes);
}

void show_recipe(Recipes* recipes) {}

void save_recipes(Recipes* recipes) {}
