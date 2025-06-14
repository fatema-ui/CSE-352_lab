#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(const char *str) {
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isValidIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return 0;
    for (int i = 1; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    if (isKeyword(str))
        return 0;
    return 1;
}

int main() {
    char id[100];
    FILE *inputFile, *outputFile;

    // Step 1: Get input and save to input.txt
    printf("Enter an identifier:\n");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    inputFile = fopen("input.txt", "w");
    fputs(id, inputFile);
    fclose(inputFile);

    // Step 2: Read from input.txt and validate identifier
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    fgets(id, sizeof(id), inputFile);
    id[strcspn(id, "\n")] = '\0';
    fclose(inputFile);

    if (isValidIdentifier(id)) {
        fprintf(outputFile, "Valid identifier: %s\n", id);
    } else {
        fprintf(outputFile, "Invalid identifier: %s\n", id);
    }

    fclose(outputFile);
    return 0;
}

