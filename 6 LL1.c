#include <stdio.h>
#include <string.h>

char *nt[] = {"E", "E'", "T", "T'", "F"};
char *t[]  = {"id", "+", "*", "(", ")", "$"};

char* get_rule(char* n, char* x) {
    if (strcmp(n, "E") == 0 && (strcmp(x, "id") == 0 || strcmp(x, "(") == 0))
        return "E -> T E'";
    if (strcmp(n, "E'") == 0 && strcmp(x, "+") == 0)
        return "E' -> + T E'";
    if (strcmp(n, "E'") == 0 && (strcmp(x, ")") == 0 || strcmp(x, "$") == 0))
        return "E' -> @";
    if (strcmp(n, "T") == 0 && (strcmp(x, "id") == 0 || strcmp(x, "(") == 0))
        return "T -> F T'";
    if (strcmp(n, "T'") == 0 && strcmp(x, "*") == 0)
        return "T' -> * F T'";
    if (strcmp(n, "T'") == 0 && (strcmp(x, "+") == 0 || strcmp(x, ")") == 0 || strcmp(x, "$") == 0))
        return "T' -> @";
    if (strcmp(n, "F") == 0 && strcmp(x, "id") == 0)
        return "F -> id";
    if (strcmp(n, "F") == 0 && strcmp(x, "(") == 0)
        return "F -> ( E )";
    return "";
}

int main() {
    int i, j;

    printf("\n%-6s", "");
    for (j = 0; j < 6; j++)
        printf("%-20s", t[j]);
    printf("\n");

    for (i = 0; i < 5; i++) {
        printf("%-6s", nt[i]);
        for (j = 0; j < 6; j++) {
            char *rule = get_rule(nt[i], t[j]);
            printf("%-20s", rule);
        }
        printf("\n\n");
    }

    return 0;
}
