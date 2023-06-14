#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// 哈希表节点结构
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// 哈希表结构
typedef struct HashTable {
    // 桶数组，里面有SIZE个链表
    Node* buckets[SIZE];
} HashTable;

// 创建哈希表
HashTable* createHashTable() {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < SIZE; i++) {
        hashtable->buckets[i] = NULL;
    }
    return hashtable;
}

// 哈希函数
int hashFunction(int key) {
    return key % SIZE;
}

// 向哈希表中插入键值对
void insert(HashTable* hashtable, int key, int value) {
    int index = hashFunction(key);
    
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    
    // 如果桶为空，则直接插入新节点
    if (hashtable->buckets[index] == NULL) {
        hashtable->buckets[index] = newNode;
    } else {
        // 否则，在链表末尾插入新节点
        Node* current = hashtable->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// 根据键查找哈希表中的值
int search(HashTable* hashtable, int key) {
    int index = hashFunction(key);
    
    // 查找链表中对应的节点
    Node* current = hashtable->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    // 若未找到，返回-1
    return -1;
}

// 从哈希表中删除键值对
void delete(HashTable* hashtable, int key) {
    int index = hashFunction(key);
    
    // 查找链表中对应的节点
    Node* current = hashtable->buckets[index];
    Node* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                // 若为头节点，直接修改桶指针
                hashtable->buckets[index] = current->next;
            } else {
                // 否则修改前一个节点的指针
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// 销毁哈希表
void destroyHashTable(HashTable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        Node* current = hashtable->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashtable);
}

int main() {
    HashTable* hashtable = createHashTable();
    
    // 插入键值对
    insert(hashtable, 1, 10);
    insert(hashtable, 11, 20);   
    insert(hashtable, 21, 30);
    
    // 查找值
    int value =search(hashtable, 11);
    if(value) printf("Find key =11 ,value = %d\n",value);
    else printf("key=11 not exist.\n");
    // 销毁哈希表
    destroyHashTable(hashtable);
    
    return 0;
}
