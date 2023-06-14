// 栈的应用：括号匹配
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, char c) {
    if (isFull(stack)) {
        printf("Stack is full.\n");
        return;
    }

    stack->data[++stack->top] = c;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return '\0';
    }

    return stack->data[stack->top--];
}
  

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')')
        return 1;
    else if (opening == '{' && closing == '}')
        return 1;
    else if (opening == '[' && closing == ']')
        return 1;
    else
        return 0;
}

int isParenthesesBalanced(char* expression) {
    Stack stack;
    initializeStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            push(&stack, expression[i]);
        } else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            if (isEmpty(&stack) || !isMatchingPair(pop(&stack), expression[i])) {
                return 0;
            }
        }
    }

    return isEmpty(&stack);
}

int main() {
    char expression[MAX_SIZE];
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);

    if (isParenthesesBalanced(expression)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are not balanced.\n");
    }

    return 0;
}
 
