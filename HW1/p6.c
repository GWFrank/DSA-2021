#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_N 100005

typedef struct node {
    int* unsorted;
    int* sorted;
    int size;
    uintptr_t adj;
} node;

typedef struct llist {
    node* head;
    node* tail;
} llist;

llist* newLList() {
    llist* new = malloc(sizeof(llist));
    new->head = NULL;
    new->tail = NULL;
    return new;
}

void add_tail(llist* LList, int size) {
    node* new_tail = malloc(sizeof(node));
    new_tail->unsorted = malloc(2*size*sizeof(int));
    new_tail->sorted = malloc(2*size*sizeof(int));
    new_tail->size = size;
    new_tail->adj = (uintptr_t) LList->tail;
    if (LList->tail) {
        LList->tail->adj = LList->tail->adj ^ (uintptr_t) new_tail;
        LList->tail = new_tail;
    } else {
        LList->head = new_tail;
        LList->tail = new_tail;
    }
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    int seg_len = (int) sqrt(n);

    for (int i=0; i<n; i++) {

    }


    return 0;
}