#include "free_memory.h"
#include "typedefs.h"
void start_game_again(AppConfig *app_config) {
  free_timer_data(app_config);
  free_button_grids(app_config);
  free_label_grids(app_config);
  free_game_config(app_config);

  // TODO: Navigate to home page
  gtk_stack_set_visible_child_name(GTK_STACK(app_config->uiconfig->stack),
                                   "home_page");
}
void start_game_callback(GtkWidget *widget, gpointer data) {
  AppConfig *params = (AppConfig *)data;
  start_game_again(params);
}