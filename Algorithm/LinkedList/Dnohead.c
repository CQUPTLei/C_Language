// 不带头结点的双向链表
#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 初始化双向链表
Node* initializeList() {
    return NULL;
}

// 在链表头部插入节点
Node* insertAtHead(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}

// 在链表尾部插入节点
Node* insertAtTail(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
    newNode->prev = current;
    
    return head;
}

// 在指定位置插入节点
Node* insertAtPosition(Node* head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    if (position <= 0) {
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        return newNode;
    }
    
    Node* current = head;
    int currentPosition = 0;
    while (current != NULL && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    
    if (current == NULL) {
        printf("Invalid position!\n");
        free(newNode);
        return head;
    }
    
    newNode->prev = current->prev;
    newNode->next = current;
    
    if (current->prev != NULL) {
        current->prev->next = newNode;
    }
    current->prev = newNode;
    
    if (currentPosition == 0) {
        return newNode;
    }
    
    return head;
}

// 删除头节点
Node* deleteAtHead(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    Node* toDelete = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    
    free(toDelete);
    return head;
}

// 删除尾节点
Node* deleteAtTail(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->prev->next = NULL;
    free(current);
    return head;
}

// 删除指定位置的节点
Node* deleteAtPosition(Node* head, int position) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
        if (position <= 0) {
        Node* toDelete = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(toDelete);
        return head;
    }
    
    Node* current = head;
    int currentPosition = 0;
    while (current != NULL && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    
    if (current == NULL) {
        printf("Invalid position!\n");
        return head;
    }
    
    current->prev->next = current->next;
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
    return head;
}

// 打印链表
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = initializeList();
    
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);
    head = insertAtTail(head, 3);
    head = insertAtPosition(head, 4, 2);
    
    printf("List: ");
    printList(head);
    
    head = deleteAtHead(head);
    head = deleteAtTail(head);
    head = deleteAtPosition(head, 1);
    
    printf("List after deletion: ");
    printList(head);
    
    return 0;
} 
