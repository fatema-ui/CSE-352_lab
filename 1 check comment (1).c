#include <stdio.h>
#include <string.h>

int main() {
    char line[100];
    FILE *inputFile, *outputFile;

    // Step 1: Get input from console and write to input.txt
    printf("Enter a line of code:\n");
    fgets(line, sizeof(line), stdin);

    inputFile = fopen("input.txt", "w");
    if (!inputFile) {
        printf("Error opening input file.\n");
        return 1;
    }
    fputs(line, inputFile);
    fclose(inputFile);

    // Step 2: Read from input.txt and write result to output.txt
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error with files.\n");
        return 1;
    }

    fgets(line, sizeof(line), inputFile);
    fclose(inputFile);

    if (line[0] == '/' && line[1] == '/') {
        fputs("This is a single-line comment.\n", outputFile);
    } else if (line[0] == '/' && line[1] == '*') {
        int len = strlen(line);
        if (line[len - 3] == '*' && line[len - 2] == '/') {
            fputs("This is a multi-line comment.\n", outputFile);
        } else {
            fputs("This might be an incomplete multi-line comment.\n", outputFile);
        }
    } else {
        fputs("This is not a comment.\n", outputFile);
    }

    fclose(outputFile);
    return 0;
}
