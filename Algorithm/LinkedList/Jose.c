#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;


Node* createCircularList(int n) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 1; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    tail->next = head;  // 将最后一个节点的 next 指针指向头节点，形成循环

    return head;
}


int josephusCircle(Node* head, int m) {
    Node* current = head;
    Node* prev = NULL;

    while (current->next != current) {
        // 报数 m-1 次，找到要出列的节点
        for (int i = 0; i < m - 1; i++) {
            prev = current;
            current = current->next;
        }
        printf("%d out\n",current->data);
        // 删除当前节点
        prev->next = current->next;
        Node* toDelete = current;
        current = prev->next;
        free(toDelete);
    }

    return current->data;  // 返回最后剩下的节点的编号
}


int main() {
    int n = 7;  // 人数
    int m = 3;  // 报数值

    Node* head = createCircularList(n);
    int lastPerson = josephusCircle(head, m);

    printf("The last person remaining is %d\n", lastPerson);

    return 0;
}
