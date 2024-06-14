
#include "callbacks.h"
#include "screens.h"
#include "typedefs.h"
GtkWidget *login_screen(AppConfig *app_config) {
  app_config->uiconfig->username_input = gtk_entry_buffer_new(NULL, -1);
  app_config->uiconfig->password_input = gtk_entry_buffer_new(NULL, -1);
  GtkWidget *login_btn = gtk_button_new_with_label("Login");
  gtk_widget_add_css_class(login_btn, "login-btn");
  g_signal_connect(login_btn, "clicked", G_CALLBACK(login), app_config);

  GtkWidget *grid = gtk_grid_new();
  GtkWidget *label = gtk_label_new("Login");
  gtk_widget_add_css_class(label, "login-label");

  GtkWidget *username_grid = gtk_grid_new();
  GtkWidget *username_label = gtk_label_new("Username");
  GtkWidget *username_input =
      gtk_entry_new_with_buffer(app_config->uiconfig->username_input);
  gtk_grid_attach(GTK_GRID(username_grid), username_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(username_grid), username_input, 0, 1, 1, 1);
  gtk_widget_add_css_class(username_grid, "username-grid");

  GtkWidget *password_grid = gtk_grid_new();
  GtkWidget *password_label = gtk_label_new("Password");
  GtkWidget *password_input =
      gtk_entry_new_with_buffer(app_config->uiconfig->password_input);
  gtk_entry_set_visibility(GTK_ENTRY(password_input),
                           FALSE); // Hide the entered text
  gtk_entry_set_invisible_char(GTK_ENTRY(password_input), '*');
  gtk_grid_attach(GTK_GRID(password_grid), password_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(password_grid), password_input, 0, 1, 1, 1);

  // gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  // gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), username_grid, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), password_grid, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), login_btn, 0, 3, 1, 1);

  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  gtk_widget_add_css_class(grid, "login-grid");
  return grid;
}