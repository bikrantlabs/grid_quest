#include "ui_logic.h"
#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));

  GtkApplication *app =
      gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(setup_ui), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return 1;
}
