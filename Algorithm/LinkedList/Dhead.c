// 带头结点的双向老板
#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 初始化双向链表，即创建头结点
void initializeList(Node** head) {
    *head = (Node*)malloc(sizeof(Node));
    (*head)->data = 0;
    (*head)->prev = NULL;
    (*head)->next = NULL;
}

// 在链表头部插入节点
void insertAtHead(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = head;
    newNode->next = head->next;
    if (head->next != NULL) {
        head->next->prev = newNode;
    }
    head->next = newNode;
}

// 在链表尾部插入节点
void insertAtTail(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
    newNode->prev = current;
}

// 在指定位置插入节点
void insertAtPosition(Node* head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    Node* current = head;
    int currentPosition = 0;
    while (current != NULL && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    
    if (current == NULL) {
        printf("Invalid position!\n");
        free(newNode);
        return;
    }
    
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
}

// 删除头节点
void deleteAtHead(Node* head) {
    if (head->next == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* toDelete = head->next;
    head->next = toDelete->next;
    if (toDelete->next != NULL) {
        toDelete->next->prev = head;
    }
    
    free(toDelete);
}

// 删除尾节点
void deleteAtTail(Node* head) {
    if (head->next == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->prev->next = NULL;
    free(current);
}

// 删除指定位置的节点
void deleteAtPosition(Node* head, int position) {
    if (head->next == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* current = head;
    int currentPosition = 0;
    while (current->next != NULL && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    
    if (current->next == NULL) {
        printf("Invalid position!\n");
        return;
    }
    
    Node* toDelete = current->next;
    current->next = toDelete->next;
    if (toDelete->next != NULL) {
        toDelete->next->prev = current;
    }
    
    free(toDelete);
}

// 打印链表
void printList(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head;
    initializeList(&head);
    
    insertAtHead(head, 2);
    insertAtHead(head, 1);
    insertAtTail(head, 3);
    insertAtPosition(head, 4, 2);
    
    printf("List: ");
    printList(head);
    
    deleteAtHead(head);
    deleteAtTail(head);
    deleteAtPosition(head, 1);
    
    printf("List after deletion: ");
    printList(head);
    
    return 0;
}  
