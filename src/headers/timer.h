
#ifndef TIMER_H
#define TIMER_H

#include "typedefs.h"
#include <gtk/gtk.h>

gboolean update_timer(gpointer user_data);
void stop_timer(AppConfig *app_config);
#endif