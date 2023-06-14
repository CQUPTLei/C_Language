// 循环队列
#include <stdio.h>

#define MAX_SIZE 100

// 定义循环队列结构体
typedef struct {
    int data[MAX_SIZE];
    int front;  // 队首索引
    int rear;   // 队尾索引
    int size;   // 直接用一个size来记录大小，简化空、满的判断
} CircularQueue;

// 初始化循环队列
void initQueue(CircularQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

// 判断循环队列是否为空
int isEmpty(CircularQueue *queue) {
    return (queue->size == 0);
}

// 判断循环队列是否已满
int isFull(CircularQueue *queue) {
    return (queue->size == MAX_SIZE);
}

// 入队
void enqueue(CircularQueue *queue, int item) {
    if (isFull(queue)) {
        printf("循环队列已满，无法插入元素\n");
        return;
    }

    queue->data[queue->rear] = item;
   // 注意对队尾索引的计算，因为它是循环的 
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    // 更新元素个数
    queue->size++;
}

// 出队
int dequeue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        printf("循环队列为空，无法删除元素\n");
        return -1;
    }

    int item = queue->data[queue->front];
    // 同理
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;

    return item;
}

// 获取循环队列长度
int getQueueLength(CircularQueue *queue) {
    return queue->size;
}

int main() {
    CircularQueue queue;
    initQueue(&queue);

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("循环队列长度: %d\n", getQueueLength(&queue));

    printf("出队元素: %d\n", dequeue(&queue));
    printf("出队元素: %d\n", dequeue(&queue));

    printf("循环队列长度: %d\n", getQueueLength(&queue));

    return 0;
}
