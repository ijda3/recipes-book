#ifndef HEADER_RECIPE
#define HEADER_RECIPE

typedef struct recipe_control Recipes;

Recipes* load_recipes();
void add_recipe(Recipes* recipes);
void remove_recipe(Recipes* recipes);
void edit_recipe(Recipes* recipes);
void use_recipe(Recipes* recipes);
void prev_recipe(Recipes* recipes);
void next_recipe(Recipes* recipes);
void show_recipe(Recipes* recipes);
void save_recipes(Recipes* recipes);

#endif
