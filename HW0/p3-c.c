#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// Use typedef to define "struct node" as "node".
typedef struct node{
    int data;
    struct node *nxt;
} node;

node *alloc(int data, node *nxt) {
    node *tmp = (node *) malloc(sizeof(node));
    tmp->data = data;
    tmp->nxt = nxt;
    return tmp;
}

void destroy(node *head) {
    if (head != NULL) { // if ( (1) )
        destroy(head->nxt);
        // clean sensitive data.
        memset(head, 0, sizeof(head));
        free(head);
    }
}

int main() {
    // create nodes [0, 1, 2, 4]
    node *head = alloc(0, alloc(1, alloc(2, alloc(4, NULL))));
    node *tmp = head;

    // print the nodes subsequently
    while (tmp != NULL) {
        printf("%d -> ", tmp->data); // print the data in the node
        tmp = tmp->nxt;
    }
    printf("NULL");

    // free the nodes subsequently to avoid memory leak
    destroy(head);
    return 0;
}