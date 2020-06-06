#include "recipe.h"

#define DEFAULT_LENGTH 100

typedef struct {
	char title[DEFAULT_LENGTH];
	int total_time;
	char author[DEFAULT_LENGTH];
	float rating;
	int use_count;
	char** ingredient;
	char** directions;

	Recipe* prev;
	Recipe* next;
} Recipe;

struct recipe_control {
	Recipe* list;
	Recipe* current;
	Recipe* first;
	Recipe* last;
};

void show_recipe(Recipes* recipes);

Recipes* load_recipes() {}
void add_recipe(Recipes* recipes) {}
void remove_recipe(Recipes* recipes) {}
void edit_recipe(Recipes* recipes) {}
void use_recipe(Recipes* recipes) {}
void prev_recipe(Recipes* recipes) {}
void next_recipe(Recipes* recipes) {}
void show_recipe(Recipes* recipes) {}
void save_recipes(Recipes* recipes) {}
