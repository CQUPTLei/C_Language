#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 200


// ����һ���ṹ���ʾһ�������
typedef struct {
    int row;
    int col;
} Point;

// ���һ�����Ƿ��Ѿ������ʹ�
bool visited[MAX_SIZE][MAX_SIZE];

// �ж�һ�����Ƿ��ھ�����
bool isInMatrix(Point point, int m, int n) {
    return point.row >= 0 && point.row < m && point.col >= 0 && point.col < n;
}

// DFS����������ĳ�������ڵ���ͨ����Ĵ�С
void dfs(char matrix[][MAX_SIZE], int m, int n, Point point, int* size) {
    // ����õ��Ѿ������ʹ����߸õ��Ǳ�ռ�õģ��򷵻�
    if (visited[point.row][point.col] || matrix[point.row][point.col] == 'X') {
        return;
    }

    // ��Ǹõ��Ѿ������ʹ�
    visited[point.row][point.col] = true;

    (*size)++; // ��ͨ����Ĵ�С��1

    // �����ĸ����������仯
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    // ö���ĸ��������ϡ��ҡ��£�
    for (int i = 0; i < 4; i++) {
        Point nextPoint = { point.row + dx[i], point.col + dy[i] };
        if (isInMatrix(nextPoint, m, n)) {
            // ����ھ����ڣ���ݹ����õ����ڵ���ͨ����Ĵ�С
            dfs(matrix, m, n, nextPoint, size);
        }
    }
}

int main() {

    int m, n;
    scanf("%d %d", &m, &n);

    //char matrix[MAX_SIZE][MAX_SIZE];
    char(*matrix)[MAX_SIZE];  //��malloc�ڶ������ڴ�
    matrix = (char(*)[MAX_SIZE])malloc(MAX_SIZE * MAX_SIZE * sizeof(char));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &matrix[i][j]); // ע��%cǰ���и��ո��������Ŀո����,��дX��O
        }
    }

    int maxAreaSize = -1; // ��¼�����ͨ����Ĵ�С
    int entranceRow = -1; // ��¼�����ͨ��������������
    int entranceCol = -1; // ��¼�����ͨ��������������
    bool hasUniqueMaxArea = true; // �Ƿ����Ψһ�������ͨ����

    // ö�����б߽��O��Ϊ��ڣ���һ�к����һ�У�
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 'O') {
            // ����õ���'O'��������Ըõ�Ϊ������ڵ���ͨ����Ĵ�С
            int areaSize = 0;
            dfs(matrix, m, n, (Point) { i, 0 }, & areaSize);
            if (areaSize > maxAreaSize) {
                // �������ͨ����Ĵ�С������ǰ�������ͨ����Ĵ�С������¼�¼
                maxAreaSize = areaSize;
                entranceRow = i;
                entranceCol = 0;
                hasUniqueMaxArea = true;
            }
            else if (areaSize == maxAreaSize) {
                // �������ͨ����Ĵ�С�뵱ǰ�������ͨ����Ĵ�С��ͬ����˵����Ψһ
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
    // ��һ�к����һ�����
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

    free(matrix); //�ͷ��ڴ�
    return 0;
}