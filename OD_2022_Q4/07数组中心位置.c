#include <stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1024

int main() {
    int* nums;
    nums = (int*)malloc(MAX * sizeof(int));
    char input[MAX];
    fgets(input, MAX, stdin);

    int n = 0;
    char* p = strtok(input, " ");
    while (p != NULL) {
        nums[n++] = atoi(p);
        p = strtok(NULL, " ");
    }

    int left = 1;
    int right = 1;
    for (int i = 0; i < n; i++) { //全部元素的积
        right *= nums[i];
    }
    for (int i = 0; i < n; i++) {
        right /= nums[i]; //更新右侧积
        if (left == right) {
            //也可以用数组记录中心点的下标，输出所有中心点下标
            printf("%d\n", i);
            return 0;
        }
        left *= nums[i]; //更新左侧积
    }
    printf("-1\n");

    free(nums);
    return 0;
}