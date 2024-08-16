#include "free_memory.h"
#include "typedefs.h"
#include <gtk/gtk.h>
void free_button_grids(AppConfig *app_config) {

  if (app_config->uiconfig->buttons) {
    for (int i = 0; i < app_config->game_config->table_length; ++i) {
      if (app_config->uiconfig->buttons[i]) {
        for (int j = 0; j < app_config->game_config->table_length; ++j) {
          if (app_config->uiconfig->buttons[i][j]) {
            gtk_widget_unparent(app_config->uiconfig->buttons[i][j]);
            g_object_unref(app_config->uiconfig->buttons[i][j]);
          }
        }
        free(app_config->uiconfig->buttons[i]);
      }
    }
    free(app_config->uiconfig->buttons);
  }
}
void free_position_data(ClickedPositions *clicked_positions) {
  if (clicked_positions->positions)
    free(clicked_positions->positions);
  if (clicked_positions)
    free(clicked_positions);
}
void free_label_grids(AppConfig *app_config) {
  if (app_config->uiconfig->word_hint_labels) {
    for (int i = 0; i < app_config->game_config->total_words; ++i) {
      if (app_config->uiconfig->word_hint_labels[i]) {
        gtk_widget_unparent(
            app_config->uiconfig
                ->word_hint_labels[i]); // Remove the widget from its parent
        g_object_unref(
            app_config->uiconfig
                ->word_hint_labels[i]); // Decrease the reference count
      }
    }
    free(app_config->uiconfig->word_hint_labels);
  }
  if (app_config->uiconfig->attempts_label) {
    gtk_widget_unparent(app_config->uiconfig->attempts_label);
    g_object_unref(app_config->uiconfig->attempts_label);
  }
  if (app_config->uiconfig->timer_label) {
    gtk_widget_unparent(app_config->uiconfig->timer_label);
    g_object_unref(app_config->uiconfig->timer_label);
  }
  if (app_config->uiconfig->score_grid) {

    gtk_widget_unparent(app_config->uiconfig->score_grid);
    g_object_unref(app_config->uiconfig->score_grid);
  }
}

void free_game_config(AppConfig *app_config) {

  for (int i = 0; i < app_config->game_config->total_words; i++) {
    if (app_config->game_config->game_state[i].coords)
      free(app_config->game_config->game_state[i].coords);
  }
  if (app_config->game_config->words != NULL) {
    for (int i = 0; i < app_config->game_config->total_words; i++) {
      free(app_config->game_config->words[i]);
    }
    free(app_config->game_config->words);
  }

  if (app_config->game_config->table != NULL) {
    for (int i = 0; i < app_config->game_config->table_length; i++) {
      free(app_config->game_config->table[i]); // Free each row
    }
    free(app_config->game_config->table); // Free the array of pointers
  }
}

void free_timer_data(AppConfig *app_config) {
  if (app_config && app_config->game_config) {
    if (app_config->game_config->timer_data) {
      free(app_config->game_config->timer_data);
    }
  }
}