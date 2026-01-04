#include <stdio.h>
#include <stdlib.h>
#include "arrayQueue.h"

// Function prototypes
void enterRegularQueue(Queue* regularQ, int* queueNumber);
void enterPriorityQueue(Queue* priorityQ, int* queueNumber);
void callNextCustomer(Queue* regularQ, Queue* priorityQ);
void displayQueues(Queue* regularQ, Queue* priorityQ);

int main() {
    // GUIDE QUESTION 1: Declare and initialize the two queues
    Queue* regularQueue = initialize();
    Queue* priorityQueue = initialize();
    
    if (regularQueue == NULL || priorityQueue == NULL) {
        printf("Failed to initialize queues!\n");
        return 1;
    }
    
    int queueNumber = 1;  // Sequential queue number starting from 1
    int choice;
    
    printf("=== PHARMACY QUEUEING SYSTEM ===\n");
    printf("Priority customers are always served first!\n\n");
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Enter Regular Queue\n");
        printf("2. Enter Priority Queue\n");
        printf("3. Call Next Customer\n");
        printf("4. Display All Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                enterRegularQueue(regularQueue, &queueNumber);
                break;
                
            case 2:
                enterPriorityQueue(priorityQueue, &queueNumber);
                break;
                
            case 3:
                callNextCustomer(regularQueue, priorityQueue);
                break;
                
            case 4:
                displayQueues(regularQueue, priorityQueue);
                break;
                
            case 5:
                printf("Exiting program. Goodbye!\n");
                free(regularQueue);
                free(priorityQueue);
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// GUIDE QUESTION 2: Code for entering the regular queue
void enterRegularQueue(Queue* regularQ, int* queueNumber) {
    if (isFull(regularQ)) {
        printf("Regular queue is full! Cannot add more customers.\n");
        return;
    }
    
    enqueue(regularQ, *queueNumber);
    printf("Customer added to Regular Queue with Queue Number: %d\n", *queueNumber);
    (*queueNumber)++;  // Increment for next customer
}

// GUIDE QUESTION 3: Code for entering the priority queue
void enterPriorityQueue(Queue* priorityQ, int* queueNumber) {
    if (isFull(priorityQ)) {
        printf("Priority queue is full! Cannot add more customers.\n");
        return;
    }
    
    enqueue(priorityQ, *queueNumber);
    printf("Customer added to Priority Queue with Queue Number: %d\n", *queueNumber);
    (*queueNumber)++;  // Increment for next customer
}

// GUIDE QUESTION 4: Code for calling the next customer
void callNextCustomer(Queue* regularQ, Queue* priorityQ) {
    int customerNumber;
    
    // Check priority queue first
    if (!isEmpty(priorityQ)) {
        customerNumber = dequeue(priorityQ);
        printf("Calling Customer #%d from PRIORITY QUEUE to the counter.\n", customerNumber);
    }
    // If priority queue is empty, check regular queue
    else if (!isEmpty(regularQ)) {
        customerNumber = dequeue(regularQ);
        printf("Calling Customer #%d from REGULAR QUEUE to the counter.\n", customerNumber);
    }
    // Both queues are empty
    else {
        printf("No customers in queue!\n");
    }
}

// Display both queues
void displayQueues(Queue* regularQ, Queue* priorityQ) {
    printf("\n=== PHARMACY QUEUE STATUS ===\n");
    
    printf("Priority Queue (Customers: %d): ", priorityQ->count);
    if (isEmpty(priorityQ)) {
        printf("Empty\n");
    } else {
        display(priorityQ);
    }
    
    printf("Regular Queue (Customers: %d): ", regularQ->count);
    if (isEmpty(regularQ)) {
        printf("Empty\n");
    } else {
        display(regularQ);
    }
    
    printf("==============================\n");
}
