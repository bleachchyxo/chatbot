#include <stdio.h>
#include <string.h>

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

int main() {
   char sentence[2000] = "This is a long sentence that we will split into words";
   char words[20][100]; // 100 words of maximum length 100

   // Split the sentence into words
   int i = 0;
   char *token = strtok(sentence, " ");
   while (token != NULL && i < 20) {
      if (!is_stopword(token)) {
         strcpy(words[i], token);
         i++;
      }
      token = strtok(NULL, " ");
   }

    const char* suffixes[] = {"s", "es", "ed", "ing"};
    int numWords = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < numWords; i++) {
        for (int j = 0; j < sizeof(suffixes) / sizeof(suffixes[0]); j++) {
            int suffixLen = strlen(suffixes[j]);
            int wordLen = strlen(words[i]);

            if (wordLen > suffixLen && strcmp(words[i] + wordLen - suffixLen, suffixes[j]) == 0) {
                words[i][wordLen - suffixLen] = '\0';
                break;
            }
        }

        printf("%s ", words[i]);
    }

    printf("\n");
    return 0;
}
