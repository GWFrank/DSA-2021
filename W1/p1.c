#include <stdio.h>
#define MINN -4
#define MAXN 4
int main() {
    int storage[MAXN - MINN + 1]={0};
    int *ary = &storage[MAXN - 1];
    for (int i=MINN; i<= MAXN; i++)
        ary[i] = i;
    for (int i=MINN; i<= MAXN; i++)
        printf("%d ", ary[i]);
    return 0;
}