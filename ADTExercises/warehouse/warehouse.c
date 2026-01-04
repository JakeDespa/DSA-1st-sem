#include <stdio.h>
#include <stdlib.h>
#include "arrayStack.h"

#define NUM_STACKS 3

// Function prototypes for main operations
void addContainer(Stack stacks[], int containerID);
void removeContainer(Stack stacks[]);
void searchContainer(Stack stacks[], int containerID);
void displayAllStacks(Stack stacks[]);

int main() {
    // GUIDE QUESTION 1: Create and initialize the three stacks (using an array!)
    Stack stacks[NUM_STACKS];
    
    for (int i = 0; i < NUM_STACKS; i++) {
        initialize(&stacks[i]);
    }
    
    int choice, containerID;
    
    printf("=== WAREHOUSE INVENTORY MANAGEMENT SYSTEM ===\n");
    printf("Each stack can hold a maximum of %d containers.\n\n", MAX);
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Add Container\n");
        printf("2. Remove Container\n");
        printf("3. Search Container\n");
        printf("4. Display All Stacks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter Container ID to add: ");
                scanf("%d", &containerID);
                addContainer(stacks, containerID);
                break;
                
            case 2:
                removeContainer(stacks);
                break;
                
            case 3:
                printf("Enter Container ID to search: ");
                scanf("%d", &containerID);
                searchContainer(stacks, containerID);
                break;
                
            case 4:
                displayAllStacks(stacks);
                break;
                
            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// GUIDE QUESTION 2: Code for adding a container to the next available stack
void addContainer(Stack stacks[], int containerID) {
    int stackIndex = -1;
    
    // Find the next available stack
    for (int i = 0; i < NUM_STACKS; i++) {
        if (!isFull(&stacks[i])) {
            stackIndex = i;
            break;
        }
    }
    
    // Check if all stacks are full
    if (stackIndex == -1) {
        printf("All stacks are full! Cannot add container %d.\n", containerID);
        return;
    }
    
    // Push the container to the available stack
    push(&stacks[stackIndex], containerID);
    printf("Container %d added to Stack %d successfully.\n", containerID, stackIndex + 1);
}

// GUIDE QUESTION 3: Code for removing a container from the latest stack
void removeContainer(Stack stacks[]) {
    int stackIndex = -1;
    
    // Find the latest stack that has containers (search from last to first)
    for (int i = NUM_STACKS - 1; i >= 0; i--) {
        if (!isEmpty(&stacks[i])) {
            stackIndex = i;
            break;
        }
    }
    
    // Check if all stacks are empty
    if (stackIndex == -1) {
        printf("All stacks are empty! Cannot remove container.\n");
        return;
    }
    
    // Pop the container from the latest stack
    int removedContainer = pop(&stacks[stackIndex]);
    printf("Container %d removed from Stack %d successfully.\n", removedContainer, stackIndex + 1);
}

// GUIDE QUESTION 4: Code for checking if a container exists
void searchContainer(Stack stacks[], int containerID) {
    bool found = false;
    
    // Search through all stacks
    for (int i = 0; i < NUM_STACKS; i++) {
        // Search through each element in the current stack
        for (int j = 0; j <= stacks[i].top; j++) {
            if (stacks[i].data[j] == containerID) {
                printf("Container %d found in Stack %d at position %d (from bottom).\n", 
                       containerID, i + 1, j + 1);
                found = true;
                break;
            }
        }
        if (found) break;
    }
    
    if (!found) {
        printf("Container %d not found in any stack.\n", containerID);
    }
}

// Display all stacks
void displayAllStacks(Stack stacks[]) {
    printf("\n=== WAREHOUSE INVENTORY STATUS ===\n");
    for (int i = 0; i < NUM_STACKS; i++) {
        printf("Stack %d (Capacity: %d/%d): ", i + 1, stacks[i].top + 1, MAX);
        if (isEmpty(&stacks[i])) {
            printf("Empty\n");
        } else {
            display(&stacks[i]);
        }
    }
    printf("===================================\n");
}
