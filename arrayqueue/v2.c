#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// Initialize queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 1;
    q->rear = 0;
    return q;
}

// Check if empty
int isEmpty(Queue* q) {
    return q->front == (q->rear + 1) % MAX;
}

// Check if full
int isFull(Queue* q) {
    return q->front == (q->rear + 2) % MAX;
}

// Enqueue
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}

// Dequeue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return value;
}

// Peek front
int front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// Display
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    int i = q->front;
    while (i != (q->rear + 1) % MAX) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}
