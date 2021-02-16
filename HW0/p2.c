#include <stdio.h>
#include <stdlib.h>

#define MAX_L 30


void printGraph(int **graph, int row_n, int col_n) {
    for (int i=0; i<row_n; i++) {
        for (int j=0; j<col_n; j++) {
            if (graph[i][j] == 1)
                printf("o");
            else if (graph[i][j] == -1)
                printf("_");
            else if (graph[i][j] == 0)
                printf("@");
        }
        printf("\n");
    }
}

int *cntRow(int **graph, int row, int col_n) {
    int *ans = malloc(MAX_L*sizeof(int));
    ans[0] = 0;
    int cnting=0, len=0, ans_idx=1;
    for (int i=0; i<col_n; i++) {
        if (graph[row][i] == 1) {
            len++;
            if (cnting) {
                continue;
            } else {
                cnting = 1;
            }
        } else if (graph[row][i] == -1) {
            if (cnting) {
                cnting = 0;
                ans[ans_idx] = len;
                ans[0]++;
                ans_idx++;
                len=0;
            } else {
                continue;
            }            
        }
    }
    // for getting counts in tail
    if (cnting) {
        ans[ans_idx] = len;
        ans[0]++;
    }
    return ans;
}

int *cntCol(int **graph, int col, int row_n) {
    int *ans = malloc(MAX_L*sizeof(int));
    ans[0] = 0;
    int cnting=0, len=0, ans_idx=1;
    for (int i=0; i<row_n; i++) {
        if (graph[i][col] == 1) {
            len++;
            if (cnting) {
                continue;
            } else {
                cnting = 1;
            }
        } else if (graph[i][col] == -1) {
            if (cnting) {
                cnting = 0;
                ans[ans_idx] = len;
                ans[0]++;
                ans_idx++;
                len=0;
            } else {
                continue;
            }            
        }
    }
    // for getting counts in tail
    if (cnting) {
        ans[ans_idx] = len;
        ans[0]++;
    }
    return ans;
}

int cmpClue(int *clue, int *guess) {
    if (clue[0] != guess[0]) {
        return 0;
    } else {
        for (int i=1; i<=clue[0]; i++) {
            if (clue[i] != guess[i]) {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int **graph, int row_n, int col_n, int **row_clue, int **col_clue) {
    for (int r=0; r<row_n; r++) {
        for (int c=0; c<col_n; c++) {
            if (graph[r][c] == 0) {
                graph[r][c] = 1;
                if (solve(graph, row_n, col_n, row_clue, col_clue)) {
                    return 1;
                }
                graph[r][c] = -1;
                if (solve(graph, row_n, col_n, row_clue, col_clue)) {
                    return 1;
                }
                graph[r][c] = 0;
                return 0;
            }
        }
        int *row_status = cntRow(graph, r, col_n);
        int legal_row = cmpClue(row_clue[r], row_status);
        free(row_status);
        if (!legal_row){
            return 0;    
        }
    }

    for (int c=0; c<col_n; c++) {
        int *col_status = cntCol(graph, c, row_n);
        int legal_col = cmpClue(col_clue[c], col_status);
        free(col_status);
        if (!legal_col) {
            return 0;
        }
    }

    return 1;
}


int main() {
    int row_n, col_n;
    scanf("%d%d", &row_n, &col_n);

    int **graph = malloc(row_n*sizeof(int*));
    for (int i=0; i<row_n; i++) {
        graph[i] = malloc(col_n*sizeof(int));
        for (int j=0; j<col_n; j++) {
            graph[i][j] = 0;
        }
    }

    int **row_clue = malloc(row_n*sizeof(int*));
    for (int i=0; i<row_n; i++) {
        int seg_n;
        scanf("%d", &seg_n);
        row_clue[i] = malloc(MAX_L*sizeof(int));
        row_clue[i][0] = seg_n;
        for (int j=1; j<=seg_n; j++) {
            scanf("%d", &row_clue[i][j]);
        }
    }
    int **col_clue = malloc(col_n*sizeof(int*));
    for (int i=0; i<col_n; i++) {
        int seg_n;
        scanf("%d", &seg_n);
        col_clue[i] = malloc(MAX_L*sizeof(int));
        col_clue[i][0] = seg_n;
        for (int j=1; j<=seg_n; j++) {
            scanf("%d", &col_clue[i][j]);
        }
    }

    // printGraph(graph, row_n, col_n);
    int solved = solve(graph, row_n, col_n, row_clue, col_clue);
    if (solved) {
        printGraph(graph, row_n, col_n);
    } else {
        printf("No Solutions!\n");
    }

    return 0;
}