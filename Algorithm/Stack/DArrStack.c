// 数组栈，动态
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;     // 数据 
    int top;       // 栈顶指针
    int capacity;  // 初始容量
} ArrayStack;

void initStack(ArrayStack* stack, int capacity) {
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
}

int isEmpty(ArrayStack* stack) {
    return stack->top == -1;
}

int isFull(ArrayStack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(ArrayStack* stack, int item) {
    if (isFull(stack)) {
        // 动态调整容量
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[++stack->top] = item;
    printf("Pushed item %d.\n", item);
}

int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop item.\n");
        return -1;
    }
    int item = stack->data[stack->top--];
    printf("Popped item %d.\n", item);

    // 动态调整容量
    if (stack->top + 1 <= stack->capacity / 4) {
        stack->capacity /= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }
    return item;
}

int peek(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot peek.\n");
        return -1;
    }
    return stack->data[stack->top];
}
void freeStack(ArrayStack* stack) {
    free(stack->data);
}

int main() {
    int capacity = 2;
    ArrayStack stack;
    initStack(&stack, capacity);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    int topItem = peek(&stack);
    printf("Top item: %d\n", topItem);

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);

    freeStack(&stack);

    return 0;
}
