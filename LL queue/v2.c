/*
 * Variation 2: Queue implemented as a Linked List
 * FRONT is a pointer to the last node of the list
 * REAR is a pointer to the first node of the list
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
    Node* front;  // Points to the last node
    Node* rear;   // Points to the first node
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
    return (q == NULL || q->rear == NULL);
}

// Enqueue operation - add element at the rear (first node position)
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
        // New node is both rear (first) and front (last)
        q->rear = newNode;
        q->front = newNode;
    } else {
        // New node becomes the new rear (first node)
        newNode->next = q->rear;
        q->rear = newNode;
    }
    
    printf("Enqueued: %d\n", value);
}

// Dequeue operation - remove element from the front (last node position)
int dequeue(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    
    // Special case: only one node in the queue
    if (q->rear == q->front) {
        int value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return value;
    }
    
    // Traverse to the node before front (last node)
    Node* temp = q->rear;
    while (temp->next != q->front) {
        temp = temp->next;
    }
    
    // Store the data of the front node (last node)
    int value = q->front->data;
    
    // Free the front node
    free(q->front);
    
    // Update front to the previous node
    q->front = temp;
    q->front->next = NULL;
    
    return value;
}

// Get the front element without removing it (last node)
int front(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    // Return data of front node (last node)
    return q->front->data;
}

// Display all elements in the queue (from rear to front)
void display(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue contents (rear to front): ");
    // Create temporary pointer to traverse
    Node* temp = q->rear;
    
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
    
    printf("=== Queue Variation 2 Demo ===\n");
    printf("FRONT -> last node, REAR -> first node\n\n");
    
    // Test isEmpty
    printf("Is queue empty? %s\n\n", isEmpty(Q) ? "Yes" : "No");
    
    // Enqueue operations
    printf("--- Enqueue Operations ---\n");
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    display(Q);
    printf("Front element: %d\n\n", front(Q));
    
    // Enqueue one more
    enqueue(Q, 4);
    display(Q);
    printf("Front element: %d\n\n", front(Q));
    
    // Dequeue operations
    printf("--- Dequeue Operations ---\n");
    int value = dequeue(Q);
    printf("Dequeued: %d\n", value);
    display(Q);
    printf("Front element: %d\n\n", front(Q));
    
    // More dequeue
    value = dequeue(Q);
    printf("Dequeued: %d\n", value);
    display(Q);
    printf("Front element: %d\n\n", front(Q));
    
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
