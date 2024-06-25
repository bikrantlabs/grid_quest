#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "typedefs.h"
#include <gtk/gtk.h>
#include <stdbool.h>
#define ADDITIONAL_EASY_ATTEMPTS 4
#define ADDITIONAL_MEDIUM_ATTEMPTS 3
#define ADDITIONAL_HARD_ATTEMPTS 2
#define TOTAL_EASY_WORDS 5
#define TOTAL_MEDIUM_WORDS 5
#define TOTAL_HARD_WORDS 5
void initialize_game(GameConfig *config);

// Check if the cell is already filled

// Returns Coordinate in array [int row, int col]

#endif // GAME_LOGIC_H
