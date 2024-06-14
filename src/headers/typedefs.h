#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <gtk/gtk.h>
#include <stdbool.h>
typedef enum Direction { HORIZONTAL, VERTICAL } Direction;
typedef enum Difficulty { EASY, MEDIUM, HARD } Difficulty;

// Struct for savin game state like total words placed, their positions, etc
typedef struct {
  int *coords;
  char *word;
  int word_length;
  Direction direction;
  bool found;
} GameState;
// The config struct needed to initialize the game
typedef struct {
  int minutes;
  int seconds;
} Time;
typedef struct {
  int minutes;
  int seconds;
  int flat;
  guint timer_id; // Timer ID to manage the timeout function
  GtkWidget *stack;
} TimerData;

typedef struct {
  char *username;
  int flat_seconds;
} TopScores;

typedef struct {
  int total_words;
  int table_length;
  int total_score_count;
  char *username;
  char *password;
  bool new_user;
  int first_game;
  char *filepath;
  char **words;
  char **table;
  int attempts;
  char previous_score[10];
  int previous_score_flat;
  TopScores *top_scores;
  Difficulty difficulty;
  GameState *game_state;
  TimerData *timer_data;
} GameConfig;

typedef struct {
  char *word;
  int word_length;
} SelectedWord;

typedef struct {
  char *name;
  char *title;
} CreatePageParams;

typedef struct {
  char **words;
  int total_words;
} RandomSelectedWords;

typedef struct {
  int clicked_count;
  int *positions;
  int max_size;
} ClickedPositions;

typedef struct {
  GtkWidget *attempts_label;
  GtkWidget *stack;
  GtkWidget *button_grid;
  GtkWidget *game_page;
  GtkWidget ***buttons;
  GtkWidget **word_hint_labels;
  GtkWidget *word_hints_grid;
  GtkWidget *login_page;
  GtkWidget *window;
  GtkWidget *timer_label;
  GtkEntryBuffer *username_input;
  GtkEntryBuffer *password_input;
  GtkWidget **top_score_labels;
  GtkWidget *score_grid;
  GtkWidget *top_score_parent_grid;
} UiConfig;

typedef struct {
  GameConfig *game_config;
  UiConfig *uiconfig;
} AppConfig;

typedef struct {
  int new_position;
  ClickedPositions *clicked_positions;
  AppConfig *app_config;
  GtkWidget *button;
} ButtonClickData;
typedef struct {
  int total_words;
  char **words;
} LoadWordsReturn;

#endif // DATA_H
