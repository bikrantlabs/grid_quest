#include "callbacks.h"
#include "grid_utils.h"
#include "typedefs.h"
#include "word_utils.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
void generate_button_grids(AppConfig *app_config, GtkWidget *grid) {

  app_config->uiconfig->buttons =
      malloc(app_config->game_config->table_length * sizeof(GtkWidget **));
  for (int i = 0; i < app_config->game_config->table_length; ++i) {
    app_config->uiconfig->buttons[i] =
        malloc(app_config->game_config->table_length * sizeof(GtkWidget *));
  }
  int total_cells = app_config->game_config->table_length *
                    app_config->game_config->table_length;
  ClickedPositions *clicked_positions = malloc(sizeof(ClickedPositions));
  clicked_positions->positions = malloc(total_cells * sizeof(int));
  clicked_positions->clicked_count = 0;
  clicked_positions->max_size = total_cells;
  // Create buttons and add to grid
  for (int i = 0; i < app_config->game_config->table_length; ++i) {
    for (int j = 0; j < app_config->game_config->table_length; ++j) {
      char label[2];
      label[0] = app_config->game_config->table[i][j];
      label[1] = '\0';
      app_config->uiconfig->buttons[i][j] = gtk_button_new_with_label(label);
      int coords[2];
      coords[0] = i;
      coords[1] = j;
      int position = change_coordinate_to_position(
          coords, app_config->game_config->table_length);
      ButtonClickData *button_data = malloc(sizeof(ButtonClickData));
      button_data->new_position = position;
      button_data->button = app_config->uiconfig->buttons[i][j];
      button_data->app_config = app_config;
      button_data->clicked_positions = clicked_positions;
      gtk_widget_add_css_class(app_config->uiconfig->buttons[i][j],
                               "characters");
      g_signal_connect(app_config->uiconfig->buttons[i][j], "clicked",
                       G_CALLBACK(on_button_clicked), button_data);
      gtk_grid_attach(GTK_GRID(grid), app_config->uiconfig->buttons[i][j], j, i,
                      1, 1);
    }
  }
}
void generate_words_hints_grid(AppConfig *app_config) {
  app_config->uiconfig->word_hint_labels =
      malloc(app_config->game_config->total_words * sizeof(GtkWidget *));
  if (app_config->uiconfig->word_hint_labels == NULL) {
    // Handle memory allocation failure
    perror("Failed to allocate memory for labels");
    exit(EXIT_FAILURE);
  }

  app_config->uiconfig->score_grid = gtk_grid_new();
  GtkWidget *new_user_label = gtk_label_new(
      app_config->game_config->first_game == 1 ? "First Game"
                                               : "Previous Best: ");
  printf("First Game: %d\n", app_config->game_config->first_game);
  GtkWidget *previous_score =
      gtk_label_new(app_config->game_config->previous_score);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), new_user_label, 0,
                  0, app_config->game_config->first_game == 1 ? 2 : 1, 1);
  if (app_config->game_config->first_game == 0) {
    // Attaching to grid
    printf("\nAttaching to Grid: %s\n",
           app_config->game_config->first_game ? "True" : "False");
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), previous_score,
                    1, 0, 1, 1);
  } else {
    gtk_grid_set_row_homogeneous(GTK_GRID(app_config->uiconfig->score_grid),
                                 TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(app_config->uiconfig->score_grid),
                                    TRUE);
  }
  char attempts[300];
  GtkWidget *attempt_word = gtk_label_new("Attempts left: ");
  snprintf(attempts, sizeof(attempts), "%d", app_config->game_config->attempts);

  GtkWidget *label = gtk_label_new("WORDS:");
  app_config->uiconfig->timer_label = gtk_label_new("00:00");

  GtkWidget *attempt_label_wrapper = gtk_grid_new();
  gtk_widget_set_size_request(attempt_label_wrapper, 100, 50);

  gtk_grid_attach(GTK_GRID(attempt_label_wrapper), attempt_word, 0, 0, 1, 1);

  app_config->uiconfig->attempts_label = gtk_label_new(attempts);

  gtk_grid_attach(GTK_GRID(attempt_label_wrapper),
                  app_config->uiconfig->attempts_label, 1, 0, 1, 1);
  gtk_widget_add_css_class(label, "word_hint_label");
  gtk_widget_add_css_class(app_config->uiconfig->timer_label, "timer_label");
  gtk_widget_add_css_class(attempt_label_wrapper, "attempts_label");
  gtk_widget_add_css_class(new_user_label, "new_user_label");

  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                  app_config->uiconfig->score_grid, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                  new_user_label, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                  app_config->uiconfig->timer_label, 0, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                  attempt_label_wrapper, 0, 3, 1, 1);

  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid), label, 0, 4,
                  1, 1);
  // Create labels and add to grid
  for (int i = 0; i < app_config->game_config->total_words; ++i) {

    app_config->uiconfig->word_hint_labels[i] =
        gtk_label_new(uppercase(app_config->game_config->words[i]));
    gtk_widget_add_css_class(app_config->uiconfig->word_hint_labels[i],
                             "word_hint");
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                    app_config->uiconfig->word_hint_labels[i], 0, i + 5, 1, 1);
  }
}

void generate_game_score_grid(AppConfig *app_config) {

  char attempts[300];
  snprintf(attempts, sizeof(attempts), "%d", app_config->game_config->attempts);
  GtkWidget *label = gtk_label_new("You Won!");
  GtkWidget *label2 = gtk_label_new("Your Score");
  gtk_widget_add_css_class(label, "word_hint_label");

  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                  app_config->uiconfig->attempts_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid), label, 0, 1,
                  1, 1);
  // Create labels and add to grid
  for (int i = 0; i < app_config->game_config->total_words; ++i) {

    app_config->uiconfig->word_hint_labels[i] =
        gtk_label_new(uppercase(app_config->game_config->words[i]));
    gtk_widget_add_css_class(app_config->uiconfig->word_hint_labels[i],
                             "word_hint");
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->word_hints_grid),
                    app_config->uiconfig->word_hint_labels[i], 0, i + 2, 1, 1);
  }
}