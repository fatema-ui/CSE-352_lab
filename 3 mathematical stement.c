#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Check if parentheses are balanced
int areParenthesesBalanced(const char* expr) {
    int count = 0;
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(') count++;
        else if (expr[i] == ')') count--;
        if (count < 0) return 0;
    }
    return count == 0;
}

// Check if characters are valid
int isValidCharacter(char ch) {
    return isdigit(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || isspace(ch);
}

// VERY basic evaluator: only supports expressions like "2 + 3"
int simpleEvaluate(const char* expr) {
    int a, b;
    char op;
    if (sscanf(expr, "%d %c %d", &a, &op, &b) == 3) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b != 0 ? a / b : 999999; // prevent divide-by-zero
        }
    }
    return 999999;
}

int main() {
    char expr[100];
    FILE *inputFile, *outputFile;

    // Step 1: Get input from user and write to input.txt
    printf("Enter a mathematical expression:\n");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0';

    inputFile = fopen("input.txt", "w");
    fputs(expr, inputFile);
    fclose(inputFile);

    // Step 2: Read from input.txt and write result to output.txt
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    fgets(expr, sizeof(expr), inputFile);
    fclose(inputFile);

    int valid = 1;
    for (int i = 0; expr[i]; i++) {
        if (!isValidCharacter(expr[i])) {
            valid = 0;
            break;
        }
    }

    if (!areParenthesesBalanced(expr)) {
        valid = 0;
    }

    if (valid) {
        int result = simpleEvaluate(expr);
        if (result != 999999)
            fprintf(outputFile, "Expression is solvable. Result: %d\n", result);
        else
            fprintf(outputFile, "Expression is valid but cannot be evaluated with this basic logic.\n");
    } else {
        fprintf(outputFile, "Invalid mathematical expression.\n");
    }

    fclose(outputFile);
    return 0;
}

