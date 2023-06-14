// 链队  
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front; // 队头指针
    Node* rear; // 队尾指针
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Unable to dequeue.\n");
        return -1; // 返回一个表示错误的特殊值
    }
    
    int data = queue->front->data;
    Node* temp = queue->front;
    
    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    
    free(temp);
    return data;
}

void traverse(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Nothing to traverse.\n");
        return;
    }
    
    printf("Queue traversal:\n\t\t");
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    
    enqueue(queue, 5);
    enqueue(queue, 10);
    enqueue(queue, 3);
    
    traverse(queue);
    
    int data = dequeue(queue);
    printf("Dequeued data: %d\n", data);
    
    traverse(queue);
    
    return 0;
}
