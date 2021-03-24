#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int label;
    struct node* nxt;
    struct node* prv;
} node;

typedef struct llist {
    node* head;
    node* tail;
} llist;

llist* newStack() {
    llist* stack = malloc(sizeof(llist));
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

node* nxt(node* cur) {
    return cur->nxt;
}

node* prv(node* cur) {
    return cur->prv;
}

void push(llist* stack, int label) {
    node* new_node = malloc(sizeof(node));
    new_node->label = label;    
    new_node->nxt = stack->head;
    new_node->prv = NULL;
    if (stack->head) {
        stack->head->prv = new_node;
    } else {
        stack->tail = new_node;
    }
    stack->head = new_node;
}

int pop(llist* stack) {
    int popped = -1;
    if (stack->head) {
        node* old_head = stack->head;
        popped = old_head->label;
        stack->head = stack->head->nxt;
        free(old_head);
        if (stack->head) { 
            stack->head->prv = NULL;
        } else { // handle stack with only one element
            stack->tail = NULL;
        }
    }
    return popped;
}

void migrate(llist* sa, llist* sb) {
    while (sa->head) {
        // int l = pop(sa);
        // push(sb, l);
        push(sb, pop(sa));
    }
}

void printRails(llist** rails, int rail_num) {
    for (int i=0; i<rail_num; i++) {
        node* cur = rails[i]->tail;
        if (cur == 0) {
            printf("\n");
        } else {
            while (cur) {
                printf("%d", cur->label);
                if (cur->prv) {
                    printf(" ");
                } else {
                    printf("\n");
                }
                cur = cur->prv;
            }
        }
    }
}

int main(){
    int rail_num, record_num;
    scanf("%d%d", &rail_num, &record_num);
    
    llist** rails = malloc(sizeof(llist*)*rail_num);
    for (int i=0; i<rail_num; i++) {
        rails[i] = newStack();
    }

    for (int i=0; i<record_num; i++) {
        char cmd[10];
        scanf("%s", cmd);
        if (strcmp(cmd, "enter") == 0) {
            int r, l;
            scanf("%d%d", &r, &l);
            push(rails[r], l);
        } else if (strcmp(cmd, "leave") == 0) {
            int r;
            scanf("%d", &r);
            pop(rails[r]);
        } else if (strcmp(cmd, "migrate") == 0) {
            int ra, rb;
            scanf("%d%d", &ra, &rb);
            migrate(rails[ra], rails[rb]);
        }
    }

    printRails(rails, rail_num);


    return 0;
}