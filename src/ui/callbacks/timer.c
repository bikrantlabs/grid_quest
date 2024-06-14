#include "typedefs.h"
#include <gtk/gtk.h>

gboolean update_timer(gpointer user_data) {
  AppConfig *app_config = (AppConfig *)user_data;

  // Update the time

  app_config->game_config->timer_data->seconds++;
  if (app_config->game_config->timer_data->seconds == 60) {
    app_config->game_config->timer_data->seconds = 0;
    app_config->game_config->timer_data->minutes++;
  }

  // Update the label text
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%02d:%02d",
           app_config->game_config->timer_data->minutes,
           app_config->game_config->timer_data->seconds);
  gtk_label_set_text(GTK_LABEL(app_config->uiconfig->timer_label), buffer);

  return TRUE; // Continue calling the timeout function
}

void stop_timer(AppConfig *app_config) {
  if (app_config->game_config->timer_data->timer_id != 0) {
    g_source_remove(app_config->game_config->timer_data->timer_id);
    app_config->game_config->timer_data->timer_id = 0;
    // Optionally, update the label to show the current time
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%02d:%02d",
             app_config->game_config->timer_data->minutes,
             app_config->game_config->timer_data->seconds);
    gtk_label_set_text(GTK_LABEL(app_config->uiconfig->timer_label), buffer);
  }
}