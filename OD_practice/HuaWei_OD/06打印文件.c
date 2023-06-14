#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct node {
    int num;    // �ļ����
    int priority; // �ļ����ȼ�
    struct node* next;
}Node;

Node* head[6];  // ��̨��ӡ���Ķ���ͷ
int count[6];   // ��̨��ӡ���Ѿ���ӡ���ļ�����

// ��ʼ������
void init() {
    for (int i = 1; i <= 5; i++) {
        head[i] = (Node*)malloc(sizeof(Node));
        head[i]->next = NULL;
        count[i] = 0;
    }
}

// ���ӡ��i�Ķ����в������ȼ�Ϊprio���ļ�
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

// ��ӡ��i��ӡһ���ļ�
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
    scanf("%d", &n); //�¼�����
    init();          //��ʼ��
    while (n--) {
        int i, prio;
        char od[4];
        scanf("%s %d",od,&i); //�ȶ�ȡ2�����ǲ��룬�ٶ�ȡ���ȼ�
        if (strcmp(od, "IN") == 0) {
            scanf("%d", &prio);
            insert(i, prio);
        } 
        else
            print(i);
    
    }

    return 0;
}
