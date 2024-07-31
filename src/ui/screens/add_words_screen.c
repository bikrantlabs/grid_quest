
#include "file_utils.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include "typedefs.h"
#include <stdbool.h>
#include <string.h>
static void select_easy(GtkWidget *check_button, gpointer user_data) {
  AppConfig *app_config = (AppConfig *)(user_data);
  gboolean is_active =
      gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));

  if (is_active) {
    app_config->game_config->custom_word_category = EASY;
  }
}
static void select_medium(GtkWidget *check_button, gpointer user_data) {
  AppConfig *app_config = (AppConfig *)(user_data);
  gboolean is_active =
      gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
  if (is_active) {

    app_config->game_config->custom_word_category = MEDIUM;
  }
}
static void select_hard(GtkWidget *check_button, gpointer user_data) {
  AppConfig *app_config = (AppConfig *)(user_data);
  gboolean is_active =
      gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
  if (is_active) {
    app_config->game_config->custom_word_category = HARD;
  }
}
RadioButtonGroup create_radio_buttons(AppConfig *app_config) {

  RadioButtonGroup group;

  group.easy_button = gtk_check_button_new_with_label("Easy");
  group.medium_button = gtk_check_button_new_with_label("Medium");
  group.hard_button = gtk_check_button_new_with_label("Hard");

  gtk_check_button_set_group(GTK_CHECK_BUTTON(group.medium_button),
                             GTK_CHECK_BUTTON(group.easy_button));
  gtk_check_button_set_group(GTK_CHECK_BUTTON(group.hard_button),
                             GTK_CHECK_BUTTON(group.easy_button));
  switch (app_config->game_config->custom_word_category) {
  case EASY:
    gtk_check_button_set_active(GTK_CHECK_BUTTON(group.easy_button), true);
    app_config->game_config->custom_word_category = EASY;
    break;
  case MEDIUM:
    gtk_check_button_set_active(GTK_CHECK_BUTTON(group.medium_button), true);
    app_config->game_config->custom_word_category = MEDIUM;
    break;
  case HARD:
    gtk_check_button_set_active(GTK_CHECK_BUTTON(group.hard_button), true);
    app_config->game_config->custom_word_category = HARD;
    break;
  default:
    gtk_check_button_set_active(GTK_CHECK_BUTTON(group.easy_button), true);
    app_config->game_config->custom_word_category = EASY;
    break;
  }
  g_signal_connect(G_OBJECT(group.easy_button), "toggled",
                   G_CALLBACK(select_easy), app_config);
  g_signal_connect(G_OBJECT(group.medium_button), "toggled",
                   G_CALLBACK(select_medium), app_config);
  g_signal_connect(G_OBJECT(group.hard_button), "toggled",
                   G_CALLBACK(select_hard), app_config);

  return group;
}
static void navigate_to_home_page(GtkWidget *button, gpointer data) {
  AppConfig *app_config = (AppConfig *)(data);
  gtk_stack_set_visible_child_name(GTK_STACK(app_config->uiconfig->stack),
                                   "home_page");
}
static void button_press(GtkWidget *widget, gpointer data) {
  AppConfig *app_config = (AppConfig *)(data);
  const char *text =
      gtk_entry_buffer_get_text((app_config->uiconfig->new_word_input));
  // g_print("%s", text);
  if (text && strlen(text) > 0) {
    switch (app_config->game_config->custom_word_category) {
    case EASY:
      save_new_word_to_file("../src/data/easy_words.txt", text);
      break;
    case MEDIUM:
      save_new_word_to_file("../src/data/medium_words.txt", text);
      break;
    case HARD:
      save_new_word_to_file("../src/data/hard_words.txt", text);
      break;
    default:
      save_new_word_to_file("../src/data/easy_words.txt", text);
      break;
    }
    gtk_entry_buffer_set_text(app_config->uiconfig->new_word_input, "", 0);
  }
}

GtkWidget *add_words_screen(AppConfig *app_config) {
  GtkWidget *wrapper_grid = gtk_grid_new();
  GtkWidget *radio_grid = gtk_grid_new();
  RadioButtonGroup group = create_radio_buttons(app_config);
  app_config->uiconfig->new_word_input = gtk_entry_buffer_new(NULL, -1);

  // Center Align Wrapper Grid
  gtk_widget_set_halign(wrapper_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(wrapper_grid, GTK_ALIGN_CENTER);

  // Attach Radio grid to wrapper grid
  gtk_grid_attach(GTK_GRID(wrapper_grid), radio_grid, 0, 0, 1, 1);

  // Attach buttons to radio grid

  gtk_grid_attach(GTK_GRID(radio_grid), group.easy_button, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(radio_grid), group.medium_button, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(radio_grid), group.hard_button, 2, 0, 1, 1);
  // Attach Radio grid to wrapper grid

  // Create a Input Field
  GtkWidget *new_word_grid = gtk_grid_new();
  GtkWidget *new_word_label = gtk_label_new(
      "Type word and press \"Enter\"\n\n~3-5 characters for Easy words\n\n~5-9 "
      "characters for Medium words\n\n~9-12 characters for Hard words");

  GtkWidget *new_word_input =
      gtk_entry_new_with_buffer(app_config->uiconfig->new_word_input);
  gtk_grid_attach(GTK_GRID(new_word_grid), new_word_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(new_word_grid), new_word_input, 0, 1, 1, 1);
  g_signal_connect(new_word_input, "activate", G_CALLBACK(button_press),
                   app_config);
  gtk_grid_attach(GTK_GRID(wrapper_grid), new_word_grid, 0, 1, 1, 1);

  // Create back to home button and attach to grid
  GtkWidget *back_button = gtk_button_new_with_label("Back to Home");
  g_signal_connect(back_button, "clicked", G_CALLBACK(navigate_to_home_page),
                   app_config);

  //  Add CSS Classes
  gtk_widget_add_css_class(new_word_grid, "mb-20");
  gtk_widget_add_css_class(radio_grid, "mb-20");
  gtk_widget_add_css_class(new_word_label, "new_word_label");
  gtk_widget_add_css_class(back_button, "login-btn");
  gtk_grid_attach(GTK_GRID(wrapper_grid), back_button, 0, 2, 1, 1);
  return wrapper_grid;
}