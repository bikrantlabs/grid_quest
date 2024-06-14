/**
 * A header file containing callbacks function for UI components
 */
#ifndef FREE_MEMORY_H
#define FREE_MEMORY_H
#include "typedefs.h"
#include <gtk/gtk.h>
void free_button_grids(AppConfig *app_config);
void free_label_grids(AppConfig *app_config);
void free_game_config(AppConfig *app_config);
void free_position_data(ClickedPositions *clicked_positions);
void free_timer_data(AppConfig *app_config);
#endif