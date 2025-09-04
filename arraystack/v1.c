#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // Example size

typedef struct {
    int items[MAX];
    int top;
} Stack;

// Initialize Variation 1
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;   // empty
    return s;
}

// Push operation
void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

// Pop operation
int pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack Underflow! Nothing to pop.\n");
        return -1;
    }
    int value = s->items[s->top];
    s->top--;
    return value;
}

// Peek operation
int peek(Stack* s) {
    if (s->top == -1) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return s->items[s->top];
}

// Display operation
void display(Stack* s) {
    if (s->top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

// Example usage
int main() {
    Stack* S = initialize();

    push(S, 10);
    push(S, 20);
    push(S, 30);
    display(S);

    printf("Peek: %d\n", peek(S));

    printf("Popped: %d\n", pop(S));
    display(S);

    return 0;
}
