#include "login_utils.h"
#include "word_utils.h"
#include <stdio.h>

void save_login_data(char *username, char *password) {
  FILE *fp = fopen("../credentials.txt", "a+");
  if (fp == NULL) {
    fputs("Cannot open users.txt file.", stderr);
    return;
  }
  char *removed_whitespaces = remove_whitespaces(username);
  fprintf(fp, "\n%s %s", removed_whitespaces, password);
  fclose(fp);
  return;
}
bool check_user_exists(char *username, char *password) {
  FILE *fp = fopen("../credentials.txt", "r");
  if (fp == NULL) {
    fputs("Cannot open credentials.txt file.", stderr);
    return false;
  }

  char saved_username[100]; // Assuming each line in the file is no longer than
                            // 100
  char saved_password[100];
  // characters
  while (fscanf(fp, "\n%s %s", saved_username, saved_password) != EOF) {
    if (strcmp(saved_username, username) == 0 &&
        strcmp(saved_password, password) == 0) {
      fclose(fp);
      return true;
    }
  }
  fclose(fp);
  return false;
}