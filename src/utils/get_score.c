#include "file_utils.h"
#include "login_utils.h"
#include "time_converter.h"
#include "typedefs.h"
#include <stdio.h>
bool check_score_exists(AppConfig *app_config) {
  FILE *fp = fopen("../scores.txt", "r");
  if (fp == NULL) {
    fputs("Cannot open scores.txt file(check_score_exists).\n", stderr);
    // app_config->game_config->first_game = 1;
    return false;
  }

  char saved_username[100]; // Assuming each line in the file is no longer than
                            // 100
  int score;
  // characters
  while (fscanf(fp, "%s %d\n", saved_username, &score) != EOF) {
    if (strcmp(saved_username, app_config->game_config->username) == 0) {
      fclose(fp);
      return true;
    }
  }
  fclose(fp);
  return false;
}
void get_score(AppConfig *app_config) {
  FILE *fp = fopen("../scores.txt", "r");
  if (fp == NULL) {
    fputs("Cannot open scores.txt file(get_score)\n", stderr);
    app_config->game_config->first_game = 1;
    return;
  }
  char _username[MAX_USERNAME_LENGTH];
  int score;
  if (check_score_exists(app_config)) {
    printf("Score for username %s exists", app_config->game_config->username);
    app_config->game_config->first_game = 0;
    while (fscanf(fp, "%s %d\n", _username, &score) != EOF) {
      if (strcmp(_username, app_config->game_config->username) == 0) {
        fclose(fp);
        app_config->game_config->previous_score_flat = score;
        Time *time = convert_to_minutes(score);
        snprintf(app_config->game_config->previous_score,
                 sizeof(app_config->game_config->previous_score), "%02d:%02d",
                 time->minutes, time->seconds);
      }
    }
  } else {
    printf("\nScore for username %s doesn't exists\n",
           app_config->game_config->username);
    app_config->game_config->first_game = 1;
    fclose(fp);
  }
}
