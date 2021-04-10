#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#define MAX_N 50005
#define MAX_X 100000
#define MIN_X -100000
#define MAX_NODES 300

int compare(const void *a, const void *b) {
    // compare function for qsort
    int c = *(int *)a;
    int d = *(int *)b;
    if(c < d) {
        return -1;
    } else if (c == d) {
        return 0;
    } else {
        return 1;
    }
}

typedef struct node {
    int* unsorted;
    int* sorted;
    int size;
    int capacity;
    struct node* nxt;
    struct node* prv;
    // uintptr_t adj;
} node;

typedef struct llist {
    node* head;
    node* tail;
    int node_cnt;
    int size;
} llist;

llist* newLList() {
    // initialize a LList and return a pointer to it
    llist* new = malloc(sizeof(llist));
    new->head = NULL;
    new->tail = NULL;
    new->node_cnt = 0;
    new->size = 0;
    return new;
}

void addNodeToTail(llist* LList, int size) {
    // add a new node to the tail of LList
    node* new_tail = malloc(sizeof(node));
    LList->node_cnt++;
    new_tail->capacity = 2*size;
    new_tail->unsorted = malloc(2*size*sizeof(int));
    new_tail->sorted = malloc(2*size*sizeof(int));
    new_tail->size = 0;
    new_tail->prv = LList->tail;
    new_tail->nxt = NULL;
    // new_tail->adj = (uintptr_t) LList->tail;
    if (LList->tail) {
        LList->tail->nxt = new_tail;
        // LList->tail->adj = LList->tail->adj ^ (uintptr_t) new_tail;
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
    new_llist->size += len;
    for (int i=0; i<seg_cnt; i++) {
        addNodeToTail(new_llist, seg_len);
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
        addNodeToTail(new_llist, seg_len);
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

int locateNode(llist* LList, int n) {
    // find out which node does n-th element locate
    // n range: 1 ~ LList->size
    // return value starts at 0
    node* cur_node = LList->head;
    int ele_cnt=1;
    int node_cnt=0;
    while (cur_node) {
        if (n < ele_cnt+cur_node->size) {
            return node_cnt;
        } else {
            ele_cnt += cur_node->size;
            node_cnt++;
            cur_node = cur_node->nxt;
        }
    }
    return -1;
}

node* locateNodePtr(llist* LList, int n) {
    // find out which node does n-th element locate
    // n range: 1 ~ LList->size
    // return pointer to the node
    node* cur_node = LList->head;
    int ele_cnt=1;
    while (cur_node) {
        if (n < ele_cnt+cur_node->size) {
            return cur_node;
        } else {
            ele_cnt += cur_node->size;
            cur_node = cur_node->nxt;
        }
    }
    return NULL;
}

int binSearchLs(int* sorted, int len, int val) {
    int left = 0; int right = len;
    int mid = (left+right)/2;
    while (1) {
        if ((sorted[mid] >= val && mid == 0) || (mid == len)) {
            break;
        } else if (sorted[mid-1] < val && sorted[mid] >= val) {
            break;
        }
        if (sorted[mid] < val) {
            left = mid+1;
        } else {
            right = mid-1;
        }
        mid = (left+right)/2;
    }
    return mid;
}

int query(llist* LList, int l, int r, int k) {
    // /*
    int l_node_num = locateNode(LList, l);
    int r_node_num = locateNode(LList, r);
    // printf("%d %d\n", l_node_num, r_node_num);
    node* cur_node = LList->head;
    node* l_node; node* r_node;
    node* comp_nodes[MAX_NODES];
    int comp_cnt=-1;
    for (int i=0; i<l_node_num; i++) {
        l -= cur_node->size;
        r -= cur_node->size;
        cur_node = cur_node->nxt;
    }
    l_node = cur_node;
    for (int i=l_node_num; i<r_node_num; i++) {
        r -= cur_node->size;
        comp_nodes[comp_cnt] = cur_node; comp_cnt++;
        cur_node = cur_node->nxt;
    }
    r_node = cur_node;
    // */

    int low = MIN_X; int high = MAX_X; int mid = (high+low)/2;

    if (r_node == l_node) {
        while (1) {
            int ls=0; int le=0;
                for (int idx=l-1; idx<r; idx++) {
                    if (l_node->unsorted[idx] < mid) {
                        ls++; le++;
                    } else if (l_node->unsorted[idx] == mid) {
                        le++;
                    }
                }
            if (ls < k && le >= k) {
                break;
            } else {
                if (ls >= k) {
                    high = mid-1;
                } else if (le < k) {
                    low = mid+1;
                }
                mid = (low+high)/2;
            }
        }
    } else {
        if (l == 1) {
            comp_nodes[comp_cnt] = l_node;
            comp_cnt++;
            l = l_node->size+1;
        }
        if (r == r_node->size) {
            comp_nodes[comp_cnt] = r_node;
            comp_cnt++;
            r = 0;
        } 
        while (1) {
            int ls=0; int le=0;
            for (int idx=l-1; idx < l_node->size; idx++) {
                if (l_node->unsorted[idx] < mid) {
                    ls++; le++;
                } else if (l_node->unsorted[idx] == mid) {
                    le++;
                }
            }
            for (int idx=0; idx<r; idx++) {
                if (r_node->unsorted[idx] < mid) {
                    ls++; le++;
                } else if (r_node->unsorted[idx] == mid) {
                    le++;
                }
            }
            for (int i=0; i<comp_cnt; i++) {
                int tmp_ls = binSearchLs(comp_nodes[i]->sorted, comp_nodes[i]->size, mid);
                int tmp_eq = 0;
                for (int j=tmp_ls; j < comp_nodes[i]->size; j++) {
                    if (comp_nodes[i]->sorted[j] == mid)
                        tmp_eq++;
                    else
                        break;
                }
                ls += tmp_ls;
                le += tmp_ls + tmp_eq;
            }
            if (ls < k && le >= k) {
                break;
            } else {
                if (ls >= k) {
                    high = mid-1;
                } else if (le < k) {
                    low = mid+1;
                }
                mid = (low+high)/2;
            }
        }

    }
    return mid;
}


int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    int seg_len = (int) sqrt(n);
    if (seg_len*seg_len < n) {
        seg_len++;
    }
    
    int *init_arr = malloc((n+2)*sizeof(int));
    for (int i=0; i<n; i++) {
        scanf("%d", &init_arr[i]);
    }
    llist* list = buildFromArr(init_arr, n, seg_len);
    free(init_arr);
    
    for (int i=0; i<q; i++) {
        char cmd[10];
        scanf("%s", cmd);
        if (cmd[0] == 'Q') {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int result = query(list, l, r, k);
            printf("%d\n", result);
        } else if (cmd[0] == 'I') {
            int i, x;
            scanf("%d%d", &i, &x);
        } else if (cmd[0] == 'D') {
            int i;
            scanf("%d", &i);
        } else if (cmd[0] == 'R') {
            int l, r;
            scanf("%d%d", &l, &r);
        }
    }


    // for testing
    /*
    printf("node count: %d\ntotal size: %d\n", list->node_cnt, list->size);
    printf("---------\n");
    node* cur_node = list->head;
    int node_cnt = 0;
    while (cur_node) {
        printf("node %d\n", node_cnt);
        int arr_len = cur_node->size;
        printf("unsorted\n");
        for (int i=0; i<arr_len; i++) {
            printf("%d ", cur_node->unsorted[i]);
        }
        printf("\nsorted\n");
        for (int i=0; i<arr_len; i++) {
            printf("%d ", cur_node->sorted[i]);
        }
        printf("\n---------\n");
        cur_node = cur_node->nxt;
        node_cnt++;
    }
    // */
    return 0;
}