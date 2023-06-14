// 数组栈，静态
#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];  // 数组栈
    int top;      // 栈顶 指针（等于数组元素下标，-1表示空）
} ArrayStack;

void initStack(ArrayStack* stack) {
    stack->top = -1;  // 初始化栈顶指针为-1，表示栈为空
}

int isEmpty(ArrayStack* stack) {
    return stack->top == -1;  // 栈顶指针为-1表示栈为空
}

int isFull(ArrayStack* stack) {
    return stack->top == MAX_SIZE - 1;  // 栈顶指针等于最大容量减1表示栈已满
}

void push(ArrayStack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push item %d.\n", item);
    } else {
        stack->data[++stack->top] = item;  // 将元素入栈，并将栈顶指针加1
        printf("Pushed item %d.\n", item);
    }
}

int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop item.\n");
        return -1;  // 返回一个特殊值表示栈为空
    } else {
        int item = stack->data[stack->top--];  // 栈顶元素出栈，并将栈顶指针减1
        printf("Popped item %d.\n", item);
        return item;  // 返回出栈的元素值
    }
}

// 取栈顶元素，并不弹出栈顶元素 
int peek(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot peek.\n");
        return -1;  // 返回一个特殊值表示栈为空
    } else {
        return stack->data[stack->top];  // 返回栈顶元素的值
    }
}

int main() {
    ArrayStack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    int topItem = peek(&stack);
    printf("Top item: %d\n", topItem);

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);  // 出栈空栈

    return 0;
}
 
