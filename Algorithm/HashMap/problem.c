#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024 // 输入字符串最大长度

// 用于统计数字出现次数的结构体
typedef struct {
    int num;
    int count;
} Word;

// 排序函数
int qk_s(const void *a, const void *b) {
    Word *x = (Word *)a;
    Word *y = (Word *)b;
    return y->count - x->count;
}

// 处理输入字符串
void GetWords(int *save, int *count) {
    char *arr = (char *)malloc(MAX_LEN * sizeof(char));
    puts("Please input several numbers divided by space:");
    fgets(arr, MAX_LEN, stdin);
    arr[strlen(arr) - 1] = '\0';

    char *p = strtok(arr, " \n");

    while (p != NULL) {
        save[(*count)++] = atoi(p);
        p = strtok(NULL, " \n");
    }
    free(arr);
}

// 计算每个数字出现次数，并将结果降序排列
int CauCount(Word *word, const int *words, const int count) {
    word[0].num = words[0];
    word[0].count = 1;
    int index = 0; // 结构体数组下标
    for (int i = 1; i < count; i++) {
        int flag = 0;
        for (int j = 0; j < index + 1; j++) {
            if (words[i] == word[j].num) {
                word[j].count++;
                flag = 0;
                break;
            } else {
                flag = 1;
            }
        }
        if (flag == 1) {
            word[++index].num = words[i];
            word[index].count++;
        }
    }
    // 降序排列结果
    qsort(word, index + 1, sizeof(Word), qk_s);
    return index + 1; // 返回结构体数组实际用到的元素个数，即不重复的数字个数
}

int main() {
    int count = 0; // 数字数量(注意不是下标)
    int *words = (int *)malloc(MAX_LEN * sizeof(int));
    GetWords(words, &count);

    Word *word = (Word *)calloc(count, sizeof(Word));
    int num = CauCount(word, words, count);
    for (int i = 0; i < num; i++) {
        printf("数字：%d  出现次数：%d\n", word[i].num, word[i].count);
    }
    free(word);
    free(words);
    return 0;
}
