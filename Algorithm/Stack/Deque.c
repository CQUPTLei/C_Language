// 双端栈
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front; // 头部指针
    int rear;  // 尾部指针
} Deque;

void initializeDeque(Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

int isFull(Deque* deque) {
    return (deque->front == 0 && deque->rear == MAX_SIZE - 1) || (deque->front == deque->rear + 1);
}

int isEmpty(Deque* deque) {
    return deque->front == -1;
}

void pushFront(Deque* deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full.\n");
        return;
    }

    if (deque->front == -1) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->front == 0) {
        deque->front = MAX_SIZE - 1;
    } else {
        deque->front--;
    }

    deque->data[deque->front] = value;
}

void pushBack(Deque* deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full.\n");
        return;
    }

    if (deque->front == -1) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->rear == MAX_SIZE - 1) {
        deque->rear = 0;
    } else {
        deque->rear++;
    }

    deque->data[deque->rear] = value;
}

int popFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }

    int value = deque->data[deque->front];

    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->front == MAX_SIZE - 1) {
        deque->front = 0;
    } else {
        deque->front++;
    }

    return value;
}

int popBack(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }

    int value = deque->data[deque->rear];

    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->rear == 0) {
        deque->rear = MAX_SIZE - 1;
    } else {
        deque->rear--;
    }

    return value;
}

int getFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }

    return deque->data[deque->front];
}

int getBack(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }

    return deque->data[deque->rear];
}

void clearDeque(Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

int main() {
    Deque deque;
    initializeDeque(&deque);

    pushFront(&deque, 1);
    pushFront(&deque, 2);
    pushBack(&deque, 3);

    printf("Front element: %d\n", getFront(&deque));  // Output: 2
    printf("Back element: %d\n", getBack(&deque));    // Output: 3

    printf("Popped front element: %d\n", popFront(&deque));  // Output: 2
    printf("Popped back element: %d\n", popBack(&deque));    // Output: 3

    printf("Front element after popping: %d\n", getFront(&deque));  // Output: 1
    printf("Back element after popping: %d\n", getBack(&deque));    // Output: 1

    clearDeque(&deque);

    return 0;
}
  
