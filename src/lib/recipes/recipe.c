#include "recipe.h"
#include <stdlib.h>

#define DEFAULT_LENGTH 100

typedef struct recipe {
	char title[DEFAULT_LENGTH];
	int total_time;
	char author[DEFAULT_LENGTH];
	float rating;
	int use_count;
	char** ingredient;
	char** directions;

	struct recipe* prev;
	struct recipe* next;
} Recipe;

struct recipe_control {
	int total_recipes;
	Recipe* list;
	Recipe* current;
	Recipe* first;
	Recipe* last;
};

void show_recipe(Recipes* recipes);

Recipes* load_recipes() {
	Recipes* recipes = malloc(sizeof(Recipes));
	recipes->total_recipes = 0;

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
