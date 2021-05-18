#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100005
#define MAX_N 100005
#define MAX_O 200005

typedef struct __node__ {
    int key;
    struct __node__* nxt;
    struct __node__* prv;
} node;

typedef struct __llist__ {
    node* head;
    node* tail;
} llist;

typedef struct __line__ {
    int size;
    int cap;
    int* heap;
    llist deque;
} line;

void addLList(llist* list, int key) {
    node* new_node = malloc(sizeof(node));
    new_node->key = key;
    new_node->nxt = NULL;
    if (list->tail) {
        list->tail->nxt = new_node;
    } else {
        list->head = new_node;
    }
    new_node->prv = list->tail;
    list->tail = new_node;
}

void insertHeap(int* heap, int size, int key) {
    heap[size] = key;
    int child = size;
    int parent = child/2;
    while (parent) {
        if (heap[child] > heap[parent]) {
            heap[child] = heap[parent];
            heap[parent] = key;
            child = parent;
            parent = child/2;
        } else {
            break;
        }
    }
}

void pushLine(line* l, int key) {
    l->size++;
    while (l->size >= l->cap) {
        l->cap *= 10;
        l->heap = realloc(l->heap, l->cap*sizeof(int));
    }
    addLList(&(l->deque), key);
    insertHeap(l->heap, l->size, key);
}

int popHead(llist* deque) {
    node* tmp = deque->head;
    int popped = tmp->key;
    deque->head = deque->head->nxt;
    if (deque->head) {
        deque->head->prv = NULL;
    } else {
        deque->tail = NULL;
    }
    free(tmp);
    return popped;
}

int popTail(llist* deque) {
    node* tmp = deque->tail;
    int popped = tmp->key;
    deque->tail = deque->tail->prv;
    if (deque->tail) {
        deque->tail->nxt = NULL;
    } else {
        deque->head = NULL;
    }
    free(tmp);
    return popped;
}

int popMax(int* heap, int size) {
    int popped = heap[1];
    heap[1] = heap[size];
    int p=1;
    // printf("size: %d\n", size);
    while (2*p < size) {
        int max_c;
        if (2*p+1 < size) {
            max_c = (heap[2*p] > heap[2*p+1]) ?  2*p: 2*p+1;
        } else {
            max_c = 2*p;
        }
        // printf("heap: %d %d\n", heap[p], heap[max_c]);
        if (heap[p] < heap[max_c]) {
            int tmp = heap[p];
            heap[p] = heap[max_c];
            heap[max_c] = tmp;
            p = max_c;
        } else {
            break;
        }
    }
    return popped;
}

void cleanLine(line* l, int* p_loc) {
    while (p_loc[l->deque.head->key] < 0) {
        popHead(&(l->deque));
    }
    while (p_loc[l->deque.tail->key] < 0) {
        popTail(&(l->deque));
    }
    while (p_loc[l->heap[1]] < 0) {
        popMax(l->heap, l->size);
        l->size--;
    }
}

int isPopable(line* l, int key, int* p_loc) {
    cleanLine(l, p_loc);
    if (key == l->deque.head->key) {
        popHead(&(l->deque));
        p_loc[key] = -1;
        return 1;
    } else if (key == l->deque.tail->key) {
        popTail(&(l->deque));
        p_loc[key] = -1;
        return 1;
    } else if (key == l->heap[1]) {
        popMax(l->heap, l->size);
        l->size--;
        p_loc[key] = -1;
        return 1;
    } else {
        return 0;
    }
}

void merge(line* main_l, line* sub_l, int* p_loc) {
    // cleanLine(sub_l, p_loc);
    // cleanLine(main_l, p_loc);
    int rev = 0;
    if (main_l->size < sub_l->size) {
        rev = 1;
    }
    if (rev) {
        line* tmp = main_l;
        main_l = sub_l;
        sub_l = tmp;
    }
    if (!rev) {
        if (main_l->deque.head) {
            main_l->deque.tail->nxt = sub_l->deque.head;
        } else {
            main_l->deque.head = sub_l->deque.head;
        }
        if (sub_l->deque.head) {
            sub_l->deque.head->prv = main_l->deque.tail;
            main_l->deque.tail = sub_l->deque.tail;
        }
    } else {
        if (main_l->deque.head) {
            main_l->deque.head->prv = sub_l->deque.tail;
        } else {
            main_l->deque.tail = sub_l->deque.tail;
        }

        if (sub_l->deque.head) {
            sub_l->deque.tail->nxt = main_l->deque.head;
            main_l->deque.head = sub_l->deque.head;
        }
    }
    
    if (!rev) {
        node* np = sub_l->deque.head;
        while (np) {
            main_l->size++;
            while (main_l->size >= main_l->cap) {
                main_l->cap *= 10;
                main_l->heap = realloc(main_l->heap, main_l->cap*sizeof(int));
            }
            int popped = np->key;
            if (p_loc[popped] >= 0)
                insertHeap(main_l->heap, main_l->size, popped);
            else
                main_l->size--;
            np = np->nxt;
        }
    } else {
        node* np = sub_l->deque.tail;
        while (np) {
            main_l->size++;
            while (main_l->size >= main_l->cap) {
                main_l->cap *= 10;
                main_l->heap = realloc(main_l->heap, main_l->cap*sizeof(int));
            }
            int popped = np->key;
            if (p_loc[popped] >= 0)
                insertHeap(main_l->heap, main_l->size, popped);
            else
                main_l->size--;
            np = np->prv;
        }
    }

    if (rev) {
        line* tmp = main_l;
        main_l = sub_l;
        sub_l = tmp;
        line tmp_l = *main_l;
        *main_l = *sub_l;
        *sub_l = tmp_l;
    }

    sub_l->deque.head = NULL;
    sub_l->deque.tail = NULL;
    sub_l->size = 0;
    free(sub_l->heap);
}

int findSet(int* line_trans, int id) {
    if (id == line_trans[id]) {
        return id;
    } else {
        line_trans[id] = findSet(line_trans, line_trans[id]);
        return line_trans[id];
    }
}


int main(){
    int T;
    scanf("%d", &T);
    // printf("Hey\n");
    for (int i=0; i<T; i++) {
        int N, O, L;
        scanf("%d%d%d", &N, &O, &L);
        // Some variables
        line lines[MAX_L];
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
            lines[j].deque.head = NULL;
            lines[j].deque.tail = NULL;
            lines[j].heap = malloc(2*sizeof(int));
        }
        // Initialize package location
        for (int j=1; j<=N; j++) {
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
                pushLine(&(lines[line_num]), height);
            } else {
                int m_idx = ops[j][2];
                int s_idx = ops[j][1];
                line_trans[s_idx] = m_idx;
                merge(&(lines[m_idx]), &(lines[s_idx]), package_loc);
            }

            // Try to pop for final
            while (final_stage < N) {
                if (final_stage > j) {
                    break;
                }
                int target_package = final[final_stage];
                int target_id = package_loc[target_package];
                if (target_id < 0) {
                    break;
                }
                target_id = findSet(line_trans, target_id);
                // while (target_id != line_trans[target_id]) {
                //     target_id = line_trans[target_id];
                // }
                
                line* target_line = &(lines[target_id]);
                int popable = isPopable(target_line, target_package, package_loc);
                
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
            if (lines[j].size) {
                free(lines[j].heap);
            }
        }
    }
    return 0;
}