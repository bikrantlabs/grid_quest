#include "callbacks.h"
#include "file_utils.h"
#include "game_logic.h"
#include "get_words.h"
#include "grid_utils.h"
#include "screens.h"
#include "time_converter.h"
#include "timer.h"
#include "typedefs.h"
#include "word_utils.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
void select_difficulty(GtkButton *button, gpointer user_data) {
  AppConfig *params = (AppConfig *)user_data;
  const gchar *label = gtk_button_get_label(button);
  // Free memory for top scores after we enter game screen

  // Allocate all memory only after selecting difficulty
  LoadWordsReturn *words_data;
  params->game_config->words = malloc(5 * sizeof(char *));
  params->game_config->timer_data = malloc(sizeof(TimerData));
  params->game_config->timer_data->minutes = 0;
  params->game_config->timer_data->seconds = 0;
  params->game_config->attempts = 0;

  if (strcmp(label, "Easy") == 0) {
    params->game_config->attempts += 4;
    params->game_config->difficulty = EASY;
    words_data = load_words("../src/data/easy_words.txt", 1);
  } else if (strcmp(label, "Medium") == 0) {
    params->game_config->attempts += 3;
    params->game_config->difficulty = MEDIUM;
    words_data = load_words("../src/data/medium_words.txt", 1);
  } else if (strcmp(label, "Hard") == 0) {
    params->game_config->attempts += 2;
    params->game_config->difficulty = HARD;
    words_data = load_words("../src/data/hard_words.txt", 1);
  } else {
    params->game_config->attempts += 4;
    params->game_config->difficulty = MEDIUM;
    words_data = load_words("../src/data/medium_words.txt", 5);
  }
  // Get Scores:

  get_score(params);

  RandomSelectedWords *random_word = get_words(params->game_config->difficulty);
  params->game_config->words = words_data->words;
  params->game_config->total_words = words_data->total_words;

  int longest_word = longest_word_in_array(params->game_config->words,
                                           params->game_config->total_words);

  params->game_config->table_length = longest_word + 2;

  params->game_config->game_state =
      malloc(params->game_config->total_words * sizeof(GameState));
  initialize_grid(params);
  initialize_game(params->game_config);
  generate_button_grids(params, params->uiconfig->button_grid);
  generate_words_hints_grid(params);
  params->game_config->timer_data->timer_id =
      g_timeout_add_seconds(1, update_timer, params);

  gtk_stack_set_visible_child_name(GTK_STACK(params->uiconfig->stack),
                                   "game_page");
}