#ifndef GRID_UTILS_H
#define GRID_UTILS_H
#include "typedefs.h"
#include <stdbool.h>

int choose_random_position(int grid_length);
bool validate_position(int *coords, int grid_length, SelectedWord word,
                       Direction direction, GameConfig *config);
bool is_cell_filled(GameConfig *config, int *coords);
Direction choose_random_direction();

int *change_position_to_coordinate(int number, int cols);
int change_coordinate_to_position(int *coords, int cols);
void place_word_in_table(SelectedWord word, int *coords, GameConfig *config,
                         GameState game_state);
void fill_grid_with_characters(GameConfig *config);
void initialize_grid(AppConfig *app_config);
#endif // GRID_UTILS_H
