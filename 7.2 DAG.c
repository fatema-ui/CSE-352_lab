#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DAG Node
typedef struct Node {
    char value[10];
    struct Node *left, *right;
} Node;

// Helper to check if two subtrees are same (for detecting common subexpressions)
int isSame(Node* a, Node* b) {
    if (!a || !b) return 0;
    if (strcmp(a->value, b->value) != 0) return 0;
    if ((a->left && b->left && isSame(a->left, b->left)) || (!a->left && !b->left)) {
        if ((a->right && b->right && isSame(a->right, b->right)) || (!a->right && !b->right)) {
            return 1;
        }
    }
    return 0;
}

// Create node
Node* createNode(char* value, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->value, value);
    node->left = left;
    node->right = right;
    return node;
}

// Construct DAG with subexpression reuse
Node* constructDAG() {
    // Common subexpression
    Node* sub_bc = createNode("-", createNode("b", NULL, NULL), createNode("c", NULL, NULL));

    Node* mul1 = createNode("*", createNode("a", NULL, NULL), sub_bc);
    Node* mul2 = createNode("*", sub_bc, createNode("d", NULL, NULL));
    Node* add1 = createNode("+", createNode("a", NULL, NULL), mul1);
    Node* root = createNode("+", add1, mul2);

    return root;
}

// Print DAG in preorder
void printDAG(Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("%s\n", root->value);

    printDAG(root->left, level + 1);
    printDAG(root->right, level + 1);
}

int main() {
    Node* dag = constructDAG();
    printf("Directed Acyclic Graph (DAG):\n");
    printDAG(dag, 0);
    return 0;
}
