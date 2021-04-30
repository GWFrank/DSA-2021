#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MIN_W 0
#define MAX_W 1000000005

void evalAccess(int idx, int up, int down, int* keys, int* lefts, int* rights, int* cnt) {
    int real_idx = idx-1;
    int key = keys[real_idx];
    int right = rights[real_idx];
    int left = lefts[real_idx];
    int new_up = (key < up) ? key : up;
    int new_down = (key > down) ? key : down;
    printf("---------------\n");
    printf("%d\n", idx);
    printf("%d %d %d\n", up, key, down);
    if (key < up && key > down) {
        *cnt = *cnt+1;
        printf("found!\n");
    }
    if (left > 0) {
        evalAccess(left, new_up, down, keys, lefts, rights, cnt);
    }
    if (right > 0) {
        evalAccess(right, up, new_down, keys, lefts, rights, cnt);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int* keys = malloc(n*sizeof(int));
    int* lefts = malloc(n*sizeof(int));
    int* rights = malloc(n*sizeof(int));
    for (int i=0; i<n; i++) {
        scanf("%d%d%d", &keys[i], &lefts[i], &rights[i]);
    }

    int *cnt = malloc(sizeof(int));
    *cnt = 0;
    evalAccess(1, MAX_W, MIN_W, keys, lefts, rights, cnt);
    printf("%d\n", *cnt);
    return 0;
}