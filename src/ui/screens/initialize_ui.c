#include "headers/typedefs.h"
#include "screens.h"
void destroy_g(GtkWidget *widget, gpointer data) { printf("Destroy"); }
void initialize_ui(AppConfig *app_config, GtkWidget *window) {
  // Create Stack
  GtkWidget *stack = gtk_stack_new();
  app_config->uiconfig->stack = stack;

  gtk_stack_set_transition_type(GTK_STACK(stack),
                                GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  gtk_window_set_child(GTK_WINDOW(window), stack);

  // Home Page
  CreatePageParams home_page_params = {"home_page", "Home Page"};
  CreatePageParams login_page_params = {"login_page", "Login Page"};
  GtkWidget *home_page = create_page(stack, home_page_params);
  GtkWidget *login_page = create_page(stack, login_page_params);
  app_config->uiconfig->login_page = login_page;
  // Create the game page
  CreatePageParams game_page_garams = {"game_page", "Game Page"};
  GtkWidget *game_page = create_page(stack, game_page_garams);
  gtk_widget_set_halign(game_page, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(game_page, GTK_ALIGN_CENTER);
  app_config->uiconfig->game_page = game_page;

  // Top Scores Page
  CreatePageParams top_scores_page_params = {"top_scores_page",
                                             "Top Scores Page"};
  GtkWidget *_top_scores_page = create_page(stack, top_scores_page_params);
  // GtkWidget *top_scores_page_grid = top_score_screen(app_config);
  GtkWidget *top_score_parent_grid = gtk_grid_new();
  gtk_box_append(GTK_BOX(_top_scores_page), top_score_parent_grid);
  app_config->uiconfig->top_score_parent_grid = top_score_parent_grid;
  // Wrapper Grid
  GtkWidget *wrapper_grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(wrapper_grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(wrapper_grid), TRUE);
  gtk_box_append(GTK_BOX(game_page), wrapper_grid);
  //
  GtkWidget *button_grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(button_grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(button_grid), TRUE);
  gtk_widget_set_halign(game_page, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(game_page, GTK_ALIGN_CENTER);
  app_config->uiconfig->button_grid = button_grid;
  gtk_grid_attach(GTK_GRID(wrapper_grid), button_grid, 0, 0, 8, 1);
  //
  GtkWidget *word_hints_grid = gtk_grid_new();
  gtk_widget_add_css_class(word_hints_grid, "word_hints_grid");
  // gtk_grid_set_row_homogeneous(GTK_GRID(word_hints_grid), TRUE);
  // gtk_grid_set_column_homogeneous(GTK_GRID(word_hints_grid), TRUE);

  app_config->uiconfig->word_hints_grid = word_hints_grid;
  gtk_grid_attach(GTK_GRID(wrapper_grid), word_hints_grid, 9, 0, 2, 1);

  GtkWidget *start_screen_grid = home_screen(app_config);
  gtk_box_append(GTK_BOX(home_page), start_screen_grid);

  // GtkWidget *login_screen = login_screen(app_config);
  GtkWidget *login_screen_grid = login_screen(app_config);
  gtk_box_append(GTK_BOX(login_page), login_screen_grid);

  g_signal_connect(stack, "destroy", G_CALLBACK(destroy_g), NULL);
}
