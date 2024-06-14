#include "file_utils.h"
#include "login_utils.h"
#include "time_converter.h"
#include <stdio.h>
#include <string.h>
typedef struct {
  int score;
  char username[MAX_USERNAME_LENGTH];
} UserScore;
// Comparison function for sorting
int compare(const void *a, const void *b) {
  const UserScore *user1 = (const UserScore *)a;
  const UserScore *user2 = (const UserScore *)b;
  return user1->score - user2->score; // Sort in descending order
}

void update_or_add_user(UserScore *users, int *num_users, const char *username,
                        int score) {
  int found = 0;
  for (int i = 0; i < *num_users; i++) {
    if (strcmp(users[i].username, username) == 0) {
      users[i].score = score; // Update score if username already exists
      found = 1;
      break;
    }
  }
  if (!found) {
    // Add new user if not found
    strcpy(users[*num_users].username, username);
    users[*num_users].score = score;
    (*num_users)++;
  }
}

void save_scores(AppConfig *app_config) {
  FILE *fp;

  fp = fopen("../scores.txt", "a+");

  if (fp == NULL) {
    printf("Cannot open scores.txt for writing\n");
    return;
  }

  UserScore users[MAX_USERS];
  int num_users = 0;

  // Read all data from the file and store in users array
  char username[MAX_USERNAME_LENGTH];
  int score;
  while (fscanf(fp, "%s %d", username, &score) != EOF) {
    update_or_add_user(users, &num_users, username, score);
  }
  fclose(fp);

  int seconds =
      convert_to_seconds(app_config->game_config->timer_data->minutes,
                         app_config->game_config->timer_data->seconds);

  update_or_add_user(users, &num_users, app_config->game_config->username,
                     seconds);
  qsort(users, num_users, sizeof(UserScore), compare);

  // Open the file in write mode to save updated scores
  fp = fopen("../scores.txt", "w");
  if (fp == NULL) {
    printf("Cannot open scores.txt for writing\n");
    return;
  }

  // Write all new sorted data to the file
  for (int i = 0; i < num_users; i++) {
    fprintf(fp, "%s %d\n", users[i].username, users[i].score);
  }

  fclose(fp);
  return;
}
