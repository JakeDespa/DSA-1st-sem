#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int items[MAX];
    int front, rear, count;
} Queue;

// Initialize queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    q->count = 0;
    return q;
}

// Check if empty
int isEmpty(Queue* q) {
    return q->count == 0;
}

// Check if full
int isFull(Queue* q) {
    return q->count == MAX;
}

// Enqueue
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear] = value;
    q->count++;
}

// Dequeue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->count == 1) { // last element removed
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    q->count--;
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
    int i, idx;
    for (i = 0; i < q->count; i++) {
        idx = (q->front + i) % MAX;
        printf("%d ", q->items[idx]);
    }
    printf("\n");
}
