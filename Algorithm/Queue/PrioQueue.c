#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int value;
    int priority;
} Element;

Element queue[MAX_SIZE];
int size = 0;

void enqueue(int value, int priority) {
    if (size >= MAX_SIZE) {
        printf("Queue is full. Unable to enqueue.\n");
        return;
    }
    
    int i = size - 1;
    while (i >= 0 && queue[i].priority > priority) {
        queue[i + 1] = queue[i];
        i--;
    }
    
    queue[i + 1].value = value;
    queue[i + 1].priority = priority;
    size++;
}

int dequeue() {
    if (size <= 0) {
        printf("Queue is empty. Unable to dequeue.\n");
        return -1; // Return a sentinel value indicating an error
    }
    
    int value = queue[0].value;
    
    for (int i = 1; i < size; i++) {
        queue[i - 1] = queue[i];
    }
    
    size--;
    return value;
}

void traverse() {
    if (size <= 0) {
        printf("Queue is empty. Nothing to traverse.\n");
        return;
    }
    
    printf("Queue traversal: \n\t");
    for (int i = 0; i < size; i++) {
        printf("Val: %3d   Prio: %d\n\t", queue[i].value, queue[i].priority);
    }
    printf("\n");
}

int main() {
    enqueue(5, 3);
    enqueue(10, 1);
    enqueue(3, 6);
    
    traverse();
    
    int value = dequeue();
    printf("Dequeued value: %d\n", value);
    
    traverse();

    enqueue(888, 4);
    printf("Enter (888,4)\n");
    traverse();
    
    return 0;
}
