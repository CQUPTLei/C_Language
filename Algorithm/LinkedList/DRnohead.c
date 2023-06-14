#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* initializeList(int value) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = value;
    head->prev = head;
    head->next = head;
    return head;
}

void insertAtTail(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = head->prev;
    newNode->next = head;
    head->prev->next = newNode;
    head->prev = newNode;
}

void insertAtPosition(Node* head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    Node* current = head->next;
    int currentPosition = 0;
    while (current != head && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
}

void deleteAtPosition(Node* head, int position) {
    Node* current = head->next;
    int currentPosition = 0;
    while (current != head && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    if (current != head) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    }
}

void printList(Node* head) {
    Node* current = head->next;
    while (current != head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = initializeList(1);
    
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
