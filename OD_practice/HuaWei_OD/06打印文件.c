#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct node {
    int num;    // 文件编号
    int priority; // 文件优先级
    struct node* next;
}Node;

Node* head[6];  // 五台打印机的队列头
int count[6];   // 五台打印机已经打印的文件数量

// 初始化队列
void init() {
    for (int i = 1; i <= 5; i++) {
        head[i] = (Node*)malloc(sizeof(Node));
        head[i]->next = NULL;
        count[i] = 0;
    }
}

// 向打印机i的队列中插入优先级为prio的文件
void insert(int i, int prio) {
    Node* p = head[i];
    while (p->next != NULL && p->next->priority >= prio) {
        p = p->next;
    }
    Node* new_file = (Node*)malloc(sizeof(Node));
    new_file->num = ++count[i];
    new_file->priority = prio;
    new_file->next = p->next;
    p->next = new_file;
}

// 打印机i打印一份文件
void print(int i) {
    Node* p = head[i]->next;
    if (p == NULL) {
        printf("NULL\n");
    }
    else {
        printf("%d\n", p->num);
        head[i]->next = p->next;
        free(p);
    }
}

int main() {
    int n;
    scanf("%d", &n); //事件数量
    init();          //初始化
    while (n--) {
        int i, prio;
        char od[4];
        scanf("%s %d",od,&i); //先读取2项，如果是插入，再读取优先级
        if (strcmp(od, "IN") == 0) {
            scanf("%d", &prio);
            insert(i, prio);
        } 
        else
            print(i);
    
    }

    return 0;
}
