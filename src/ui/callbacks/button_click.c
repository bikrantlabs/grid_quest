#include "callbacks.h"
#include "file_utils.h"
#include "free_memory.h"
#include "grid_utils.h"
#include "time_converter.h"
#include "timer.h"
#include "typedefs.h"
#include "ui_logic.h"
#include "word_utils.h"
#include <gtk/gtk.h>
#include <stdbool.h>
void remove_clicked_position(int index, ClickedPositions *positions) {
  for (int i = index; i < positions->clicked_count - 1; ++i) {
    positions->positions[i] = positions->positions[i + 1];
  }
  positions->clicked_count--;
}
void add_or_remove_clicked_position(ClickedPositions *position,
                                    GameConfig *config, int new_position) {
  for (int i = 0; i < position->clicked_count; ++i) {
    if (position->positions[i] == new_position) {
      remove_clicked_position(i, position);
      return;
    }
  }
  position->positions[position->clicked_count++] = new_position;
  config->attempts--;
}

void check_user_selection(ClickedPositions *position, GameConfig *game_config,
                          UiConfig *uiconfig) {
  for (int i = 0; i < game_config->total_words; ++i) {
    if (!game_config->game_state[i].found &&
        is_word_found(position->positions, position->clicked_count,
                      game_config->game_state[i].coords,
                      game_config->game_state[i].word_length)) {

      for (int j = 0; j < game_config->game_state[i].word_length; j++) {
        int *coords = change_position_to_coordinate(
            game_config->game_state[i].coords[j], game_config->table_length);

        gtk_widget_set_sensitive(uiconfig->buttons[coords[0]][coords[1]],
                                 FALSE);
        gtk_widget_add_css_class(uiconfig->buttons[coords[0]][coords[1]],
                                 "disabled_button");
      }

      gtk_widget_add_css_class(uiconfig->word_hint_labels[i], "label_strike");
      game_config->game_state[i].found = true;
    }
  }
}
bool game_complete(GameConfig *game_config) {
  for (int i = 0; i < game_config->total_words; i++) {
    if (!game_config->game_state[i].found) {
      return false;
    }
  }
  return true;
}
void on_button_clicked(GtkWidget *widget, gpointer data) {
  ButtonClickData *button_data =
      (ButtonClickData *)(data); // Retrieve the integer data

  add_or_remove_clicked_position(button_data->clicked_positions,
                                 button_data->app_config->game_config,
                                 button_data->new_position);
  // Check subset
  check_user_selection(button_data->clicked_positions,
                       button_data->app_config->game_config,
                       button_data->app_config->uiconfig);

  update_attempts(button_data->app_config->game_config->attempts,
                  button_data->app_config->uiconfig->attempts_label);
  // If attempts is 0, show Game Over screen.
  if (button_data->app_config->game_config->attempts <= 0 &&
      !game_complete(button_data->app_config->game_config)) {
    open_dialog(false, button_data->app_config);
    stop_timer(button_data->app_config);
    free_position_data(button_data->clicked_positions);
  }
  if (game_complete(button_data->app_config->game_config)) {
    int current_score = button_data->app_config->game_config->timer_data->flat;
    int prev_score = button_data->app_config->game_config->previous_score_flat;
    printf("Game Complete! New User: %d",
           button_data->app_config->game_config->new_user ? 1 : -1);

    open_dialog(true, button_data->app_config);
    stop_timer(button_data->app_config);
    free_position_data(button_data->clicked_positions);
    // Only save score if new score is better than previous
    button_data->app_config->game_config->timer_data->flat = convert_to_seconds(
        button_data->app_config->game_config->timer_data->minutes,
        button_data->app_config->game_config->timer_data->seconds);

    if (button_data->app_config->game_config->first_game == 1) {
      save_scores(button_data->app_config);
      button_data->app_config->game_config->first_game = 0;
    } else {
      if (button_data->app_config->game_config->previous_score_flat >
          button_data->app_config->game_config->timer_data->flat) {
        save_scores(button_data->app_config);
      }
    }
  };
  if (gtk_widget_has_css_class(widget, "selected")) {
    gtk_widget_remove_css_class(widget, "selected");
  } else {
    gtk_widget_add_css_class(widget, "selected");
  }
}
