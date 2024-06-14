/**
 * Source file for grid related utilities functions
 */
#include "grid_utils.h"
#include "headers/word_utils.h"
#include "stdlib.h"
#include "typedefs.h"
#include <ctype.h>
void initialize_grid(AppConfig *app_config) {
  app_config->game_config->table =
      malloc(app_config->game_config->table_length * sizeof(char *));
  if (app_config->game_config->table == NULL) {
    // Handle memory allocation failure
    perror("Failed to allocate memory for grid rows");
  }

  for (int i = 0; i < app_config->game_config->table_length; ++i) {
    app_config->game_config->table[i] =
        malloc(app_config->game_config->table_length * sizeof(char));
    if (app_config->game_config->table[i] == NULL) {
      // Handle memory allocation failure
      perror("Failed to allocate memory for grid columns");
      // Free previously allocated memory
      for (int j = 0; j < i; ++j) {
        free(app_config->game_config->table[j]);
      }
      free(app_config->game_config->table);
    }

    // Initialize each element to '\0'
    for (int j = 0; j < app_config->game_config->table_length; ++j) {
      app_config->game_config->table[i][j] = '\0';
    }
  }
}
bool validate_position(int *coords, int grid_length, SelectedWord word,
                       Direction direction, GameConfig *config) {
  // printf("Validating position for :%s\n", word.word);
  int c = coords[0];
  int c1 = coords[1];
  if (direction == VERTICAL) {

    bool available_spaces =
        word.word_length <= grid_length - coords[0] ? true : false;
    // printf("V: Word = %s, Length = %d", word.word, word.word_length);
    if (available_spaces) {
      // Check there are no other letters already filled there
      for (int i = coords[0]; i < word.word_length + coords[0]; i++) {
        // printf("Char: %c", config.table[i][coords[1]]);
        if (config->table[i][coords[1]] != '\0') {
          // printf("V: Returning false from null checker.....\n");
          return false;
        }
      }
      return true;
    } else {
      // printf("V: Returning false SNA.....\n");
      return false;
    }
  } else {
    bool available_spaces =
        word.word_length <= grid_length - coords[1] ? true : false;
    // printf("H: Word = %s, Length = %d", word.word, word.word_length);
    if (available_spaces) {

      for (int i = coords[1]; i < word.word_length + coords[1]; i++) {
        if (config->table[coords[0]][i] != '\0') {
          // printf("H: Returning false from null checker.....\n");
          return false;
        }
      }

      return true;
    } else {
      // printf("H: Returning false from SNA.....\n");
      return false;
    }
  }
  return false;
}

Direction choose_random_direction() {

  int random_index = rand() % 1;
  return random_index == 1 ? VERTICAL : HORIZONTAL;
}

int choose_random_position(int grid_length) {
  int totalSquares = grid_length * grid_length;
  int position = rand() % totalSquares;
  return position;
}

void place_word_in_table(SelectedWord word, int *coords, GameConfig *config,
                         GameState game_state) {
  for (int i = 0; i <= word.word_length; i++) {
    if (game_state.word[i] == '\0') {
      continue;
    }
    if (game_state.direction == HORIZONTAL) {
      config->table[coords[0]][coords[1] + i] = toupper(game_state.word[i]);
      int myCoords[2];
      myCoords[0] = coords[0];
      myCoords[1] = coords[1] + i;
      int position =
          change_coordinate_to_position(myCoords, config->table_length);
      game_state.coords[i] = position;
      // Whenever we place a letter in grid, increase no. of attempts
      config->attempts++;
    } else {
      config->table[coords[0] + i][coords[1]] = toupper(game_state.word[i]);
      int myCoords[2];
      myCoords[0] = coords[0] + i;
      myCoords[1] = coords[1];
      int position =
          change_coordinate_to_position(myCoords, config->table_length);
      game_state.coords[i] = position;
      // Whenever we place a letter in grid, increase no. of attempts
      config->attempts++;
    }
  }
}

void fill_grid_with_characters(GameConfig *config) {
  for (int i = 0; i < config->table_length; i++) {
    for (int j = 0; j < config->table_length; j++) {
      if (config->table[i][j] == '\0') {
        config->table[i][j] =
            generate_random_character(config->words, config->total_words);
      } else {
      }
    }
  }
}

int *change_position_to_coordinate(int number, int cols) {

  int *coords = malloc(sizeof(int) * 2);

  if (number == 0) {
    coords[0] = 0;
    coords[1] = 1;
    return coords;
  }
  if (number % cols == 0 && number != 0) {
    // The inputted number is on last column.
    coords[1] = cols - 1;
    coords[0] = number / cols - 1;
  } else {
    coords[0] = number / cols;
    coords[1] = number % cols - 1;
  }

  return coords;
}

int change_coordinate_to_position(int *coords, int cols) {
  return cols * coords[0] + coords[1] + 1;
}
