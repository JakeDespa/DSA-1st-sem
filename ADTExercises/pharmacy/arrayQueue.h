#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <stdbool.h>

#define MAX 100  // Maximum capacity for each queue

typedef struct {
    int data[MAX];
    int front;
    int rear;
    int count;
} Queue;

// Function declarations
Queue* initialize();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void display(Queue* q);

#endif
