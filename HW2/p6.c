#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100005
#define MAX_N 100005
#define MAX_O 200005


typedef struct __node__ {
    int key;
    struct __node__* nxt;
    struct __node__* prv;
    int heap_idx;
} node;

typedef struct __llist__ {
    node* head;
    node* tail;
} llist;


typedef struct __prodLine__ {
    llist deque;
    node heap[MAX_N+1];
    int size;
} prodLine;

void swapNode(node* heap, int idx_a, int idx_b) {
    int tmp_idx = heap[idx_a].heap_idx;
    heap[idx_a].heap_idx = heap[idx_b].heap_idx;
    heap[idx_b].heap_idx = tmp_idx;
    node tmp = heap[idx_a];
    heap[idx_a] = heap[idx_b];
    heap[idx_b] = tmp;
}

void pushProdLine(prodLine* prod_line, int height) {
    node* heap = prod_line->heap;
    prod_line->size++;
    int idx = prod_line->size;
    heap[idx].heap_idx = idx;
    heap[idx].key = height;
    heap[idx].prv = prod_line->deque.tail;
    heap[idx].nxt = NULL;
    if (prod_line->deque.tail) {
        prod_line->deque.tail->nxt = &(prod_line->heap[idx]);
    } else {
        prod_line->deque.head = &(prod_line->heap[idx]);
        prod_line->deque.tail = &(prod_line->heap[idx]);
    }
    int child = idx;
    int parent = child/2;
    while (parent) {
        if (heap[child].key > heap[parent].key) {
            swapNode(heap, parent, child);
        } else {
            break;
        }
    }
}

int main(){
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, O, L;
        scanf("%d%d%d", &N, &O, &L);
        // initiate production lines
        int line_trans[MAX_L];
        prodLine* lines = malloc(L*sizeof(prodLine));
        for (int j=0; j<L; j++) {
            line_trans[j] = j;
            lines[j].size = 0;
        }
        // read all operations and store
        int ops[MAX_O][3];
        for (int j=0; j<O; j++) {
            char s[10];
            scanf("%s%d%d", s, &(ops[j][1]), &(ops[j][2]));
            if (s[0] == 'p') ops[j][0] = 0;
            else ops[j][0] = 1;
        }
        // read final state
        int final[MAX_N];
        for (int j=0; j<N; j++) {
            scanf("%d", &(final[j]));
        }
        // execute operations
        for (int j=0; j<O; j++) {
            if (ops[j][0] == 1) {
                int height = ops[j][1];
                int line_num = ops[j][2];
                pushProdLine(&(lines[line_num]), height);
            }
        }
        free(lines);
    }
    return 0;
}