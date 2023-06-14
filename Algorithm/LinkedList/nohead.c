// 不带头结点的链表
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建链表（是Node*类型）
Node* createList() {
    return NULL;
}

// 在链表头部插入节点
Node* insertNode(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

// 在指定位置插入节点
//  这个函数也可以实现头插
Node* insertNodeAtPosition(Node* head, int position, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (position == 0) {
        newNode->next = head;
        return newNode;
    }
    
    Node* curr = head;
    int count = 0;
    
    while (curr && count < position - 1) {
        curr = curr->next;
        count++;
    }
    
    if (curr && count == position - 1) {
        newNode->next = curr->next;
        curr->next = newNode;
    } else {
        printf("Invalid position.\n");
        free(newNode);
    }
    
    return head;
}

// 删除指定位置的节点
Node* deleteNode(Node* head, int position) {
    if (position == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    Node* prev = head;
    Node* curr = head->next;
    int count = 0;
    
    while (curr && count < position - 1) {
        prev = curr;
        curr = curr->next;
        count++;
    }
    
    if (curr && count == position - 1) {
        prev->next = curr->next;
        free(curr);
    } else {
        printf("Invalid position.\n");
    }
    
    return head;
}

// 根据值查找节点的位置
int findPositionByValue(Node* head, int value) {
    Node* curr = head;
    int position = 0;
    
    while (curr) {
        if (curr->data == value) {
            return position;
        }
        
        curr = curr->next;
        position++;
    }
    
    return -1;  // 值不存在
}

// 根据位置查找节点的值
int findValueByPosition(Node* head, int position) {
    Node* curr = head;
    int count = 0;
    
    while (curr && count < position) {
        curr = curr->next;
        count++;
    }
    
    if (curr && count == position) {
        return curr->data;
    } else {
        printf("Invalid position.\n");
        return -1;  // 位置无效
    }
}

// 根据位置修改节点的值
void modifyValueByPosition(Node* head, int position, int newValue) {
    Node* curr = head;
    int count = 0;
    
    while (curr && count < position) {
        curr = curr->next;
        count++;
    }
    
    if (curr && count == position) {
        curr->data = newValue;
    } else {
        printf("Invalid position.\n");
    }
}

// 获取链表长度
   
int getLength(Node* head) {
    Node* curr = head;
    int length = 0;
    
    while (curr) {
        curr = curr->next;
        length++;
    }
    
    return length;
}

// 遍历链表
void traverseList(Node* head) {
    Node* curr = head;
    
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    
    printf("\n");
}

// 释放链表内存
void freeList(Node* head) {
    Node* curr = head;
    
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// 测试链表操作
int main() {
    Node* myList = createList();
    
    myList = insertNode(myList, 1);   // 头插
    myList = insertNode(myList, 2);
    myList = insertNode(myList, 3);
    myList=insertNodeAtPosition(myList, 1, 666);  
    myList=insertNodeAtPosition(myList, 0, 888);  // 也可以实现头


    printf("List: ");
    traverseList(myList);
    
    printf("Length: %d\n", getLength(myList));
    
    printf("Position of value 2: %d\n", findPositionByValue(myList, 2));
    printf("Value at position 1: %d\n", findValueByPosition(myList, 1));
    
    modifyValueByPosition(myList, 1, 4);
    
    printf("List after modification: ");
    traverseList(myList);
    
    myList = deleteNode(myList, 2);
    
    printf("List after deletion: ");
    traverseList(myList);
    
    freeList(myList);  // 释放链表内存
    
    return 0;
}
