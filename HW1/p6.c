#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_N 100005

int compare(const void *a, const void *b) {
    int c = *(int *)a;
    int d = *(int *)b;
    if(c < d) {return -1;}
    else if (c == d) {return 0;}
    else return 1;
}

typedef struct node {
    int* unsorted;
    int* sorted;
    int size;
    int capacity;
    uintptr_t adj;
} node;

typedef struct llist {
    node* head;
    node* tail;
    int node_cnt;
    int size;
} llist;

llist* newLList() {
    llist* new = malloc(sizeof(llist));
    new->head = NULL;
    new->tail = NULL;
    new->node_cnt = 0;
    new->size = 0;
    return new;
}

void addTail(llist* LList, int size) {
    node* new_tail = malloc(sizeof(node));
    new_tail->capacity = 2*size;
    new_tail->unsorted = malloc(2*size*sizeof(int));
    new_tail->sorted = malloc(2*size*sizeof(int));
    new_tail->size = 0;
    new_tail->adj = (uintptr_t) LList->tail;
    if (LList->tail) {
        LList->tail->adj = LList->tail->adj ^ (uintptr_t) new_tail;
        LList->tail = new_tail;
    } else {
        LList->head = new_tail;
        LList->tail = new_tail;
    }
}

llist* buildFromArr(int* arr, int len, int seg_len) {
    llist* new_llist = newLList();
    int seg_cnt = len/seg_len;
    int last_seg_len = len%seg_len;
    for (int i=0; i<seg_cnt; i++) {
        addTail(new_llist, seg_len);
        node* cur_seg = new_llist->tail;
        for (int j=0; j<seg_len; j++) {
            cur_seg->unsorted[j] = arr[i*seg_len + j];
            cur_seg->size++;
        }
        qsort((void*) &(arr[i*seg_len]), seg_len, sizeof(int), compare);
        for (int j=0; j<seg_len; j++) {
            cur_seg->sorted[j] = arr[i*seg_len + j];
        }
    }
    if (last_seg_len) {
        addTail(new_llist, seg_len);
        node* cur_seg = new_llist->tail;
        for (int j=0; j<last_seg_len; j++) {
            cur_seg->unsorted[j] = arr[seg_cnt*seg_len + j];
            cur_seg->size++;
        }
        qsort((void*) &(arr[seg_cnt*seg_len]), last_seg_len, sizeof(int), compare);
        for (int j=0; j<last_seg_len; j++) {
            cur_seg->sorted[j] = arr[seg_cnt*seg_len + j];
        }
    }
    return new_llist;
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    int seg_len = (int) sqrt(n);

    for (int i=0; i<n; i++) {

    }


    return 0;
}