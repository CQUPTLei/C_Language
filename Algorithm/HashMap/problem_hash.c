#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024 // 输入字符串最大长度
#define HASH_SIZE 100

// 哈希表节点
typedef struct Node {
    int num;
    int count;
    struct Node* next;
} Node;

// 哈希表
typedef struct HashTable {
    Node* buckets[HASH_SIZE];
} HashTable;

// 创建哈希表
HashTable* createHashTable() {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    memset(hashtable->buckets, 0, sizeof(Node*) * HASH_SIZE);
    return hashtable;
}

// 哈希函数
int hash(int num) {
    return num % HASH_SIZE;
}

// 查找节点
Node* findNode(HashTable* hashtable, int num) {
    int index = hash(num);
    Node* node = hashtable->buckets[index];
    while (node != NULL) {
        if (node->num == num) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// 插入节点
void insertNode(HashTable* hashtable, int num) {
    int index = hash(num);
    Node* node = findNode(hashtable, num);
    if (node != NULL) {
        node->count++;
    } else {
        node = (Node*)malloc(sizeof(Node));
        node->num = num;
        node->count = 1;
        node->next = hashtable->buckets[index];
        hashtable->buckets[index] = node;
    }
}

// 处理输入字符串
void GetWords(int *save, int *count) {
    char *arr = (char *)malloc(MAX_LEN * sizeof(char));
    puts("Please input several nums divided by space:");
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
int CauCount(Node **word, const int *nums, const int count) {
    Node* hashtable[HASH_SIZE] = { NULL };
    for (int i = 0; i < count; i++) {
        int index = hash(nums[i]);
        Node* node = hashtable[index];
        while (node != NULL) {
            if (node->num == nums[i]) {
                node->count++;
                break;
            }
            node = node->next;
        }
        if (node == NULL) {
            node = (Node*)malloc(sizeof(Node));
            node->num = nums[i];
            node->count = 1;
            node->next = hashtable[index];
            hashtable[index] = node;
        }
    }

    int index = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* node = hashtable[i];
        while (node != NULL) {
            word[index] = node;
            node = node->next;
            index++;
        }
    }

    // 降序排列结果
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (word[j]->count < word[j + 1]->count) {
                Node* temp = word[j];
                word[j] = word[j + 1];
                word[j + 1] = temp;
            }
        }
    }
    return index;
}

// 输出数字计数结果
void PrintResult(const Node **word, const int count) {
    for (int i = 0; i < count; i++) {
        printf("数字：%d  出现次数：%d\n", word[i]->num, word[i]->count);
    }
}

// 释放哈希表内存
void destroyHashTable(Node **word, const int count) {
    for (int i = 0; i < count; i++) {
        free(word[i]);
    }
}

int main() {
    int count = 0; // 数字数量(注意不是下标)
    int words[MAX_LEN];
    GetWords(words, &count);

    Node* word[MAX_LEN];
    int num = CauCount(word, words, count);
    PrintResult((const Node **)word, num);

    destroyHashTable(word, num);
    return 0;
}
