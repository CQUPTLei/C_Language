// 顺序队列
#include <stdio.h>

#define MAX_SIZE 100

// 定义队列结构体
typedef struct {
    int data[MAX_SIZE];
    int front;  // 队首索引
    int rear;   // 队尾索引
} Queue;

// 初始化队列
void initQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

// 判断队列是否为空
int isEmpty(Queue *queue) {
    return (queue->front == queue->rear);
}

// 判断队列是否已满
int isFull(Queue *queue) {
    return (queue->rear == MAX_SIZE);
}

// 入队
void enqueue(Queue *queue, int item) {
    if (isFull(queue)) {
        printf("队列已满，无法插入元素\n");
        return;
    }

    queue->data[queue->rear] = item;
    queue->rear++;
}

// 出队
int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("队列为空，无法删除元素\n");
        return -1;
    }

    int item = queue->data[queue->front];
    queue->front++;

    return item;
}

// 获取队列长度
int getQueueLength(Queue *queue) {
    return queue->rear - queue->front;
}

int main() {
    Queue queue;
    initQueue(&queue);

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("队列长度: %d\n", getQueueLength(&queue));

    printf("出队元素: %d\n", dequeue(&queue));
    printf("出队元素: %d\n", dequeue(&queue));

    printf("队列长度: %d\n", getQueueLength(&queue));

    return 0;
}
