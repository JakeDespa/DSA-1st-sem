/*
 * Variation 1: Queue implemented as a Linked List
 * FRONT is a pointer to the first node of the list
 * REAR is a pointer to the last node of the list
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure with front and rear pointers
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to allocate memory for the queue structure and initialize pointers
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

// Check if the queue is full (linked list can never be full)
bool isFull(Queue* q) {
    return false;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    return (q == NULL || q->front == NULL);
}

// Enqueue operation - add element at the rear
void enqueue(Queue* q, int value) {
    if (q == NULL) {
        printf("Queue not initialized!\n");
        return;
    }
    
    // Allocate memory for a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Set the data and next pointer
    newNode->data = value;
    newNode->next = NULL;
    
    // Check if queue is empty
    if (isEmpty(q)) {
        // New node is both front and rear
        q->front = newNode;
        q->rear = newNode;
    } else {
        // Link current rear to new node
        q->rear->next = newNode;
        // Update rear pointer to new node
        q->rear = newNode;
    }
    
    printf("Enqueued: %d\n", value);
}

// Dequeue operation - remove element from the front
int dequeue(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    
    // Store temporary pointer to front node
    Node* temp = q->front;
    // Store the data of the front node
    int value = temp->data;
    
    // Move front pointer to next node
    q->front = q->front->next;
    
    // If queue becomes empty, update rear pointer to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    // Free memory of old front node
    free(temp);
    
    return value;
}

// Get the front element without removing it
int front(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    // Return data of front node
    return q->front->data;
}

// Display all elements in the queue
void display(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue contents: ");
    // Create temporary pointer to traverse
    Node* temp = q->front;
    
    // Loop through list until NULL is reached
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate the queue operations
int main() {
    // Initialize the queue
    Queue* Q = initialize();
    
    printf("=== Queue Variation 1 Demo ===\n");
    printf("FRONT -> first node, REAR -> last node\n\n");
    
    // Test isEmpty
    printf("Is queue empty? %s\n\n", isEmpty(Q) ? "Yes" : "No");
    
    // Enqueue operations
    printf("--- Enqueue Operations ---\n");
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    display(Q);
    printf("\n");
    
    // Enqueue one more
    enqueue(Q, 4);
    display(Q);
    printf("\n");
    
    // Front operation
    printf("--- Front Operation ---\n");
    printf("Front element: %d\n\n", front(Q));
    
    // Dequeue operations
    printf("--- Dequeue Operations ---\n");
    int value = dequeue(Q);
    printf("Dequeued: %d\n", value);
    display(Q);
    printf("\n");
    
    // More dequeue
    dequeue(Q);
    display(Q);
    printf("\n");
    
    // Test isFull
    printf("Is queue full? %s\n", isFull(Q) ? "Yes" : "No");
    
    // Cleanup remaining elements
    printf("\n--- Cleanup ---\n");
    while (!isEmpty(Q)) {
        printf("Dequeued: %d\n", dequeue(Q));
    }
    
    printf("Is queue empty? %s\n", isEmpty(Q) ? "Yes" : "No");
    
    // Free the queue structure
    free(Q);
    
    return 0;
}
