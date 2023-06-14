// 线性探测法
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// 哈希表节点结构
typedef struct {
    int key;
    int value;
} Node;

// 哈希表结构
typedef struct {
    Node* data[SIZE];
} HashTable;

// 创建哈希表
HashTable* createHashTable() {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < SIZE; i++) {
        hashtable->data[i] = NULL;
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
    
    // 寻找下一个可用的位置
    while (hashtable->data[index] != NULL) {
        index = (index + 1) % SIZE;
    }
    
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    
    // 插入新节点
    hashtable->data[index] = newNode;
}

// 根据键查找哈希表中的值
int search(HashTable* hashtable, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    
    // 从哈希表中寻找对应的键值对
    while (hashtable->data[index] != NULL) {
        if (hashtable->data[index]->key == key) {
            return hashtable->data[index]->value;
        }
        index = (index + 1) % SIZE;
        
        // 如果回到原始位置，则说明未找到
        if (index == originalIndex) {
            break;
        }
    }
    
    // 若未找到，返回-1
    return -1;
}

// 从哈希表中删除键值对
void delete(HashTable* hashtable, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    
    // 从哈希表中寻找对应的键值对
    while (hashtable->data[index] != NULL) {
        if (hashtable->data[index]->key == key) {
            free(hashtable->data[index]);
            hashtable->data[index] = NULL;
            return;
        }
        index = (index + 1) % SIZE;
        
        // 如果回到原始位置，则说明未找到
        if (index == originalIndex) {
            break;
        }
    }
}

// 销毁哈希表
void destroyHashTable(HashTable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        if (hashtable->data[i] != NULL) {
            free(hashtable->data[i]);
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
    int value = search(hashtable, 1);
    if (value != -1) {
        printf("找到了，值为：%d\n", value);
    } else {
        printf("未找到该键\n");
    }
    
    // 删除键值对
    delete(hashtable, 1);
    
    // 再次查找
    value = search(hashtable, 1);
    if (value != -1) {
        printf("找到了，值为：%d\n", value);
    } else {
        printf("未找到该键\n");
    }
    
    // 销毁哈希表
    destroyHashTable(hashtable);
    
    return 0;
}
 
