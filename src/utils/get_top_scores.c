/**
 * A function to read top 10 scores from file and update the struct pointer.
 */
#include "file_utils.h"
#include "screens.h"
#include "typedefs.h"
#include <stdio.h>
#include <string.h>
void get_top_scores(AppConfig *app_config) {
  if (!app_config->game_config->top_scores) {
    printf("Top scores not initialized:");
  }
  app_config->game_config->top_scores =
      malloc(TOP_SCORE_LIMIT * sizeof(TopScores));
  FILE *fp = fopen("../scores.txt", "r");
  if (fp == NULL) {
    printf("Cannot open scores.txt\n");
    return;
  }
  char saved_username[100]; // Assuming each line in the file is no longer than
                            // 100
  int score;
  app_config->game_config->total_score_count = 0;
  // characters
  for (int i = 0; i < TOP_SCORE_LIMIT; i++) {
    if (fscanf(fp, "%s %d\n", saved_username, &score) != EOF) {
      app_config->game_config->top_scores[i].username = strdup(saved_username);
      app_config->game_config->top_scores[i].flat_seconds = score;
      app_config->game_config->total_score_count++;
      printf("Reading line %d\n", i);
    } else {
      break;
    }
  }
  fclose(fp);
  return;
}