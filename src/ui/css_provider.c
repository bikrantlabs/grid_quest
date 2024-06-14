#include <gtk/gtk.h>

void apply_css(const char *css_file_path) {
  // Create a CSS provider and load the CSS file
  // CSS
  GtkCssProvider *css_provider = gtk_css_provider_new();
  GFile *css_file = g_file_new_for_path(css_file_path);
  gtk_css_provider_load_from_file(css_provider, css_file);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(css_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
}