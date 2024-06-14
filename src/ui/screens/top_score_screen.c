#include "file_utils.h"
#include "screens.h"
#include "time_converter.h"
#include "typedefs.h"
#include <stdbool.h>
#define TOP_SCORE_LIMIT 10
char *concatenate_strings(const char *str1, const char *str2,
                          const char *str3) {
  // Calculate the total length of the concatenated string
  size_t total_length = strlen(str1) + strlen(str2) + strlen(str3) +
                        1; // +1 for the null terminator

  // Allocate memory for the concatenated string
  char *result = (char *)malloc(total_length * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  // Initialize the result string
  result[0] = '\0';

  // Concatenate the strings
  strcpy(result, str1);
  strcat(result, str2);
  strcat(result, str3);

  return result;
}
void go_home(GtkWidget *widget, gpointer data) {
  AppConfig *app_config = (AppConfig *)data;
  gtk_stack_set_visible_child_name(GTK_STACK(app_config->uiconfig->stack),
                                   "home_page");
  free(app_config->game_config->top_scores);
  gtk_widget_unparent(app_config->uiconfig->score_grid);
  g_object_unref(app_config->uiconfig->score_grid);
}

GtkWidget *generate_top_score_grids(AppConfig *app_config) {
  GtkWidget *score_grid = gtk_grid_new();
  app_config->uiconfig->score_grid = score_grid;
  // Create header labels inside boxes
  GtkWidget *rank_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *time_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  GtkWidget *rank_label = gtk_label_new("Rank");
  GtkWidget *username_label = gtk_label_new("Username");
  GtkWidget *time_label = gtk_label_new("Time (seconds)");
  gtk_box_append(GTK_BOX(rank_box), rank_label);
  gtk_box_append(GTK_BOX(username_box), username_label);
  gtk_box_append(GTK_BOX(time_box), time_label);
  gtk_widget_add_css_class(rank_box, "table_header");
  gtk_widget_add_css_class(username_box, "table_header");
  gtk_widget_add_css_class(time_box, "table_header");
  // Attach header boxes to the grid
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), rank_box, 0, 0, 1,
                  1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), username_box, 1,
                  0, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), time_box, 2, 0, 1,
                  1);

  app_config->uiconfig->top_score_labels =
      malloc(TOP_SCORE_LIMIT * sizeof(GtkWidget *) * 3); // 3 columns
  if (app_config->uiconfig->top_score_labels == NULL) {
    // Handle memory allocation failure
    perror("Failed to allocate memory for top score labels");
    exit(EXIT_FAILURE);
  }

  // get_top_scores(app_config);

  for (int i = 0; i < app_config->game_config->total_score_count; ++i) {
    char rank_text[16];
    char time_text[10];

    snprintf(rank_text, sizeof(rank_text), "%d", i + 1);
    Time *time =
        convert_to_minutes(app_config->game_config->top_scores[i].flat_seconds);
    snprintf(time_text, sizeof(time_text), "%02d:%02d", time->minutes,
             time->seconds);

    GtkWidget *rank_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *time_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *rank_label = gtk_label_new(rank_text);
    GtkWidget *username_label =
        gtk_label_new(app_config->game_config->top_scores[i].username);
    GtkWidget *time_label = gtk_label_new(time_text);

    gtk_box_append(GTK_BOX(rank_box), rank_label);
    gtk_box_append(GTK_BOX(username_box), username_label);
    gtk_box_append(GTK_BOX(time_box), time_label);

    gtk_widget_set_halign(rank_label, GTK_ALIGN_START);
    gtk_widget_set_halign(username_label, GTK_ALIGN_START);
    gtk_widget_set_halign(time_label, GTK_ALIGN_START);

    // Attach boxes to the grid
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), rank_box, 0,
                    i + 1, 1, 1);
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), username_box, 1,
                    i + 1, 1, 1);
    gtk_grid_attach(GTK_GRID(app_config->uiconfig->score_grid), time_box, 2,
                    i + 1, 1, 1);

    app_config->uiconfig->top_score_labels[i * 3] = rank_label;
    gtk_widget_add_css_class(app_config->uiconfig->top_score_labels[i * 3],
                             "table_data");
    app_config->uiconfig->top_score_labels[i * 3 + 1] = username_label;
    gtk_widget_add_css_class(app_config->uiconfig->top_score_labels[i * 3 + 1],
                             "table_data");
    app_config->uiconfig->top_score_labels[i * 3 + 2] = time_label;
    gtk_widget_add_css_class(app_config->uiconfig->top_score_labels[i * 3 + 2],
                             "table_data");
  }

  gtk_widget_set_halign(app_config->uiconfig->top_score_parent_grid,
                        GTK_ALIGN_CENTER);
  gtk_widget_set_valign(app_config->uiconfig->top_score_parent_grid,
                        GTK_ALIGN_CENTER);
  GtkWidget *label = gtk_label_new("Top Scores!");
  gtk_widget_add_css_class(label, "top_scores");
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->top_score_parent_grid), label,
                  0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->top_score_parent_grid),
                  app_config->uiconfig->score_grid, 0, 1, 1, 1);
  GtkWidget *go_home_button = gtk_button_new_with_label("Go back");
  g_signal_connect(go_home_button, "clicked", G_CALLBACK(go_home), app_config);
  gtk_widget_add_css_class(go_home_button, "go_home_button");
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->top_score_parent_grid),
                  go_home_button, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(app_config->uiconfig->top_score_parent_grid),
                  app_config->uiconfig->score_grid, 0, 0, 1, 1);

  return score_grid;
}

GtkWidget *top_score_screen(AppConfig *app_config) {
  GtkWidget *grid = gtk_grid_new();
  app_config->uiconfig->top_score_parent_grid = grid;
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  return grid;
}