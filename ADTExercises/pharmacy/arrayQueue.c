#include <stdio.h>
#include <stdlib.h>
#include "arrayQueue.h"

// Initialize the queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;
}

// Check if queue is full
bool isFull(Queue* q) {
    return q->count == MAX;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return q->count == 0;
}

// Add an element to the queue
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot enqueue %d\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
    q->count++;
}

// Remove an element from the queue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return value;
}

// Display all elements in the queue
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents (front to rear): ");
    int index = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->data[index]);
        index = (index + 1) % MAX;
    }
    printf("\n");
}
