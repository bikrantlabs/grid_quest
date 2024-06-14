#include "time_converter.h"
#include <stdlib.h>
int convert_to_seconds(int minutes, int seconds) {
  return minutes * 60 + seconds;
}
Time *convert_to_minutes(int seconds) {
  Time *time = malloc(sizeof(Time));
  time->minutes = seconds / 60;
  time->seconds = seconds % 60;
  return time;
}