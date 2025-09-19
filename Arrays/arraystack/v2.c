#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // Example size

typedef struct {
    int items[MAX];
    int top;
} Stack;

// Initialize Variation 2
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = MAX;   // empty
    return s;
}

// Push operation
void push(Stack* s, int value) {
    if (s->top == 0) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->top--;  // move left
    s->items[s->top] = value;
}

// Pop operation
int pop(Stack* s) {
    if (s->top == MAX) {
        printf("Stack Underflow! Nothing to pop.\n");
        return -1;
    }
    int value = s->items[s->top];
    s->top++;  // move right
    return value;
}

// Peek operation
int peek(Stack* s) {
    if (s->top == MAX) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return s->items[s->top];
}

// Display operation
void display(Stack* s) {
    if (s->top == MAX) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = s->top; i < MAX; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

// Example usage
int main() {
    Stack* S = initialize();

    push(S, 100);
    push(S, 200);
    push(S, 300);
    display(S);

    printf("Peek: %d\n", peek(S));

    printf("Popped: %d\n", pop(S));
    display(S);

    return 0;
}
