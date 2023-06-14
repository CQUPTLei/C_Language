// 链式栈
#include <stdio.h>
#include <stdlib.h>

// 定义链式栈的节点结构
typedef struct Node {
    int data;           // 存储的元素值
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 定义链式栈结构
typedef struct {
    Node* top;  // 栈顶指针
} Stack;

// 初始化链式栈
void initStack(Stack* stack) {
    stack->top = NULL;
}

// 判断链式栈是否为空
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// 入栈
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 创建新节点
    newNode->data = value;
    newNode->next = stack->top;  // 新节点指向当前栈顶
    stack->top = newNode;        // 更新栈顶指针
}

// 出栈
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    
    int value = stack->top->data;   // 保存栈顶元素的值
    Node* temp = stack->top;        // 保存栈顶节点的指针
    stack->top = stack->top->next;  // 更新栈顶指针
    free(temp);                     // 释放原栈顶节点的内存
    
    return value;
}

// 获取栈顶元素的值
int top(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    
    return stack->top->data;
}

// 清空栈
void clear(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

// 测试链式栈
int main() {
    Stack stack;
    initStack(&stack);
    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    
    printf("Top element: %d\n", top(&stack));
    
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));
    
    printf("Top element: %d\n", top(&stack));
    
    clear(&stack);
    
    if (isEmpty(&stack)) {
        printf("Stack is empty.\n");
    }
    
    return 0;
}
 
