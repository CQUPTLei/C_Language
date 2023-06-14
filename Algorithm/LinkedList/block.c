#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 4  // 每个块中节点的数量

// 定义节点结构体
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 定义块结构体
typedef struct Block {
    Node nodes[BLOCK_SIZE];
    struct Block* next;
} Block;

// 初始化块
Block* initializeBlock() {
    Block* block = (Block*)malloc(sizeof(Block));
    block->next = NULL;
    return block;
}

// 从块中分配一个节点
Node* allocateNode(Block* block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (block->nodes[i].next == NULL) {
            return &(block->nodes[i]);
        }
    }
    return NULL;  // 没有可用的节点
}

// 释放节点到块中
void deallocateNode(Block* block, Node* node) {
    node->next = NULL;
}

// 向链表中插入节点
void insertNode(Block** head, int value) {
    Block* currentBlock = *head;
    Node* newNode = NULL;

    while (currentBlock != NULL) {
        newNode = allocateNode(currentBlock);
        if (newNode != NULL) {
            break;
        }
        currentBlock = currentBlock->next;
    }

    if (newNode == NULL) {
        // 没有可用的节点，需要分配新的块
        Block* newBlock = initializeBlock();
        newNode = allocateNode(newBlock);

        // 将新的块插入链表
        newBlock->next = *head;
        *head = newBlock;
    }

    newNode->data = value;
}

// 打印链表
void printList(Block* head) {
    Block* currentBlock = head;
    Node* currentNode = NULL;

    while (currentBlock != NULL) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            currentNode = &(currentBlock->nodes[i]);
            if (currentNode == NULL) {
                break;
            }
            printf("%d ", currentNode->data);
        }
        currentBlock = currentBlock->next;
    }
    printf("\n");
}

// 释放链表内存
void freeList(Block* head) {
    Block* currentBlock = head;
    Block* nextBlock = NULL;
    Node* currentNode = NULL;

    while (currentBlock != NULL) {
        nextBlock = currentBlock->next;
        for (int i = 0; i < BLOCK_SIZE; i++) {
            currentNode = &(currentBlock->nodes[i]);
            currentNode->next = NULL;
        }
        free(currentBlock);
        currentBlock = nextBlock;
    }
}

int main() {
    Block* head = initializeBlock();
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 4);
    insertNode(&head, 5);

    printf("List: ");
    printList(head);

    freeList(head);

    return 0;
}


