#include <stdio.h>
#include <stdlib.h>
#include "arrayStack.h"

// Initialize the stack
void initialize(Stack *s) {
    s->top = -1;
}

// Check if stack is full
bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Check if stack is empty
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// Push an element onto the stack
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack is full! Cannot push %d\n", value);
        return;
    }
    s->data[++s->top] = value;
}

// Pop an element from the stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }
    return s->data[s->top--];
}

// Peek at the top element without removing it
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return s->data[s->top];
}

// Get the current top index
int top(Stack *s) {
    return s->top;
}

// Display all elements in the stack
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack contents (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}
