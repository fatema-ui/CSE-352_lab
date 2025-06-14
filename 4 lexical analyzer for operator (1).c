#include <stdio.h>
#include <string.h>

int isOperator(char *str) {
    // Known operators
    const char *operators[] = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=",
        "++", "--", "+=", "-=", "*=", "/=", "&&", "||", "!"
    };
    int n = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, operators[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[100], temp[3]; // temp holds up to 2-char operators
    FILE *inputFile, *outputFile;

    // Step 1: Get input and save to input.txt
    printf("Enter a line with operators:\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    inputFile = fopen("input.txt", "w");
    fputs(input, inputFile);
    fclose(inputFile);

    // Step 2: Read from input.txt and analyze operators
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    fgets(input, sizeof(input), inputFile);
    fclose(inputFile);

    int i = 0;
    while (input[i] != '\0') {
        if (strchr("=<>!+-*/%&|", input[i])) {
            temp[0] = input[i];
            temp[1] = input[i+1];
            temp[2] = '\0';

            // Try 2-character operator first
            if (isOperator(temp)) {
                fprintf(outputFile, "Valid operator: %s\n", temp);
                i += 2;
            } else {
                temp[1] = '\0';
                if (isOperator(temp)) {
                    fprintf(outputFile, "Valid operator: %s\n", temp);
                    i++;
                } else {
                    fprintf(outputFile, "Invalid operator: %c\n", input[i]);
                    i++;
                }
            }
        } else {
            i++;
        }
    }

    fclose(outputFile);
    return 0;
}

