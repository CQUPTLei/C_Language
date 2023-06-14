#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 200


// 定义一个结构体表示一个坐标点
typedef struct {
    int row;
    int col;
} Point;

// 标记一个点是否已经被访问过
bool visited[MAX_SIZE][MAX_SIZE];

// 判断一个点是否在矩阵内
bool isInMatrix(Point point, int m, int n) {
    return point.row >= 0 && point.row < m && point.col >= 0 && point.col < n;
}

// DFS函数，计算某个点所在的连通区域的大小
void dfs(char matrix[][MAX_SIZE], int m, int n, Point point, int* size) {
    // 如果该点已经被访问过或者该点是被占用的，则返回
    if (visited[point.row][point.col] || matrix[point.row][point.col] == 'X') {
        return;
    }

    // 标记该点已经被访问过
    visited[point.row][point.col] = true;

    (*size)++; // 连通区域的大小加1

    // 定义四个方向的坐标变化
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    // 枚举四个方向（左、上、右、下）
    for (int i = 0; i < 4; i++) {
        Point nextPoint = { point.row + dx[i], point.col + dy[i] };
        if (isInMatrix(nextPoint, m, n)) {
            // 如果在矩阵内，则递归计算该点所在的连通区域的大小
            dfs(matrix, m, n, nextPoint, size);
        }
    }
}

int main() {

    int m, n;
    scanf("%d %d", &m, &n);

    //char matrix[MAX_SIZE][MAX_SIZE];
    char(*matrix)[MAX_SIZE];  //用malloc在堆申请内存
    matrix = (char(*)[MAX_SIZE])malloc(MAX_SIZE * MAX_SIZE * sizeof(char));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &matrix[i][j]); // 注意%c前面有个空格，用于消耗空格符号,大写X和O
        }
    }

    int maxAreaSize = -1; // 记录最大连通区域的大小
    int entranceRow = -1; // 记录最大连通区域的入口行坐标
    int entranceCol = -1; // 记录最大连通区域的入口列坐标
    bool hasUniqueMaxArea = true; // 是否存在唯一的最大连通区域

    // 枚举所有边界的O点为入口（第一列和最后一列）
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 'O') {
            // 如果该点是'O'，则计算以该点为入口所在的连通区域的大小
            int areaSize = 0;
            dfs(matrix, m, n, (Point) { i, 0 }, & areaSize);
            if (areaSize > maxAreaSize) {
                // 如果该连通区域的大小超过当前的最大连通区域的大小，则更新记录
                maxAreaSize = areaSize;
                entranceRow = i;
                entranceCol = 0;
                hasUniqueMaxArea = true;
            }
            else if (areaSize == maxAreaSize) {
                // 如果该连通区域的大小与当前的最大连通区域的大小相同，则说明不唯一
                hasUniqueMaxArea = false;
            }
        }
        if (matrix[i][n - 1] == 'O') {
            int areaSize = 0;
            dfs(matrix, m, n, (Point) { i, n - 1 }, & areaSize);
            if (areaSize > maxAreaSize) {
                maxAreaSize = areaSize;
                entranceRow = i;
                entranceCol = n - 1;
                hasUniqueMaxArea = true;
            }
            else if (areaSize == maxAreaSize) {
                hasUniqueMaxArea = false;
            }
        }
    }
    // 第一行和最后一行入口
    for (int j = 0; j < n; j++) {
        if (matrix[0][j] == 'O') {
            int areaSize = 0;
            dfs(matrix, m, n, (Point) { 0, j }, & areaSize);
            if (areaSize > maxAreaSize) {
                maxAreaSize = areaSize;
                entranceRow = 0;
                entranceCol = j;
                hasUniqueMaxArea = true;
            }
            else if (areaSize == maxAreaSize) {
                hasUniqueMaxArea = false;
            }
        }
        if (matrix[m - 1][j] == 'O') {
            int areaSize = 0;
            dfs(matrix, m, n, (Point) { m - 1, j }, & areaSize);
            if (areaSize > maxAreaSize) {
                maxAreaSize = areaSize;
                entranceRow = m - 1;
                entranceCol = j;
                hasUniqueMaxArea = true;
            }
            else if (areaSize == maxAreaSize) {
                hasUniqueMaxArea = false;
            }
        }
    }


    if (maxAreaSize == -1) {
        printf("NULL\n");
    }
    else if (hasUniqueMaxArea) {
        printf("%d %d %d\n", entranceRow, entranceCol, maxAreaSize);
    }
    else {
        printf("%d\n", maxAreaSize);
    }

    free(matrix); //释放内存
    return 0;
}