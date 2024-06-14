#include "callbacks.h"

void update_attempts(int attempts, GtkWidget *label) {
  char label_text[300];
  snprintf(label_text, sizeof(label_text), "%d", attempts);
  gtk_label_set_text(GTK_LABEL(label), label_text);
}