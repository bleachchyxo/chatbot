#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_NUM_WORDS 20

int is_stopword(char *word) {
   char *stopwords[] = {
      "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
      "has", "have", "he", "in", "is", "it", "its", "of", "on", "that",
      "the", "to", "was", "were", "with"
   };
   int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);

   for (int i = 0; i < num_stopwords; i++) {
      if (strcmp(word, stopwords[i]) == 0) {
         return 1; // true
      }
   }

   return 0; // false
}

int is_word_in_dict(char *word) {
   FILE *fp;
   char line[MAX_WORD_LENGTH];

   fp = fopen("/usr/share/dict/words", "r");
   if (fp == NULL) {
      perror("Error opening dictionary file");
      exit(EXIT_FAILURE);
   }

   while (fgets(line, MAX_WORD_LENGTH, fp)) {
      // Remove newline character from line
      line[strcspn(line, "\n")] = 0;
     
      if (strcmp(word, line) == 0) {
         fclose(fp);
         return 1; // true
      }
   }

   fclose(fp);
   return 0; // false
}

void remove_suffixes(char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], int num_words) {
    const char* suffixes[] = {"s", "es", "ed", "ing"};
    for (int i = 0; i < num_words; i++) {
        for (int j = 0; j < sizeof(suffixes) / sizeof(suffixes[0]); j++) {
            int suffix_len = strlen(suffixes[j]);
            int word_len = strlen(words[i]);

            if (word_len > suffix_len && strcmp(words[i] + word_len - suffix_len, suffixes[j]) == 0) {
                words[i][word_len - suffix_len] = '\0';
                if (!is_word_in_dict(words[i])) {
                    strcat(words[i], suffixes[j]);
                }
                break;
            }
        }
    }
}

int main() {
   char sentence[2000] = "This is a sentence with the very purpose of testing my coding skills";
   char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];

   // Split the sentence into words
   int num_words = 0;
   char *token = strtok(sentence, " ");
   while (token != NULL && num_words < MAX_NUM_WORDS) {
      if (!is_stopword(token)) {
         strcpy(words[num_words], token);
         num_words++;
      }
      token = strtok(NULL, " ");
   }

   remove_suffixes(words, num_words);

   for (int i = 0; i < num_words; i++) {
      printf("%s ", words[i]);
   }

   printf("\n");
   return 0;
}
