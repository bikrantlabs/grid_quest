#ifndef TIME_CONVERTER_H
#define TIME_CONVERTER_H

#include "typedefs.h"
#include <gtk/gtk.h>

int convert_to_seconds(int minutes, int seconds);
Time *convert_to_minutes(int seconds);
#endif