/**
 * A header file handling functions for different screens/pages
 */
#ifndef PAGES_H
#define PAGES_H

#include "typedefs.h"
#include <gtk/gtk.h>
#define TOP_SCORE_LIMIT 10
GtkWidget *create_page(GtkWidget *stack, CreatePageParams page_params);
GtkWidget *home_screen(AppConfig *app_config);
GtkWidget *login_screen(AppConfig *app_config);
GtkWidget *top_score_screen(AppConfig *app_config);
void generate_button_grids(AppConfig *app_config, GtkWidget *grid);
GtkWidget *generate_top_score_grids(AppConfig *app_config);
void generate_words_hints_grid(AppConfig *app_config);
void initialize_ui(AppConfig *app_config, GtkWidget *window);
#endif