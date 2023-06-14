#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SIZE 10

// 哈希表节点结构
typedef struct {
    char* key;
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

// 计算SHA-256哈希值
void sha256Hash(const char* input, unsigned char* output) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, input, strlen(input));
    SHA256_Final(output, &ctx);
}

// 将SHA-256哈希值转换为索引
int hashFunction(const unsigned char* hash) {
    int index = 0;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        index += hash[i];
    }
    return index % SIZE;
}

// 向哈希表中插入键值对
void insert(HashTable* hashtable, const char* key, int value) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256Hash(key, hash);
    int index = hashFunction(hash);
    
    // 寻找下一个可用的位置
    while (hashtable->data[index] != NULL) {
        index = (index + 1) % SIZE;
    }
    
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    
    // 插入新节点
    hashtable->data[index] = newNode;
}

// 根据键查找哈希表中的值
int search(HashTable* hashtable, const char* key) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256Hash(key, hash);
    int index = hashFunction(hash);
    
    // 从哈希表中寻找对应的键值对
    while (hashtable->data[index] != NULL) {
        if (strcmp(hashtable->data[index]->key, key) == 0) {
            return hashtable->data[index]->value;
        }
        index = (index + 1) % SIZE;
    }
    
    // 若未找到，返回-1
    return -1;
}

// 从哈希表中删除键值对
void delete(HashTable* hashtable, const char* key) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256Hash(key, hash);
    int index = hashFunction(hash);
    
    // 从哈希表中寻找对应的键值对
    while (hashtable->data[index] != NULL) {
        if (strcmp(hashtable->data[index]->key, key) == 0) {
            free(hashtable->data[index]->key);
            free(hashtable->data[index]);
            hashtable->data[index] = NULL;
            return;
        }
        index = (index + 1) % SIZE;
    }
}

// 销毁哈希表
void destroyHashTable(HashTable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        if (hashtable->data[i] != NULL) {
            free(hashtable->data[i]->key);
            free(hashtable->data[i]);
        }
    }
    free(hashtable);
}

int main() {
    HashTable* hashtable = createHashTable();
    
    // 插入键值对
    insert(hashtable, "apple", 10);
    insert(hashtable, "banana", 20);
    insert(hashtable, "orange", 30);
    
    // 查找值
    int value = search(hashtable, "apple");
    if (value != -1) {
        printf("找到了，值为：%d\n", value);
    } else {
        printf("未找到该键\n");
    }
    
    // 删除键值对
    delete(hashtable, "apple");
    
    // 再次查找
    value = search(hashtable, "apple");
    if (value != -1) {
        printf("找到了，值为：%d\n", value);
    } else {
        printf("未找到该键\n");
    }
    
    // 销毁哈希表
    destroyHashTable(hashtable);
    
    return 0;
}
 
