#include <stdio.h>

int main(){
    int* ptr_arr[3];
    *(ptr_arr[0]) = 50;
    *(ptr_arr[1]) = 20;
    *(ptr_arr[2]) = 40;
    for (int i=0; i<3; i++) {
        printf("%d\n", *(ptr_arr[i]));
    }
    return 0;
}