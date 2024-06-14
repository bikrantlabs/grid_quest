#include "screens.h"
#include "typedefs.h"
#include <gtk/gtk.h>
GtkWidget *create_page(GtkWidget *stack, CreatePageParams page_params) {
  // Home Page
  GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_top(page, 10);
  gtk_widget_set_margin_bottom(page, 10);
  gtk_widget_set_margin_start(page, 10);
  gtk_widget_set_margin_end(page, 10);
  gtk_stack_add_titled(GTK_STACK(stack), page, page_params.name,
                       page_params.name);

  return page;
}