/**
 * Source file for word related utilities functions
 */

#include "word_utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *uppercase(char *str) {
  // Allocate memory for the new string
  // +1 for the null terminator
  char *result = malloc((strlen(str) + 1) * sizeof(char));
  if (result == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  // Convert each character to uppercase
  for (int i = 0; str[i] != '\0'; ++i) {
    result[i] = toupper(str[i]);
  }

  // Null-terminate the new string
  result[strlen(str)] = '\0';

  return result;
}

int longest_word_in_array(char **word, int total_words) {
  int max_length = 0;
  for (int i = 0; i < total_words; i++) {
    int current_length = strlen(word[i]);
    if (current_length > max_length) {
      max_length = current_length;
    }
  }
  return max_length;
}

/**
 * Function to generate random characters from words array.
 */
char generate_random_character(char **words, int total_words) {

  // Choose a random string from the array
  int random_index = rand() % total_words;
  char *selected_string = words[random_index];

  // Choose a random character from the selected string
  int string_length = strlen(selected_string);
  int random_char_index = rand() % string_length;

  return toupper(selected_string[random_char_index]);
}

SelectedWord choose_random_word(char **word, int total_words) {
  int random_index = rand() % total_words;
  SelectedWord word_data = {.word = word[random_index], strlen(*word)};
  return word_data;
}

int is_number_in_array(int arr[], int size, int number) {

  for (int i = 0; i < size; i++) {
    if (arr[i] == number) {
      return 1;
    }
  }
  return 0;
}
/**
 Checks if array two contains all elements of array one, and returns true or
 false
*/
bool is_word_found(int selected_coords[], int selected_count, int word_coords[],
                   int word_count) {
  if (selected_count < word_count) {
    return false;
  }

  int matched[word_count];
  memset(matched, 0, sizeof(matched));

  for (int i = 0; i < word_count; ++i) {
    for (int j = 0; j < selected_count; ++j) {
      if (word_coords[i] == selected_coords[j]) {
        matched[i] = 1;
        break;
      }
    }
  }

  for (int i = 0; i < word_count; ++i) {
    if (matched[i] == 0) {
      return false;
    }
  }

  return true;
}