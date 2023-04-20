#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 128

int main(int argc, char *argv[]) {
    char word[MAX_WORD_LEN];
    char *filename = "/usr/share/dict/words";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Unable to open file %s.\n", filename);
        exit(1);
    }

    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        exit(1);
    }

    strncpy(word, argv[1], MAX_WORD_LEN);

    char line[MAX_WORD_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, word) == 0) {
            printf("%s is in the dictionary!\n", word);
            fclose(file);
            exit(0);
        }
    }

    printf("%s is not in the dictionary.\n", word);
    fclose(file);
    exit(0);
}
