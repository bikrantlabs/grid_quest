#include "login_utils.h"

bool username_taken(char *username, char *password) {
  FILE *fp = fopen("../credentials.txt", "r");
  if (fp == NULL) {
    fputs("Cannot open credentials.txt file.", stderr);
    return false;
  }

  char saved_username[100]; // Assuming each line in the file is no longer than
                            // 100
  char saved_password[100];
  // characters
  while (fscanf(fp, "%s %s\n", saved_username, saved_password) != EOF) {
    if (strcmp(saved_username, username) == 0 &&
        strcmp(saved_password, password) != 0) {
      fclose(fp);
      return true;
    }
  }
  fclose(fp);
  return false;
}