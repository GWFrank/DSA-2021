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
    node** heap;
    int size;
    int cap;
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
    if (lines[main_l].size >= lines[sub_l].size) {
        if (lines[sub_l].size > 0) {
            // Merge deque
            lines[main_l].deque.tail->nxt = lines[sub_l].deque.head;
            lines[sub_l].deque.head->prv = lines[main_l].deque.tail;
            lines[main_l].deque.tail = lines[sub_l].deque.tail;
            // Merge heap
            for (int i=1; i<=lines[sub_l].size; i++) {
                lines[main_l].heap[lines[main_l].size+i] = lines[sub_l].heap[i];
                lines[main_l].heap[lines[main_l].size+i]->heap_idx = lines[main_l].size+i;
                int child = lines[main_l].size+i;
                int parent = child/2;
                while (parent) {
                    if (lines[main_l].heap[child]->key > lines[main_l].heap[parent]->key) {
                        swapNode(&(lines[main_l]), parent, child);
                        child = parent;
                        parent = child/2;
                    } else {
                        break;
                    }
                }
            }
        }
        // Change prodLine size
        lines[main_l].size += lines[sub_l].size;
        lines[sub_l].size = 0;
    } else {
        if (lines[main_l].size > 0) {
            // Merge deque
            lines[main_l].deque.tail->nxt = lines[sub_l].deque.head;
            lines[sub_l].deque.head->prv = lines[main_l].deque.tail;
            lines[sub_l].deque.head = lines[main_l].deque.tail;
            // Merge heap
            for (int i=1; i<=lines[main_l].size; i++) {
                lines[sub_l].heap[lines[sub_l].size+i] = lines[main_l].heap[i];
                lines[sub_l].heap[lines[sub_l].size+i]->heap_idx = lines[sub_l].size+i;
                int child = lines[sub_l].size+i;
                int parent = child/2;
                while (parent) {
                    if (lines[sub_l].heap[child]->key > lines[sub_l].heap[parent]->key) {
                        swapNode(&(lines[sub_l]), parent, child);
                        child = parent;
                        parent = child/2;
                    } else {
                        break;
                    }
                }
            }
        }
        // Change prodLine size
        lines[sub_l].size += lines[main_l].size;
        lines[main_l].size = 0;
        /* debug
        printf("+++++++++++\n");
        printf("merging %d to %d\n", sub_l, main_l);
        printf("main\n");
        printf("deque:\n");
        node* tmp_p = lines[sub_l].deque.head;
        while (tmp_p) {
            if (tmp_p == tmp_p->nxt) {
                printf("Error\n");
                break;
            }
            printf("%d -> ", tmp_p->key);
            tmp_p = tmp_p->nxt;
        }
        printf("\nheap:\n");
        for (int tmp_i=1; tmp_i<=lines[sub_l].size; tmp_i++) {
            printf("%d -> ", lines[sub_l].heap[tmp_i]->key);
        }
        printf("\n");
        printf("+++++++++++\n");
        // */
        // printf("%d %d\n", lines[main_l].size, lines[sub_l].size);
        prodLine tmp = lines[main_l];
        lines[main_l] = lines[sub_l];
        lines[sub_l] = tmp;
        // printf("%d %d\n", lines[main_l].size, lines[sub_l].size);
    }
}

prodLine lines[MAX_L];

int main(){
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, O, L;
        scanf("%d%d%d", &N, &O, &L);
        // Some variables
        // prodLine* lines = malloc(L*sizeof(prodLine));
        // prodLine lines[MAX_L];
        int line_trans[MAX_L];
        int ops[MAX_O][3];
        int final[MAX_N];
        int package_loc[MAX_N];
        int final_stage = 0;
        // Initialize production lines
        for (int j=0; j<L; j++) {
            line_trans[j] = j;
            lines[j].size = 0;
            lines[j].cap = 1;
            lines[j].heap = malloc((N+5)*sizeof(node*));
            lines[j].deque.head = NULL;
            lines[j].deque.tail = NULL;
        }
        // Initialize package location
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
                int main_line = ops[j][2];
                int sub_line = ops[j][1];
                line_trans[sub_line] = main_line;
                mergeLines(lines, main_line, sub_line);
            }
            /* debug
            printf("===========\n");
            printf("before\n");
            for (int k=0; k<L; k++) {
                if (lines[k].size == 0) {
                    continue;
                }
                printf("number %d\n", k);
                printf("deque:\n");
                node* tmp_p = lines[k].deque.head;
                while (tmp_p) {
                    printf("%d -> ", tmp_p->key);
                    if (tmp_p == tmp_p->nxt) {
                        printf("Error\n");
                        break;
                    }
                    tmp_p = tmp_p->nxt;
                }
                printf("\nheap:\n");
                for (int tmp_i=1; tmp_i<=lines[k].size; tmp_i++) {
                    printf("%d -> ", lines[k].heap[tmp_i]->key);
                }
                printf("\n");
            }
            printf("===========\n");
            // */
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
            free(lines[j].heap);
        }
    }
    return 0;
}