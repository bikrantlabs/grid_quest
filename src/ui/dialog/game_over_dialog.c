#include "callbacks.h"
#include "typedefs.h"
#include "ui_logic.h"
#include <gtk/gtk.h>
static void button_clicked(GtkButton *button, gpointer user_data) {
  AppConfig *params = (AppConfig *)user_data;
  // Print the label of the clicked button
  g_print("%s clicked\n", gtk_button_get_label(button));
  gtk_window_destroy(GTK_WINDOW(params->uiconfig->window));
}
static void on_response(GtkDialog *dialog, gint response_id,
                        gpointer user_data) {
  AppConfig *params = (AppConfig *)user_data;
  switch (response_id) {
  case GTK_RESPONSE_OK:
    g_print("OK button clicked\n");
    start_game_again(params);
    break;
  case GTK_RESPONSE_CANCEL:
    g_print("Cancel button clicked\n");
    gtk_window_destroy(GTK_WINDOW(params->uiconfig->window));
    // Perform action for Cancel button
    break;
  default:
    g_print("Other response received\n");
    // Destroy the dialog
    start_game_again(params);
    break;
  }
  gtk_window_destroy(GTK_WINDOW(dialog));
}
void open_dialog(bool game_won, AppConfig *app_config) {
  GtkWidget *dialog, *label, *content_area;
  GtkDialogFlags flags;

  // Create the widgets
  dialog = gtk_dialog_new_with_buttons(
      "Game over!", GTK_WINDOW(app_config->uiconfig->window),
      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "Play again",
      GTK_RESPONSE_OK, "Exit game", GTK_RESPONSE_CANCEL, NULL);
  content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  label = gtk_label_new(game_won ? "You Won!" : "You Lose!");

  gtk_widget_add_css_class(label, "game-over-label");

  GtkWidget *play_again_btn =
      gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
  gtk_widget_add_css_class(play_again_btn, "dialog_ok-btn");

  GtkWidget *exit_game_btn = gtk_dialog_get_widget_for_response(
      GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
  gtk_widget_add_css_class(exit_game_btn, "dialog_cancel-btn");

  // Connect response signal
  g_signal_connect(dialog, "response", G_CALLBACK(on_response), app_config);

  gtk_box_append(GTK_BOX(content_area), label);
  gtk_widget_show(dialog);
}
