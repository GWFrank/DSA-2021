#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXN 1000007
int dsu[MAXN], sz[MAXN];
int str_hash(char *a) {
    int ret = 0;
    for(int i = 0; i < 4; i++) {
        ret *= 31;
        ret += a[i];
        ret %= MAXN;
    }
    return ret;
}
int find_fa(int x) {
    if(dsu[x] == x) return x;
    dsu[x] = find_fa(dsu[x]);
    return dsu[x];
}
void union_dsu(int a, int b) {
    int fa[2];
    fa[0] = find_fa(a), fa[1] = find_fa(b);
    if(fa[0] == fa[1]) return;
    if(sz[fa[0]] > sz[fa[1]]) {
        dsu[fa[1]] = fa[0];
        sz[fa[0]] += sz[fa[1]];
    }
    else {
        dsu[fa[0]] = fa[1];
        sz[fa[1]] += sz[fa[0]];
    }
}
int main() {
    memset(sz, 0, sizeof(sz));
    int n;
    scanf("%d", &n);
    while(n--) {
        char cmd[10], str[2][505];
        scanf("%s%s%s", cmd, str[0], str[1]);
        if(cmd[0] == 'c') {
            int len[2];
            for(int i = 0; i < 2; i++) len[i] = strlen(str[i]);
            if(len[0] != len[1]) {
                printf("False\n");
                continue;
            }
            bool bAns = true;
            for(int i = 0; i < len[0] / 4; i++) {
                int f[2];
                for(int j = 0; j < 2; j++) {
                    f[j] = str_hash(&str[j][4*i]);
                    if(sz[f[j]] == 0) {
                        sz[f[j]] = 1;
                        dsu[f[j]] = f[j];
                    }
                }
                if(find_fa(f[0]) != find_fa(f[1])) {
                    bAns = false;
                    break;
                }
            }
            printf("%s\n", (bAns ? "True" : "False"));
        }
        else {
            int ha[2];
            for(int i = 0; i < 2; i++) {
                ha[i] = str_hash(str[i]);
                if(sz[ha[i]] == 0) {
                    sz[ha[i]] = 1;
                    dsu[ha[i]] = ha[i];
                }
            }
            union_dsu(ha[0], ha[1]);
        }
    }
    return 0;
}
