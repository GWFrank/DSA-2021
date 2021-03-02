#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

typedef struct array{
    int data[MAXLEN];
    int len;
} array;

void prtArr(array *arr) {
    for (int i=0; i<arr->len; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

void insert(array *arr, int data) {
    arr->data[arr->len] = data;
    arr->len ++;
    int i = arr->len - 1;
    while (i>0) {
        if (arr->data[i] < arr->data[i-1]) {
            int tmp = arr->data[i];
            arr->data[i] = arr->data[i-1];
            arr->data[i-1] = tmp;
            i--;
        } else {
            break;
        }
    }
}

array *init() {
    array *ptr = malloc(sizeof(array));
    ptr->len = 0;
    return ptr;
}

array *construct(int *iarr, int len) {
    array *arr = init();
    for (int i=0; i<len; i++) {
        insert(arr, iarr[i]);
    }
    return arr;
}

void updateByIdx(array *arr, int index, int new_data) {
    arr->data[index] = new_data;
    if (index > 0 && arr->len > 1) {
        int i=index;
        while (i>0) {
            if (arr->data[i] < arr->data[i-1]) {
                int tmp = arr->data[i];
                arr->data[i] = arr->data[i-1];
                arr->data[i-1] = tmp;
                i--;
            } else {
                break;
            }
        }
    }
    if (index < (arr->len)-1 && arr->len > 1) {
        int i=index;
        while (i<(arr->len)-1) {
            if (arr->data[i] > arr->data[i+1]) {
                int tmp = arr->data[i];
                arr->data[i] = arr->data[i+1];
                arr->data[i+1] = tmp;
                i++;
            } else {
                break;
            }
        }
    }
}

void removeByIdx(array *arr, int index) {
    for (int i=index; i<(arr->len)-1; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->len--;
}

int main(){
    while (1) {
        int len;
        scanf("%d", &len);
        int iarr[MAXLEN];
        for (int i=0; i<len; i++) {
            scanf("%d", &iarr[i]);
        }
        array *ordered_arr = construct(iarr, len);
        prtArr(ordered_arr);
        
        int update_idx, update_data;
        scanf("%d%d", &update_idx, &update_data);
        updateByIdx(ordered_arr, update_idx, update_data);
        prtArr(ordered_arr);
        
        int remove_idx;
        scanf("%d", &remove_idx);
        removeByIdx(ordered_arr, remove_idx);
        prtArr(ordered_arr);
        
    }
    return 0;
}