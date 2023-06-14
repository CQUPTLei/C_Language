#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 65535

// ��ϣ���ֵ��
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// ��ϣ��ṹ��
typedef struct HashTable {
    Node** buckets; //Ͱ����ָ��
    int size;       //��ϣ���С����Ͱ����Ĵ�С��
} HashTable;

//������ϣ��
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (Node**)calloc(size, sizeof(Node*)); //calloc���Գ�ʼ��Ϊ0
    return table;
}

//ɾ����ϣ��
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

//�����¼
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

//���Ҽ�¼
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