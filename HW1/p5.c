/*
Reference:
https://www.geeksforgeeks.org/can-we-reverse-a-linked-list-in-less-than-on/
https://stackoverflow.com/questions/26569728/using-xor-with-pointers-in-c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct node {
    int label;
    uintptr_t adj;
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

void push(llist* stack, int label) {
    node* new_node = malloc(sizeof(node));
    new_node->label = label;    
    new_node->adj = (uintptr_t) stack->head;
    if (stack->head) {
        stack->head->adj = stack->head->adj ^ (uintptr_t) new_node;
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
        stack->head = (node *) stack->head->adj;
        if (stack->head) {
            stack->head->adj = stack->head->adj ^ (uintptr_t) old_head;
        } else {
            stack->tail = NULL;
        }
        free(old_head);
    }
    return popped;
}

void migrate(llist* sa, llist* sb) {
    // migrates sa to sb
    // while (sa->head) {
    //     // int l = pop(sa);
    //     // push(sb, l);
    //     push(sb, pop(sa));
    // }
    if (sa->head) {
        if (sb->head) {
            // connect sa's head to sb's head
            sb->head->adj = sb->head->adj ^ (uintptr_t) sa->head;
            sa->head->adj = sa->head->adj ^ (uintptr_t) sb->head;
            // relocate sb's head at sa's tail
            sb->head = sa->tail;
        } else {
            sb->tail = sa->head;
            sb->head = sa->tail;
        }
        // empty sa
        sa->head = NULL;
        sa->tail = NULL;
    }
}

void printRails(llist** rails, int rail_num) {
    for (int i=0; i<rail_num; i++) {
        node* cur = rails[i]->tail;
        if (cur == 0) {
            printf("\n");
        } else {
            node* prv = NULL;
            uintptr_t nxt = 0;
            while (cur) {
                printf("%d", cur->label);
                nxt = (uintptr_t) prv ^ cur->adj;
                if (nxt) {
                    printf(" ");
                } else {
                    printf("\n");
                }
                prv = cur;
                cur = (node *) nxt;
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