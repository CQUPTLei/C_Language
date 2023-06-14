#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 65535

// 哈希表键值对
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// 哈希表结构体
typedef struct HashTable {
    Node** buckets; //桶数组指针
    int size;       //哈希表大小（即桶数组的大小）
} HashTable;

//创建哈希表
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (Node**)calloc(size, sizeof(Node*)); //calloc可以初始化为0
    return table;
}

//删除哈希表
void destroyHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* node = table->buckets[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int hash(int key, int size) {
    return key % size;
}

//插入记录
void insert(HashTable* table, int key, int value) {
    int index = hash(key, table->size);
    Node* node = table->buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

//查找记录
int find(HashTable* table, int key) {
    int index = hash(key, table->size);
    Node* node = table->buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return 0;
}

int mainq() {

    int n;
    scanf("%d", &n);

    HashTable* table = createHashTable(MAX + 1);

    int max_freq = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        int freq = find(table, x) + 1;
        insert(table, x, freq);
        if (freq > max_freq) {
            max_freq = freq;
        }
    }

    int min_len = n + 1;
    for (int i = 1; i <= MAX; i++) {
        if (find(table, i) == max_freq) {
            int len = 0;
            int start = -1;
            for (int j = 0; j < n; j++) {
                int x;
                scanf("%d", &x);
                if (x == i) {
                    if (start == -1) {
                        start = j;
                    }
                    len++;
                }
                else if (len > 0) {
                    if (j - start < min_len) {
                        min_len = j - start;
                    }
                    len = 0;
                    start = -1;
                }
            }
            if (len > 0 && n - start < min_len) {
                min_len = n - start;
            }
        }
    }
    printf("%d\n", min_len);

    destroyHashTable(table);

    return 0;
}