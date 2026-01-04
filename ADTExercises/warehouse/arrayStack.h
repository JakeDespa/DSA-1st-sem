#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdbool.h>

#define MAX 5  // Maximum capacity for each stack

typedef struct {
    int data[MAX];
    int top;
} Stack;

// Function declarations
void initialize(Stack *s);
bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
int top(Stack *s);
void display(Stack* s);

#endif
