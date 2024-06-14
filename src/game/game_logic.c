#include "game_logic.h"
#include "grid_utils.h"
#include "typedefs.h"
#include <string.h>
void initialize_game(GameConfig *config) {
  Direction direction = HORIZONTAL;
  for (int i = 0; i < config->total_words; i++) {
    char *word = config->words[i];

    bool is_position_valid = false;
    SelectedWord selected_word;
    selected_word.word = config->words[i];
    selected_word.word_length = strlen(config->words[i]);
    GameState game_state;
    game_state.coords = malloc(selected_word.word_length * sizeof(int));
    int *coords;
    int position;
    if (direction == VERTICAL) {
      direction = HORIZONTAL;
    } else {
      direction = VERTICAL;
    }
    while (!is_position_valid) {

      position = choose_random_position(config->table_length);

      coords = change_position_to_coordinate(position, config->table_length);

      is_position_valid = validate_position(coords, config->table_length,
                                            selected_word, direction, config);
    }
    // Out of while loop, the position is valid.
    game_state.direction = direction;
    game_state.word = selected_word.word;
    game_state.word_length = selected_word.word_length;
    game_state.found = false;
    place_word_in_table(selected_word, coords, config, game_state);
    config->game_state[i] = game_state;
  }
  fill_grid_with_characters(config);
}