#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <pthread.h>
#include <string.h>
#define MAX_NUM 30000200   // 最大素数范围
#define QUEUE_CAPACITY 20   // 队列容量
#define THREAD_NUM 10   // 线程数
#define TASK_NUM 200   // 任务数
#define PRIME_NUM 200   // 待计算的素数个数

// 定义任务队列
struct queue {
    int finished;
    int head;
    int tail;
    int data[QUEUE_CAPACITY];
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

// 定义线性表，用于存储待计算的素数
int prime[PRIME_NUM] = {0};
int prime_cnt = 0;

// 初始化任务队列
void queue_init(struct queue* q) {
    q->finished = 0;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond, NULL);
    printf("初始化OK\n");
}

// 向任务队列中添加数字
void queue_push(struct queue* q, int num) {
    pthread_mutex_lock(&q->mutex);
    printf("运行到queue_push");
    while(q->count >= QUEUE_CAPACITY && q->finished == 0) {
        // 队列已满，等待队列中的数字被取出
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    if(q->finished == 1) {
        pthread_mutex_unlock(&q->mutex);
        return;
    }

    q->data[q->tail] = num;
    q->tail = (q->tail + 1) % QUEUE_CAPACITY;
    q->count++;

    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->mutex);
}

// 从任务队列中获取数字
int queue_pop(struct queue* q) {
    pthread_mutex_lock(&q->mutex);
    printf("运行到queue_pop");
    while(q->count == 0 && q->finished == 0) {
        // 队列为空，等待数字到来
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    if(q->count == 0 && q->finished == 1) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }

    int num = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_CAPACITY;
    q->count--;

    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->mutex);

    return num;
}

// 线程执行的任务
void thread_task(struct queue* q) {
    int num;
    while(1) {
        pthread_mutex_lock(&q->mutex);  // 加锁
        num = queue_pop(q);
        if(num == -1) {
            // 队列为空并且finished为1，退出线程
            pthread_mutex_unlock(&q->mutex);  // 解锁
            break;
        }
        pthread_mutex_unlock(&q->mutex);  // 解锁

        // 判断数字是否为素数，如果是，输出线程号和数字
        int is_prime = 1;
        for(int i = 2; i < num; i++) {
            if(num % i >0) {
                is_prime = 0;
                break;
            }
        }
        if(is_prime) {
            pthread_mutex_lock(&q->mutex);  // 加锁
            printf("Thread %ld: %d is a prime\n", pthread_self(), num);
            // 将素数添加到线性表中
            prime[prime_cnt++] = num;
            pthread_mutex_unlock(&q->mutex);  // 解锁
        }
    }
}

int main() {
    pthread_t threads[THREAD_NUM];
    struct queue queue;
    queue_init(&queue);

    // 往任务队列中添加数字
    for(int i = 0; i < TASK_NUM; i++) {
        usleep(1000);
        printf("Number %d ",i);
        for(int j = 1; j <= 200; j++) {
            usleep(1000);
            printf(" %d",j);
            queue_push(&queue, 30000000 + i * 200 + j);
        }
        printf("\n");
    }
    //queue.finished = 1;

    printf("添加完成\n");
    // 创建线程池
    for(int i = 0; i < THREAD_NUM; i++) {
        pthread_create(&threads[i], NULL, (void*)thread_task, &queue);
        //pthread_create(&threads[i], NULL, (void*)thread_task, NULL);
    }

    queue.finished = 1;

    // 等待子线程执行完毕
    for(int i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    // 输出所有素数
    printf("All primes:\n");
    for(int i = 0; i < prime_cnt; i++) {
        printf("%d ", prime[i]);
    }
    printf("\n");

    return 0;
}  
