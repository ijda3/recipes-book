#include "../src/lib/recipes/recipe.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	Recipes* recipes = load_recipes();
	Recipe* new_recipe = malloc(sizeof(Recipe));

	strcpy(new_recipe->title, argv[1]);
	new_recipe->total_time = atoi(argv[2]);
	new_recipe->rating = atof(argv[3]);
	strcpy(new_recipe->ingredient, argv[4]);
	strcpy(new_recipe->directions, argv[5]);
	strcpy(new_recipe->author, argv[6]);
	new_recipe->use_count = 0;

	add_in_recipes(recipes, new_recipe);
	save_recipes(recipes);

	return 0;
}
