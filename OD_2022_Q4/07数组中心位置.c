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
    for (int i = 0; i < n; i++) { //ȫ��Ԫ�صĻ�
        right *= nums[i];
    }
    for (int i = 0; i < n; i++) {
        right /= nums[i]; //�����Ҳ��
        if (left == right) {
            //Ҳ�����������¼���ĵ���±꣬����������ĵ��±�
            printf("%d\n", i);
            return 0;
        }
        left *= nums[i]; //��������
    }
    printf("-1\n");

    free(nums);
    return 0;
}