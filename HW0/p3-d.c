#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset

// Use typedef to substitute "struct node" with "node".
typedef struct node {
    int data;
    struct node *left, *right;
} node;

// creates a node filled with predefined values
node *alloc(int data, node *left, node *right) {
    node *tmp = (node *) malloc(sizeof(node));
    tmp->data = data;
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

// traverses the nodes recursively
void traverse(node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        traverse(root->left);
        traverse(root->right);
    }
}

// frees the nodes recursively
void destroy(node *root) {
    if (root != NULL) {
        // recursively destroy nodes
        destroy(root->left);
        destroy(root->right);
        // clean sensitive data
        memset(root, 0, sizeof(root));
        free(root);
    }
}


int main() {
    // creates a hierarchical data structure
    node *root = \
        alloc(0,
            alloc(3,
                alloc(7, NULL, NULL),
                alloc(4, NULL, NULL)
            ),
            alloc(2,
                alloc(1, NULL, NULL),
                alloc(9, NULL, NULL)
            )
        );
    
    // traverses the nodes one by one
    traverse(root);

    // frees the nodes to avoid memory leak
    destroy(root);

    return 0;
}