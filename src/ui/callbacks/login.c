#include "callbacks.h"
#include "login_utils.h"
#include "typedefs.h"
#include <gtk/gtk.h>
/**
 * If username/password matches in credentials.txt, user will be logged in,
 * otherwise a new user will be created.
 */
void login(GtkButton *button, gpointer user_data) {
  AppConfig *app_config = (AppConfig *)user_data;

  // TODO: Prevent conflicting usernames
  const char *username =
      gtk_entry_buffer_get_text((app_config->uiconfig->username_input));
  const char *password =
      gtk_entry_buffer_get_text((app_config->uiconfig->password_input));
  if (strlen(username) > 0 && strlen(password) > 0) {
    app_config->game_config->username = (char *)malloc(strlen(username) + 1);
    app_config->game_config->password = (char *)malloc(strlen(password) + 1);
    strcpy(app_config->game_config->username, username);
    strcpy(app_config->game_config->password, password);
    if (check_user_exists(app_config->game_config->username,
                          app_config->game_config->password)) {
      printf("User Exists\n");
      app_config->game_config->new_user = false;

    } else {
      printf("User Doesn't Exists\n");
      save_login_data(app_config->game_config->username,
                      app_config->game_config->password);
      app_config->game_config->new_user = true;
    }
    gtk_stack_set_visible_child_name(GTK_STACK(app_config->uiconfig->stack),
                                     "home_page");
  } else {
    g_print("Invalid credentials format found\n");
  }
}