#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 初始化链表，创建头节点
Node* initializeList() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->prev = head;
    head->next = head; // 头节点的前后指针都指向自身形成循环
    return head;
}

// 在链表尾部插入节点
void insertAtTail(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = head->prev;
    newNode->next = head;
    head->prev->next = newNode; // 新节点插入到尾节点之后
    head->prev = newNode; // 更新尾节点
}

// 在指定位置插入节点
void insertAtPosition(Node* head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    Node* current = head;
    int currentPosition = 0;
    while (current->next != head && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    newNode->prev = current;
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
}

// 删除指定位置的节点
void deleteAtPosition(Node* head, int position) {
    Node* current = head;
    Node* toDelete = NULL;
    int currentPosition = 0;
    while (current->next != head && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    toDelete = current->next;
    current->next = toDelete->next;
    toDelete->next->prev = current;
    free(toDelete);
}

// 打印链表
void printList(Node* head) {
    Node* current = head->next;
    while (current != head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = initializeList();
    
    insertAtTail(head, 1);
    insertAtTail(head, 2);
    insertAtTail(head, 3);
    insertAtPosition(head, 4, 2);
    
    printf("List: ");
    printList(head);
    
    deleteAtPosition(head, 1);
    
    printf("List after deletion: ");
    printList(head);
    
    return 0;
} 
