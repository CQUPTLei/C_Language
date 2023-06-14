// 带头结点的单链表
// 头指针指向头结点，头结点不存放数据
// 计算位置是从第一个数据节点开始计算，0即为第一个数据节点
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建链表
// 即创建一个头结点，head指针指向头结点，头结点指针为NULL
// 如果没有头结点，那么创建一个链表就至少有一个数据
Node *createList() {
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 在指定位置插入节点（前面）
void insertNode(Node *head, int position, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    Node *curr = head;
    int count = 0;
    while (curr && count < position) {
        curr = curr->next;
        count++;
    }

    if (curr) {
        newNode->next = curr->next; // 将新节指针指向插入位置后面的节点
        curr->next = newNode; // 插入位置的节点指针执行刚刚插入的新节点
    } else {
        printf("Invalid position.\n");
        free(newNode);
    }
}

// 删除指定位置的节点
void deleteNode(Node *head, int position) {
    Node *prev = head;       // 删除位置前一个节点
    Node *curr = head->next; // 删除位置的节点
    int count = 0;

    while (curr && count < position) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (curr) {
        prev->next = curr->next; // 将删除位置前一个节点指向删除位置后一个节点
        free(curr); // 释放删除位置的节点
    } else {
        printf("Invalid position.\n");
    }
}

// 根据值查找节点的位置
// 假设没有重复元素，否则只能返回第一个匹配到的，不过也可以进行修改
int findPositionByValue(Node *head, int value) {
    Node *curr = head->next; // 从第一个数据节点开始找，位置为0
    int position = 0;

    while (curr) {
        if (curr->data == value) {
            return position;
        }

        curr = curr->next;
        position++;
    }

    return -1; // 值不存在
}

// 根据位置查找节点的值
int findValueByPosition(Node *head, int position) {
    Node *curr = head->next;
    int count = 0;

    while (curr && count < position) {
        curr = curr->next;
        count++;
    }

    if (curr) {
        return curr->data;
    } else {
        printf("Invalid position.\n");
        return -1; // 位置无效
    }
}

// 根据位置修改节点的值
void modifyValueByPosition(Node *head, int position, int newValue) {
    Node *curr = head->next;
    int count = 0;

    while (curr && count < position) {
        curr = curr->next;
        count++;
    }

    if (curr) {
        curr->data = newValue;
    } else {
        printf("Invalid position.\n");
    }
}

// 获取链表长度（即数据节点的个数）
int getLength(Node *head) {
    Node *curr = head->next;
    int length = 0;

    while (curr) {
        curr = curr->next;
        length++;
    }

    return length;
}

// 遍历链表
void traverseList(Node *head) {
    Node *curr = head->next;

    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    printf("\n");
}

// 链表反转--迭代
Node *reverseList(Node *head) {
    Node *prev = NULL;
    Node *current = head->next;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head->next = prev;
    return head;
}


// 释放整个链表内存
void freeList(Node *head) {
    Node *curr = head->next;

    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(head);
}

// 测试链表操作
int main() {

    Node *myList = createList(); // 创建链表，即创建一个头结点

    insertNode(myList, 0, 1); //在开头插入1
    insertNode(myList, 1, 2);
    insertNode(myList, 2, 3);
    insertNode(myList, 1, 666);

    printf("List: ");
    traverseList(myList); // 遍历打印

    printf("Length: %d\n", getLength(myList)); // 求链表长度（数据节点个数）

    printf("Position of value 3: %d\n",
           findPositionByValue(myList, 3)); // 按位置查找
    printf("Value at position 1: %d\n",
           findValueByPosition(myList, 1)); // 按值查找

    modifyValueByPosition(myList, 1, 888); // 按位置修改

    printf("List after modification: ");
    traverseList(myList);

    deleteNode(myList, 2); // 按位置删除

    printf("List after deletion: ");
    traverseList(myList);

    myList = reverseList(myList);
    printf("After reverse: ");
    traverseList(myList);

    freeList(myList); // 释放链表内存

    return 0;
}
