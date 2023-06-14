#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

int n, m;
int a[MAXN + 2][MAXN + 2];
int ans = MAXN * MAXN;

void dfs(int x, int y, int step) {
    if (step >= ans) return;
    if (x == n + 1) {
        ans = step;
        return;
    }
    if (y == m + 1) {
        dfs(x + 1, 1, step);
        return;
    }
    if (x == 1 || a[x - 1][y] == 0) {
        dfs(x, y + 1, step);
        return;
    }
    a[x][y] ^= 1; a[x - 1][y] ^= 1; a[x + 1][y] ^= 1; a[x][y - 1] ^= 1; a[x][y + 1] ^= 1;
    dfs(x, y + 1, step + 1);
    a[x][y] ^= 1; a[x - 1][y] ^= 1; a[x + 1][y] ^= 1; a[x][y - 1] ^= 1; a[x][y + 1] ^= 1;
    dfs(x, y + 1, step);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    dfs(1, 1, 0);
    printf("%d\n", ans);
    return 0;
}