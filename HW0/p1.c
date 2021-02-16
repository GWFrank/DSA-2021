#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 260


void printBigInt(int a[MAX_LEN]) {
    // prints out a Big Int
    int st_print = 0;
    for (int i=(MAX_LEN-1); i>=0; i--) {
        if (st_print) {
            printf("%d", a[i]);
        } else {
            if (a[i] != 0) {
                st_print = 1;
                printf("%d", a[i]);
            }
        }
    }
    printf("\n");
}

int largerBigInt(int a[MAX_LEN], int b[MAX_LEN]) {
    // returns a>=b
    for (int i=(MAX_LEN-1); i>=0; i--) {
        if (a[i] > b[i])
            return 1;
        else if (b[i] > a[i])
            return 0;
        else
            continue;
    }
    return 1;
}

int eqBigInt(int a[MAX_LEN], int b[MAX_LEN]) {
    for (int i=0; i<MAX_LEN; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

int *subsBigInt(int a[MAX_LEN], int b[MAX_LEN]) {
    // returns a-b
    int *ans = malloc(MAX_LEN * sizeof(int));
    int borrow = 0;
    for (int i=0; i<MAX_LEN; i++) {
        int dig_a = a[i]-borrow, dig_b = b[i];
        if (dig_a >= dig_b) {
            ans[i] = dig_a-dig_b;
            borrow = 0;
        } else {
            ans[i] = 10+(dig_a-dig_b);
            borrow = 1;
        }
    }
    return ans;
}

int *mult2BigInt(int a[MAX_LEN]) {
    // returns a*2
    int *ans = malloc(MAX_LEN * sizeof(int));
    int carry = 0;
    for (int i=0; i<MAX_LEN; i++) {
        int dig_ans = a[i]*2 + carry;
        ans[i] = dig_ans%10;
        carry = dig_ans/10;
    }
    return ans;
}

int *pwr2BigInt(int a[MAX_LEN], int pwr) {
    int *ans = malloc(MAX_LEN * sizeof(int));
    for (int i=0; i<MAX_LEN; i++)
        ans[i] = a[i];
    for (int i=0; i<pwr; i++) {
        int *free_ptr = ans;
        ans = mult2BigInt(ans);
        free(free_ptr);
    }
    return ans;
}

int *div2BigInt(int a[MAX_LEN]) {
    // returns a/2
    int *ans = malloc(MAX_LEN * sizeof(int));
    int remain = 0;
    for (int i=MAX_LEN-1; i>=0; i--) {
        int dividend = 10*remain + a[i];
        ans[i] = dividend/2;
        remain = dividend%2;
    }
    return ans;
}

int *gcdBigInt(int a[MAX_LEN], int b[MAX_LEN]) {
    // returns gcd(a, b)
    int ans_pwr=0, zero[MAX_LEN]={0};
    
    int *n, *m;
    if (largerBigInt(a, b)) {
        m = a; n = b; 
    } else {
        m = b; n = a; 
    }

    while ((!eqBigInt(n, zero)) && (!eqBigInt(m, zero))) {
        int n_even = 1-n[0]%2, m_even = 1-m[0]%2;
        int *free_ptr;
        if (n_even) {
            free_ptr = n;
            n = div2BigInt(n);
            free(free_ptr);
        }
        if (m_even) {
            free_ptr = m;
            m = div2BigInt(m);
            free(free_ptr);
        }
        if (n_even && m_even) {
            ans_pwr++;
        }
        if (largerBigInt(n, m)) {
            int *tmp = n;
            n = m;
            m = tmp;
        }
        free_ptr = m;
        m = subsBigInt(m, n);
        free(free_ptr);
    }
    int *ans = pwr2BigInt(n, ans_pwr);
    free(m);
    free(n);
    return ans;
}

int main(){
    // int a[MAX_LEN]={0}, b[MAX_LEN]={0};
    int *a = malloc(MAX_LEN*sizeof(int)), *b = malloc(MAX_LEN*sizeof(int));
    int *a_ptr = a, *b_ptr = b;
    char n[MAX_LEN];
    
    scanf("%s", n);
    int l = strlen(n);
    for (int i=0; i<l; i++) {
        a[(l-1)-i] = (n[i] - '0');
    }

    scanf("%s", n);
    l = strlen(n);
    for (int i=0; i<l; i++) {
        b[(l-1)-i] = (n[i] - '0');
    }

    int *gcd = gcdBigInt(a, b);
    printBigInt(gcd);
    free(gcd);
    return 0;
}