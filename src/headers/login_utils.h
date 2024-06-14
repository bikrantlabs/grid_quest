#ifndef LOGIN_UTILS_H
#define LOGIN_UTILS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_USERS 100
void save_login_data(char *username, char *password);
bool check_user_exists(char *username, char *password);

#endif // GAME_LOGIC_H
