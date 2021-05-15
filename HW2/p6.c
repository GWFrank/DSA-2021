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
    node* heap[MAX_N+1];
    int size;
} prodLine;

void swapNode(prodLine* prod_line, int idx_a, int idx_b) {
    node** heap = prod_line->heap;
    int tmp_idx = heap[idx_a]->heap_idx;
    heap[idx_a]->heap_idx = heap[idx_b]->heap_idx;
    heap[idx_b]->heap_idx = tmp_idx;
    node* tmp = heap[idx_a];
    heap[idx_a] = heap[idx_b];
    heap[idx_b] = tmp;
}

void pushProdLine(prodLine* prod_line, int height) {
    node** heap = prod_line->heap;
    prod_line->size++;
    int idx = prod_line->size;
    heap[idx] = malloc(sizeof(node));
    heap[idx]->heap_idx = idx;
    heap[idx]->key = height;
    heap[idx]->prv = prod_line->deque.tail;
    heap[idx]->nxt = NULL;
    if (prod_line->deque.tail) {
        prod_line->deque.tail->nxt = heap[idx];
    } else {
        prod_line->deque.head = heap[idx];
    }
    prod_line->deque.tail = heap[idx];

    int child = idx;
    int parent = child/2;
    while (parent) {
        if (heap[child]->key > heap[parent]->key) {
            swapNode(prod_line, parent, child);
            child = parent;
            parent = child/2;
        } else {
            break;
        }
    }
}

void popInHeap(prodLine* prod_line, int og_size, int pop_idx) {
    node** heap = prod_line->heap;
    swapNode(prod_line, og_size, pop_idx);
    int p = pop_idx;
    while (p < og_size/2) {
        int c;
        if (2*p+1 < og_size) {
            c = (heap[2*p]->key > heap[2*p+1]->key) ?  2*p: 2*p+1;
        } else {
            c = 2*p;
        }
        if (heap[p]->key < heap[c]->key) {
            swapNode(prod_line, p, c);
            p = c;
        } else {
            break;
        }
    }
}

int popHead(prodLine* prod_line) {
    if (prod_line->size > 0) {
        int pop_idx = prod_line->deque.head->heap_idx;
        int popped_key = prod_line->deque.head->key;
        popInHeap(prod_line, prod_line->size, pop_idx);
        prod_line->size--;
        prod_line->deque.head = prod_line->deque.head->nxt;
        if (prod_line->deque.head) {
            prod_line->deque.head->prv = NULL;
        } else {
            prod_line->deque.tail = NULL;
        }
        free(prod_line->heap[prod_line->size+1]);
        return popped_key;
    } else {
        return -1;
    }
}

int popTail(prodLine* prod_line) {
    if (prod_line->size > 0) {
        int pop_idx = prod_line->deque.tail->heap_idx;
        int popped_key = prod_line->deque.tail->key;
        popInHeap(prod_line, prod_line->size, pop_idx);
        prod_line->size--;
        prod_line->deque.tail = prod_line->deque.tail->prv;
        if (prod_line->deque.tail) {
            prod_line->deque.tail->nxt = NULL;
        } else {
            prod_line->deque.head = NULL;
        }
        return popped_key;
    } else {
        return -1;
    }
}

int popMax(prodLine* prod_line) {
    if (prod_line->size > 0) {
        int pop_idx = 1;
        int popped_key = prod_line->heap[1]->key;
        node* node_ptr = prod_line->heap[1];
        popInHeap(prod_line, prod_line->size, pop_idx);
        prod_line->size--;
        if (node_ptr->prv) {
            node_ptr->prv->nxt = node_ptr->nxt;
        }
        if (node_ptr->nxt) {
            node_ptr->nxt->prv = node_ptr->prv;
        }
        return popped_key;
    } else {
        return -1;
    }
}

int isPopable(prodLine* prod_line, int key) {
    // 1 => head, 2 => tail, 3 => max, 0 => none
    if (prod_line->deque.head->key == key) {
        return 1;
    } else if (prod_line->deque.tail->key == key) {
        return 2;
    } else if (prod_line->heap[1]->key == key) {
        return 3;
    } else {
        return 0;
    }
}

void mergeLines(prodLine* lines, int main_l, int sub_l) {

}


int main(){
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, O, L;
        scanf("%d%d%d", &N, &O, &L);
        // Some variables
        prodLine* lines = malloc(L*sizeof(prodLine));
        // prodLine lines[MAX_L];
        int line_trans[MAX_L];
        int ops[MAX_O][3];
        int final[MAX_N];
        int package_loc[MAX_N];
        int final_stage = 0;
        // Initiate production lines
        for (int j=0; j<L; j++) {
            line_trans[j] = j;
            lines[j].size = 0;
        }
        // Initiate package location
        for (int j=0; j<MAX_N; j++) {
            package_loc[j] = -1;
        }
        // Read all operations and store
        for (int j=0; j<O; j++) {
            char s[10];
            scanf("%s%d%d", s, &(ops[j][1]), &(ops[j][2]));
            if (s[0] == 'p') ops[j][0] = 0;
            else ops[j][0] = 1;
        }
        // Read final state
        for (int j=0; j<N; j++) {
            scanf("%d", &(final[j]));
        }
        // Execute operations
        for (int j=0; j<O; j++) {
            // 0 is push, 1 is merge
            if (ops[j][0] == 0) {
                int height = ops[j][1];
                int line_num = ops[j][2];
                package_loc[height] = line_num;
                pushProdLine(&(lines[line_num]), height);
            } else {
                int main_line = ops[j][1];
                int sub_line = ops[j][2];
                line_trans[sub_line] = main_line;
                mergeLines(lines, main_line, sub_line);
            }
            // debug
            // printf("===========\n");
            // printf("before\n");
            // printf("deque:\n");
            // node* tmp_p = lines[0].deque.head;
            // while (tmp_p) {
            //     printf("%d -> ", tmp_p->key);
            //     if (tmp_p == tmp_p->nxt) {
            //         printf("Error\n");
            //         break;
            //     }
            //     tmp_p = tmp_p->nxt;
            // }
            // printf("\nheap:\n");
            // for (int tmp_i=1; tmp_i<=lines[0].size; tmp_i++) {
            //     printf("%d -> ", lines[0].heap[tmp_i]->key);
            // }
            // printf("\n===========\n");
            // Try to pop for final
            while (final_stage < N) {
                if (final_stage > j) {
                    break;
                }
                int target_package = final[final_stage];
                int target_id = package_loc[target_package];
                if (target_id < 0) {
                    break;
                } else {
                    while (target_id != line_trans[target_id]) {
                        target_id = line_trans[target_id];
                    }
                }
                prodLine* target_line = &(lines[target_id]);
                int popable = isPopable(target_line, target_package);
                switch (popable) {
                    case 1:
                        popHead(target_line);
                        break;
                    case 2:
                        popTail(target_line);
                        break;
                    case 3:
                        popMax(target_line);
                        break;
                }
                // printf("%d\n", popable);
                if (popable > 0) {
                    final_stage++;
                    // debug
                    // printf("===========\n");
                    // printf("after\n");
                    // printf("deque:\n");
                    // node* tmp_p = lines[0].deque.head;
                    // while (tmp_p) {
                    //     if (tmp_p == tmp_p->nxt) {
                    //         printf("Error\n");
                    //         break;
                    //     }
                    //     printf("%d -> ", tmp_p->key);
                    //     tmp_p = tmp_p->nxt;
                    // }
                    // printf("\nheap:\n");
                    // for (int tmp_i=1; tmp_i<=lines[0].size; tmp_i++) {
                    //     printf("%d -> ", lines[0].heap[tmp_i]->key);
                    // }
                    // printf("\n===========\n");
                } else {
                    break;
                }
            }
            if (final_stage == N)
                break;
            
        }

        if (final_stage == N) {
            printf("possible\n");
        } else {
            printf("impossible\n");
        }

        for (int j=0; j<L; j++) {
            for (int k=1; k<=lines[j].size; k++) {
                free(lines[j].heap[k]);
            }
        }
        free(lines);
    }
    return 0;
}