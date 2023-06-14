#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include<math.h>

void find_equ(int **input,int n,int m) {

    int** Out_arr = (int**)malloc(sizeof(int*) * n);//存放输出值：距离
    for (int i = 0; i < n; ++i) {
        Out_arr[i] = (int*)calloc(m,sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int count = 0; //检查是否有元素与input[i][j]相等
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < m; b++) {
                    if (i != a || j != b) {  //不与自己比
                        if (input[i][j] == input[a][b]) {
                            count++;
                            if (Out_arr[i][j] == 0)
                                Out_arr[i][j] = abs(i - a) + abs(j - b);
                            else
                                if (Out_arr[i][j] > (abs(i - a) + abs(j - b)))
                                    Out_arr[i][j] = abs(i - a) + abs(j - b);
                        }   
                    }
                }
            }
            if (count == 0)Out_arr[i][j] = -1;
        }
    }

    printf("[");
    for (int i = 0; i < n; ++i) {
        printf("[");
        for (int j = 0; j < m; j++) {
            printf("%d", Out_arr[i][j]);
            if (j != m - 1) {
                printf(",");
            }
        }
        printf("]");
        if (i != n - 1) {
            printf(",");
        }
    }
    printf("]");
    for (int i = 0; i < n; ++i) {
        free(Out_arr[i]);
    }
    free(Out_arr);
}



int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    //int* arr = (int(*)[m])malloc(n * m * sizeof(int));
    int** arr = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) {
        arr[i] = (int*)malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }


    //solveMethod(arr, n, m);
    find_equ(arr,n,m);
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}

