#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a tree node
typedef struct Node {
    char value[10];
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* createNode(char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->value, value);
    node->left = node->right = NULL;
    return node;
}

// Manually constructing AST for: a + a * (b - c) + (b - c) * d
Node* constructAST() {
    Node* root = createNode("+");

    Node* left = createNode("+");
    Node* right = createNode("*");

    Node* mul1 = createNode("*");
    Node* sub1 = createNode("-");
    Node* sub2 = createNode("-");

    // Left side of the tree
    root->left = left;
    left->left = createNode("a");
    left->right = mul1;
    mul1->left = createNode("a");
    mul1->right = sub1;
    sub1->left = createNode("b");
    sub1->right = createNode("c");

    // Right side of the tree
    root->right = right;
    right->left = sub2;
    sub2->left = createNode("b");
    sub2->right = createNode("c");
    right->right = createNode("d");

    return root;
}

// Print AST in preorder
void printAST(Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("%s\n", root->value);

    printAST(root->left, level + 1);
    printAST(root->right, level + 1);
}

int main() {
    Node* ast = constructAST();
    printf("Abstract Syntax Tree (Preorder View):\n");
    printAST(ast, 0);
    return 0;
}

