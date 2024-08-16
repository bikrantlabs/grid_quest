#include "callbacks.h"
#include "file_utils.h"
#include "game_logic.h"
#include "get_words.h"
#include "grid_utils.h"
#include "screens.h"
#include "timer.h"
#include "typedefs.h"
#include "word_utils.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
void select_difficulty(GtkButton *button, gpointer user_data) {
  AppConfig *params = (AppConfig *)user_data;
  const gchar *label = gtk_button_get_label(button);

  // Allocate all memory only after selecting difficulty

  params->game_config->timer_data = malloc(sizeof(TimerData));
  params->game_config->timer_data->minutes = 0;
  params->game_config->timer_data->seconds = 0;
  params->game_config->attempts = 0;

  if (strcmp(label, "Easy") == 0) {
    params->game_config->attempts += ADDITIONAL_EASY_ATTEMPTS;
    params->game_config->difficulty = EASY;
    LoadWordsReturn *words_data =
        load_words("../src/data/easy_words.txt", TOTAL_EASY_WORDS);
    params->game_config->words = words_data->words;
    params->game_config->total_words = words_data->total_words;
  } else if (strcmp(label, "Medium") == 0) {
    params->game_config->attempts += ADDITIONAL_MEDIUM_ATTEMPTS;
    params->game_config->difficulty = MEDIUM;
    // words_data = load_words("../src/data/medium_words.txt",
    // TOTAL_MEDIUM_WORDS);
  } else if (strcmp(label, "Hard") == 0) {
    params->game_config->attempts += ADDITIONAL_HARD_ATTEMPTS;
    params->game_config->difficulty = HARD;
    LoadWordsReturn *words_data =
        load_words("../src/data/hard_words.txt", TOTAL_HARD_WORDS);
    params->game_config->words = words_data->words;
    params->game_config->total_words = words_data->total_words;
  } else {
    params->game_config->attempts += ADDITIONAL_MEDIUM_ATTEMPTS;
    params->game_config->difficulty = MEDIUM;
    LoadWordsReturn *words_data =
        load_words("../src/data/medium_words.txt", TOTAL_MEDIUM_WORDS);
    params->game_config->words = words_data->words;
    params->game_config->total_words = words_data->total_words;
  }
  // Get Scores:

  get_score(params);

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