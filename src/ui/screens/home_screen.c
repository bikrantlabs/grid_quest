/**
 * Choose Difficulty in Start Screen.
 */
#include "callbacks.h"
#include "file_utils.h"
#include "screens.h"
#include "typedefs.h"
static void navigate_to_top_scores(GtkButton *button, gpointer user_data) {
  AppConfig *app_config = (AppConfig *)user_data;
  // app_config->game_config->top_scores =
  //     malloc(TOP_SCORE_LIMIT * sizeof(TopScores));
  get_top_scores(app_config);
  // Generate Labels here
  for (int i = 0; i < app_config->game_config->total_score_count; i++) {
    printf("%s %d\n", app_config->game_config->top_scores[i].username,
           app_config->game_config->top_scores[i].flat_seconds);
  }
  generate_top_score_grids(app_config);
  gtk_stack_set_visible_child_name(GTK_STACK(app_config->uiconfig->stack),
                                   "top_scores_page");
}
GtkWidget *home_screen(AppConfig *app_config) {
  GtkWidget *easy_button;
  GtkWidget *medium_button;
  GtkWidget *hard_button;
  GtkWidget *top_scores_button;

  easy_button = gtk_button_new_with_label("Easy");
  g_signal_connect(easy_button, "clicked", G_CALLBACK(select_difficulty),
                   app_config);
  medium_button = gtk_button_new_with_label("Medium");
  g_signal_connect(medium_button, "clicked", G_CALLBACK(select_difficulty),
                   app_config);
  hard_button = gtk_button_new_with_label("Hard");
  g_signal_connect(hard_button, "clicked", G_CALLBACK(select_difficulty),
                   app_config);
  top_scores_button = gtk_button_new_with_label("Top Scores");
  g_signal_connect(top_scores_button, "clicked",
                   G_CALLBACK(navigate_to_top_scores), app_config);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *label = gtk_label_new("Select difficulty");
  gtk_widget_add_css_class(label, "select-difficulty-label");
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), easy_button, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), medium_button, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), hard_button, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), top_scores_button, 0, 4, 1, 1);

  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  gtk_widget_add_css_class(grid, "select-level-grid");
  gtk_widget_add_css_class(easy_button, "select-level-btn");
  gtk_widget_add_css_class(medium_button, "select-level-btn");
  gtk_widget_add_css_class(hard_button, "select-level-btn");
  return grid;
}