/*
Refs:
B09902100
https://en.wikipedia.org/wiki/Fenwick_tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

#define MAX_CORD 1048575
#define MIN_CORD -1048576
#define OFFSET 1-(MIN_CORD)

typedef struct __tri__  {
    int p;
    int q;
    int r;
} tri;

int cmpP(const void *a, const void *b) {
    tri tri_a = *(tri*)a;
    tri tri_b = *(tri*)b;
    return tri_a.p - tri_b.p;
}

int lowbit(int x){
    return x&(-x);
}

int main() {
    generator.init();
    int t = generator.getT();
    // /*
    while (t--) {
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);

        // Sort triangles by p
        // tri** paths = malloc(n*sizeof(tri*));
        tri paths[10000];
        for (int i=0; i<n; i++) {
            // paths[i] = malloc(sizeof(tri));
            paths[i].p = p[i];
            if (q[i] < r[i]) {
                paths[i].q = q[i];
                paths[i].r = r[i];
            } else {
                paths[i].q = r[i];
                paths[i].r = q[i];
            }
        }
        qsort(paths, n, sizeof(tri), cmpP);
        printf("Hey\n");
        // Find seperated pairs to calculate intersecting pairs
        long long int sep = 0;
        // Use a Binary Index Tree to store r values
        int BIT[2097153] = {0};
        // int* BIT = calloc(MAX_CORD-MIN_CORD+1+1, sizeof(int));
        int* r_hold = malloc(n*sizeof(int));
        int hold_size = 0;
        int old_p = MIN_CORD-100;
        for (int i=0; i<n; i++) {
            int p_i = paths[i].p;
            int q_i = paths[i].q;
            int r_i = paths[i].r;
            // Insert all holding r if proceed to a new p value
            if (p_i != old_p) {
                while (hold_size) {
                    hold_size--;
                    for (int j=r_hold[hold_size]+OFFSET; j<= MAX_CORD-MIN_CORD+1;
                            j+=lowbit(j)) {
                        BIT[j]++;
                    }
                }
                old_p = p_i;
            }
            // Query sum from MIN_CORD to q_i
            for (int j=q_i+OFFSET-1; j>0; j-=lowbit(j)) {
                sep += BIT[j];
            }
            // Add r_i to waiting line
            r_hold[hold_size] = r_i;
            hold_size++;
        }

        // Use long long int to avoid overflow for large n
        long long int lln = (long long int) n;
        long long int ans = lln*(lln-1)/2 - sep;
        printf("%lld\n", ans);

        // Free allocated memories
        free(r_hold);
    }
    // */
}