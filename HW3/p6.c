/*
Refs:
B09902100
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010

typedef struct __node__ {
    int key1;
    int key2;
    struct __node__* nxt;
} node;

typedef struct __llist__ {
    node* head;
} llist;

llist* newLList() {
    llist* new = malloc(sizeof(llist));
    new->head = NULL;
    return new;
}

void addHead(llist* list, int val1, int val2) {
    node* new_node = malloc(sizeof(node));
    new_node->key1 = val1;
    new_node->key2 = val2;
    new_node->nxt = list->head;
    list->head = new_node;
}

typedef struct __sNode__ {
    int key;
    struct __sNode__* nxt;
} sNode;

typedef struct __stack__ {
    sNode* top;
} stack;

stack* newStack() {
    stack* s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void push(stack* stk, int key) {
    sNode* new_node = malloc(sizeof(sNode));
    new_node->key = key;
    new_node->nxt = stk->top;
    stk->top = new_node;
}

int pop(stack* stk) {
    sNode* top  =stk->top;
    int popped = top->key;
    stk->top = top->nxt;
    free(top);
    return popped;
}

int isEmpty(stack* s) {
    if (s->top) return 0;
    else return 1;
}

void printEdges(llist* edge_list) {
    while (edge_list->head) {
        node* head = edge_list->head;
        printf("%d %d\n", head->key1, head->key2);
        edge_list->head = head->nxt;
        free(head);
    }
}

int complete(int N, int* list_pos) {
    for (int i=1; i<=N; i++) {
        if (list_pos[i] >= 0) return 0;
    }
    return 1;
}

int solve(int N, int* list_pos, int** adj_list, llist* edge_list) {
    stack* stk = newStack();
    int visiting[MAX_N] = {0};
    // int progress = N;
    while (!complete(N, list_pos)) {
        for (int i=1; i<=N; i++) {
            if (list_pos[i] < 0) {
                continue;
            }
            push(stk, i);
            visiting[i] = 1;
            while (!isEmpty(stk)) {
                int u = stk->top->key; int idx1 = list_pos[u];
                int v = adj_list[u][idx1]; int idx2 = list_pos[v];
                if (visiting[v]) {
                    return 0;
                }
                if (u == adj_list[v][idx2]) {
                    list_pos[u]--;
                    list_pos[v]--;
                    pop(stk);
                    visiting[u] = 0;
                    addHead(edge_list, u, v);
                } else {
                    push(stk, v);
                    visiting[v] = 1;
                }
            }
        }
    }
    return 1;
}

int main(){
    int N;
    scanf("%d", &N);
    int* adj_list[MAX_N];
    int list_pos[MAX_N];
    for (int i=1; i<=N; i++) {
        int list_size;
        scanf("%d", &list_size);
        list_pos[i] = list_size-1;
        adj_list[i] = malloc(list_size*sizeof(int));
        for (int j=0; j<list_size; j++) {
            int adj;
            scanf("%d", &adj);
            adj_list[i][j] = adj;
        }
    }
    
    llist* edge_list = newLList();
    int result = solve(N, list_pos, adj_list, edge_list);

    if (result) {
        printf("Yes\n");
        printEdges(edge_list);
    } else {
        printf("No\n");
    }
    free(edge_list);
    return 0;
}