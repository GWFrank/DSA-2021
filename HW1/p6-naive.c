#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50005
#define MAX_X 100000
#define MIN_X -100000

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

void insert(int* arr, int arr_len, int idx, int x) {
    if (idx == arr_len+1) {
        arr[arr_len] = x;
    } else {
        int tmp_in = x;
        int tmp_out;
        for (int i=idx-1; i<arr_len+1; i++) {
            tmp_out = arr[i];
            arr[i] = tmp_in;
            tmp_in = tmp_out;
        }
    }
}

void delete(int* arr, int arr_len, int idx) {
    int tmp_in;
    int tmp_out;
    for (int i=idx-1; i<arr_len-1; i++) {
        arr[i] = arr[i+1];
    }
}

void reverse(int* arr, int l, int r) {
    while (l < r) {
        int tmp = arr[l-1];
        arr[l-1] = arr[r-1];
        arr[r-1] = tmp;
        l++; r--;
    }
}

int query(int* arr, int l, int r, int k) {
    int* tmp_arr = malloc((r-l+1)*sizeof(int));
    for (int i=0; i<(r-l+1); i++) {
        tmp_arr[i] = arr[l-1+i];
    }
    // printf("%d\n", tmp_arr[0]);
    qsort((void*) tmp_arr, r-l+1, sizeof(int), compare);
    int ans = tmp_arr[k-1];
    free(tmp_arr);
    return ans;
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    int arr[MAX_N];
    int arr_len = 0;
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
        arr_len++;
    }

    for (int i=0; i<q; i++) {
        char cmd[10];
        scanf("%s", cmd);
        if (cmd[0] == 'I') {
            int idx, x;
            scanf("%d%d", &idx, &x);
            insert(arr, arr_len, idx, x);
            arr_len++;
        } else if (cmd[0] == 'D') {
            int idx;
            scanf("%d", &idx);
            delete(arr, arr_len, idx);
            arr_len--;
        } else if (cmd[0] == 'R') {
            int l, r;
            scanf("%d%d", &l, &r);
            reverse(arr, l, r);
        } else if (cmd[0] == 'Q') {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", query(arr, l, r, k));
        }
    }


    return 0;
}