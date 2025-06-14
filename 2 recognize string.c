#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isAsteriskBPlus(const char *str) {
    int i = 0;

    // Count 'a's (zero or more)
    while (str[i] == 'a') {
        i++;
    }

    // There must be at least one 'b'
    int bCount = 0;
    while (str[i] == 'b') {
        bCount++;
        i++;
    }

    // If bCount >= 1 and we reached the end of the string
    return bCount >= 1 && str[i] == '\0';
}

int main() {
    char str[100];
    FILE *inputFile, *outputFile;

    // Step 1: Get input from user and write to input.txt
    printf("Enter a string:\n");
    fgets(str, sizeof(str), stdin);

    // Remove newline if exists
    str[strcspn(str, "\n")] = '\0';

    inputFile = fopen("input.txt", "w");
    if (!inputFile) {
        printf("Error opening input file.\n");
        return 1;
    }
    fputs(str, inputFile);
    fclose(inputFile);

    // Step 2: Process input from input.txt and write result to output.txt
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error with files.\n");
        return 1;
    }

    fgets(str, sizeof(str), inputFile);
    str[strcspn(str, "\n")] = '\0';  // Remove newline again if present

    if (strcmp(str, "a") == 0) {
        fputs("String matches: 'a'\n", outputFile);
    } else if (strcmp(str, "aab") == 0) {
        fputs("String matches: 'aab'\n", outputFile);
    } else if (isAsteriskBPlus(str)) {
        fputs("String matches: 'a*b+'\n", outputFile);
    } else {
        fputs("String does not match any given pattern.\n", outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

