#include "file_utils.h"
#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to check if a number is in an array
int is_in_array(int *array, int size, int num) {
  for (int i = 0; i < size; i++) {
    if (array[i] == num) {
      return 1;
    }
  }
  return 0;
}

// Function to load words from the file
LoadWordsReturn *load_words(const char *filepath, const int total_words) {
  FILE *in;
  char line[256];
  int lines = 0;

  // Open the file
  in = fopen(filepath, "r");
  if (in == NULL) {
    fputs("Cannot open dictionary file.", stderr);
    return NULL;
  }

  // First pass: count the number of lines
  while (fgets(line, sizeof(line), in) != NULL) {
    lines++;
  }

  // Allocate memory for the LoadWordsReturn structure
  LoadWordsReturn *word_data = malloc(sizeof(LoadWordsReturn));
  if (word_data == NULL) {
    fputs("Memory allocation failed for LoadWordsReturn.", stderr);
    fclose(in);
    return NULL;
  }

  word_data->total_words = total_words;

  if (lines == 0) {
    fputs("No lines found in the file.", stderr);
    fclose(in);
    free(word_data);
    return NULL;
  }

  // Allocate memory for the words array
  word_data->words = malloc(lines * sizeof(char *));
  if (word_data->words == NULL) {
    fputs("Memory allocation failed for words array.", stderr);
    fclose(in);
    free(word_data);
    return NULL;
  }

  // Allocate memory for tracking random line numbers
  int *selected_lines = malloc(lines * sizeof(int));
  if (selected_lines == NULL) {
    fputs("Memory allocation failed for selected lines array.", stderr);
    fclose(in);
    free(word_data->words);
    free(word_data);
    return NULL;
  }
  int selected_count = 0;

  // // Initialize random number generator
  // srand(time(NULL));

  // Read random lines and select words
  rewind(in);
  for (int i = 0; i < word_data->total_words; i++) {
    int random_line;
    do {
      random_line = rand() % lines;
    } while (is_in_array(selected_lines, selected_count, random_line));
    selected_lines[selected_count++] = random_line;

    // Move to the random line
    rewind(in);
    for (int j = 0; j <= random_line; j++) {
      fgets(line, sizeof(line), in);
    }

    // Copy the selected word
    strtok(line, "\n"); // Remove newline character
    word_data->words[i] = strdup(line);
    if (word_data->words[i] == NULL) {
      fputs("Memory allocation failed for word string.", stderr);
      // Free previously allocated memory before returning
      for (int k = 0; k < i; k++) {
        free(word_data->words[k]);
      }
      free(word_data->words);
      free(word_data);
      free(selected_lines);
      fclose(in);
      return NULL;
    }
  }

  // Free the selected lines array
  free(selected_lines);

  // Close the file
  fclose(in);
  return word_data;
}
