#include "get_words.h"
#include "typedefs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

RandomSelectedWords *get_words(Difficulty difficulty) {
  char *easy_words[] = {
      "dog",   "run",   "car",   "book",   "tree",  "bird",  "fish",  "blue",
      "jump",  "moon",  "home",  "fire",   "game",  "ship",  "ball",  "park",
      "kite",  "frog",  "rain",  "lamp",   "love",  "star",  "baby",  "rock",
      "duck",  "hand",  "flag",  "milk",   "door",  "tree",  "bird",  "road",
      "song",  "bear",  "cake",  "duck",   "farm",  "goat",  "hill",  "jeep",
      "lion",  "mice",  "nuts",  "oven",   "pink",  "quilt", "rice",  "soap",
      "taxi",  "unit",  "vase",  "whip",   "yoga",  "zebra", "apple", "beach",
      "chair", "dance", "email", "fruit",  "ghost", "horse", "igloo", "juice",
      "kayak", "lemon", "money", "north",  "olive", "pizza", "queen", "river",
      "snake", "tiger", "uncle", "violin", "whale", "xenon", "yacht", "zeus",
      "actor", "brush", "cloud", "dream",  "earth", "flute", "grass", "happy",
      "image", "joker", "karma", "laugh",  "mango", "ninja", "ocean", "panda",
      "quiet", "rhyme", "smile", "start",  "google"};
  int easy_words_count = sizeof(easy_words) / sizeof(easy_words[0]);
  char *medium_words[] = {
      "couch",  "mirror",  "clock",      "lamp",       "rug",   "shirt",
      "pants",  "dress",   "jacket",     "hat",        "socks", "shoes",
      "gloves", "dog",     "cat",        "bird",       "fish",  "rabbit",
      "turtle", "hamster", "guinea pig", "bicycle",    "car",   "bus",
      "train",  "plane",   "boat",       "motorcycle", "truck", "pen",
      "pencil", "marker",
  };
  int medium_words_count = sizeof(medium_words) / sizeof(medium_words[0]);
  char *hard_words[] = {
      "abacus",   "bagpipes", "cobweb",   "dwarves", "elbow",
      "fishhook", "gazebo",   "hangnail", "ivory",   "jigsaw",
      "kilobyte", "larynx",   "marquis",
  };
  int hard_words_count = sizeof(hard_words) / sizeof(hard_words[0]);

  int total_words = 2;
  switch (difficulty) {
  case EASY:
    total_words = 2;
    break;
  case MEDIUM:
    total_words = 3;
    break;
  case HARD:
    total_words = 4;
    break;
  default:
    total_words = 2;
    break;
  }

  // Initialize random seed
  srand(time(NULL));

  RandomSelectedWords *word_data;
  word_data = malloc(sizeof(RandomSelectedWords));
  if (word_data == NULL) {
    perror("Failed to allocate memory for word_data");
    exit(EXIT_FAILURE);
  }

  word_data->total_words = total_words;

  char **selected_words = malloc(total_words * sizeof(char *));
  if (selected_words == NULL) {
    perror("Failed to allocate memory for selected_words");
    exit(EXIT_FAILURE);
  }

  bool *chosen = calloc(easy_words_count, sizeof(bool));
  if (chosen == NULL) {
    perror("Failed to allocate memory for chosen");
    free(selected_words);
    exit(EXIT_FAILURE);
  }

  switch (difficulty) {
  case EASY:
    for (int i = 0; i < total_words; i++) {
      int random_idx;
      do {
        random_idx = rand() % easy_words_count;
      } while (chosen[random_idx]);
      selected_words[i] = easy_words[random_idx];
      chosen[random_idx] = true;
    }
    break;
  case MEDIUM:
    for (int i = 0; i < total_words; i++) {
      int random_idx;
      do {
        random_idx = rand() % medium_words_count;
      } while (chosen[random_idx]);
      selected_words[i] = medium_words[random_idx];
      chosen[random_idx] = true;
    }
    break;
  case HARD:
    for (int i = 0; i < total_words; i++) {
      int random_idx;
      do {
        random_idx = rand() % hard_words_count;
      } while (chosen[random_idx]);
      selected_words[i] = hard_words[random_idx];
      chosen[random_idx] = true;
    }
    break;
  default:
    for (int i = 0; i < total_words; i++) {
      int random_idx;
      do {
        random_idx = rand() % medium_words_count;
      } while (chosen[random_idx]);
      selected_words[i] = medium_words[random_idx];
      chosen[random_idx] = true;
    }
    break;
  }
  free(chosen);
  word_data->words = selected_words;

  return word_data;
}
