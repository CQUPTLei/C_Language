#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char key[20];
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair table[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
    }
    return hashValue % TABLE_SIZE;
}

void insert(HashTable* hashTable, const char* key, int value) {
    unsigned int index = hash(key);
    strcpy(hashTable->table[index].key, key);
    hashTable->table[index].value = value;
}

void  get(HashTable* hashTable, const char* key) {
     bool flag;
     int value;
    unsigned int index = hash(key);
    if (strcmp(hashTable->table[index].key, key) == 0 && hashTable->table[index].key[0] != '\0') {
        value = hashTable->table[index].value;
        flag=true;
    }
    else flag=false;
    if(flag) printf("Value for %s:%d\n",key,value);
    else printf("key %s not found.\n",key);
}

int main() {
    HashTable hashTable;
    memset(hashTable.table, 0, sizeof(hashTable.table));

    insert(&hashTable, "apple", 1);
    insert(&hashTable, "apple",88);
    insert(&hashTable, "banana", 2);
    insert(&hashTable, "orange", 3);

    get(&hashTable,"apple");
    get(&hashTable, "orange");

    return 0;
}
