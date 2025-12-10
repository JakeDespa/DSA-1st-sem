/*
 * Variation 1: Cursor Based List using Virtual Heap
 * A VHeap simulates system memory using an array where indices are "addresses"
 * Multiple Lists can share one VHeap
 * Array indices DO NOT determine element order in the list
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX 4

// Cell structure with elem and next (next is an index, not a pointer)
typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

// VHeap structure with HeapSpace array and avail index
typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

// List is represented as an integer (index to the first cell)
typedef int List;

// Initialize the virtual heap
void initialize(VHeap *V) {
    int i;
    
    // Set avail to the beginning of list (index 0)
    V->avail = 0;
    
    // Traverse and create a chain linking all cells
    for (i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1;
    }
    
    // Set last cell's next to -1
    V->H[MAX - 1].next = -1;
    
    printf("VHeap initialized with %d cells\n", MAX);
}

// Allocate space from the virtual heap
int allocSpace(VHeap* V) {
    // Check if there is an available cell
    if (V->avail == -1) {
        printf("No space available in VHeap!\n");
        return -1;
    }
    
    // Get the index of the first available cell
    int index = V->avail;
    
    // Update avail to the next available cell
    V->avail = V->H[V->avail].next;
    
    return index;
}

// Deallocate space back to the virtual heap
void deallocSpace(VHeap* V, int index) {
    if (index < 0 || index >= MAX) {
        return;
    }
    
    // Set the next of deallocated cell to current avail
    V->H[index].next = V->avail;
    
    // Update avail to point to newly deallocated cell
    V->avail = index;
}

// Insert element at the beginning of the list
void insertFirst(List* L, VHeap* V, int elem) {
    // Allocate a new cell
    int newIndex = allocSpace(V);
    
    // Check if allocation was successful
    if (newIndex == -1) {
        printf("Cannot insert %d - heap full\n", elem);
        return;
    }
    
    // Set the element of the new cell
    V->H[newIndex].elem = elem;
    
    // Set next of new cell to current list head
    V->H[newIndex].next = *L;
    
    // Update list head to point to new cell
    *L = newIndex;
    
    printf("Inserted %d at first position (index %d)\n", elem, newIndex);
}

// Insert element at the end of the list
void insertLast(List* L, VHeap* V, int elem) {
    // Allocate a new cell
    int newIndex = allocSpace(V);
    
    // Check if allocation was successful
    if (newIndex == -1) {
        printf("Cannot insert %d - heap full\n", elem);
        return;
    }
    
    // Set the element of the new cell
    V->H[newIndex].elem = elem;
    
    // Set next of new cell to -1
    V->H[newIndex].next = -1;
    
    // If list is empty, new cell becomes the head
    if (*L == -1) {
        *L = newIndex;
    } else {
        // Use a pointer to traverse to the last cell
        int trav = *L;
        while (V->H[trav].next != -1) {
            trav = V->H[trav].next;
        }
        
        // Update next of last cell to new cell
        V->H[trav].next = newIndex;
    }
    
    printf("Inserted %d at last position (index %d)\n", elem, newIndex);
}

// Insert element at a specific position
void insertPos(List* L, VHeap* V, int elem, int pos) {
    // Allocate a new cell
    int newIndex = allocSpace(V);
    
    // Check if allocation was successful
    if (newIndex == -1) {
        printf("Cannot insert %d - heap full\n", elem);
        return;
    }
    
    // Set the element of the new cell
    V->H[newIndex].elem = elem;
    
    // Special case: insert at position 0
    if (pos == 0) {
        V->H[newIndex].next = *L;
        *L = newIndex;
        printf("Inserted %d at position %d (index %d)\n", elem, pos, newIndex);
        return;
    }
    
    // Use a pointer to traverse the list
    int trav = *L;
    int i;
    
    // Traverse to the cell before the insertion point
    for (i = 0; i < pos - 1 && trav != -1; i++) {
        trav = V->H[trav].next;
    }
    
    if (trav == -1) {
        printf("Position %d out of bounds\n", pos);
        deallocSpace(V, newIndex);
        return;
    }
    
    // Link the new cell into the list
    V->H[newIndex].next = V->H[trav].next;
    V->H[trav].next = newIndex;
    
    printf("Inserted %d at position %d (index %d)\n", elem, pos, newIndex);
}

// Insert element in sorted order (ascending)
void insertSorted(List* L, VHeap* V, int elem) {
    // Allocate a new cell
    int newIndex = allocSpace(V);
    
    // Check if allocation was successful
    if (newIndex == -1) {
        printf("Cannot insert %d - heap full\n", elem);
        return;
    }
    
    // Set the element of the new cell
    V->H[newIndex].elem = elem;
    
    // Special case: empty list or insert at beginning
    if (*L == -1 || V->H[*L].elem >= elem) {
        V->H[newIndex].next = *L;
        *L = newIndex;
        printf("Inserted %d in sorted position (index %d)\n", elem, newIndex);
        return;
    }
    
    // Use a pointer to traverse the list
    int trav = *L;
    
    // Traverse until correct sorted position
    while (V->H[trav].next != -1 && V->H[V->H[trav].next].elem < elem) {
        trav = V->H[trav].next;
    }
    
    // Link the new cell into the list at correct position
    V->H[newIndex].next = V->H[trav].next;
    V->H[trav].next = newIndex;
    
    printf("Inserted %d in sorted position (index %d)\n", elem, newIndex);
}

// Delete first occurrence of an element
void delete(List* L, VHeap* V, int elem) {
    if (*L == -1) {
        printf("List is empty, cannot delete %d\n", elem);
        return;
    }
    
    // Special case: element is at head
    if (V->H[*L].elem == elem) {
        int temp = *L;
        *L = V->H[*L].next;
        deallocSpace(V, temp);
        printf("Deleted %d from list\n", elem);
        return;
    }
    
    // Use pointer to traverse to cell with element to delete
    int trav = *L;
    while (V->H[trav].next != -1 && V->H[V->H[trav].next].elem != elem) {
        trav = V->H[trav].next;
    }
    
    // Element not found
    if (V->H[trav].next == -1) {
        printf("Element %d not found in list\n", elem);
        return;
    }
    
    // Update previous cell's next to point to current cell's next
    int temp = V->H[trav].next;
    V->H[trav].next = V->H[temp].next;
    
    // Deallocate current cell
    deallocSpace(V, temp);
    
    printf("Deleted %d from list\n", elem);
}

// Delete all occurrences of an element
void deleteAllOccurrence(List* L, VHeap* V, int elem) {
    if (*L == -1) {
        printf("List is empty, cannot delete %d\n", elem);
        return;
    }
    
    int count = 0;
    
    // Handle deletions at the head
    while (*L != -1 && V->H[*L].elem == elem) {
        int temp = *L;
        *L = V->H[*L].next;
        deallocSpace(V, temp);
        count++;
    }
    
    // Traverse the list
    int trav = *L;
    while (trav != -1 && V->H[trav].next != -1) {
        // If next node contains element to delete
        if (V->H[V->H[trav].next].elem == elem) {
            // Unlink the node
            int temp = V->H[trav].next;
            V->H[trav].next = V->H[temp].next;
            
            // Deallocate the removed cell
            deallocSpace(V, temp);
            count++;
        } else {
            // Continue to traverse
            trav = V->H[trav].next;
        }
    }
    
    printf("Deleted %d occurrence(s) of %d\n", count, elem);
}

// Display the list
void display(List L, VHeap V) {
    if (L == -1) {
        printf("List is empty\n");
        return;
    }
    
    printf("List contents: ");
    int trav = L;
    
    // Print all cell values in order until next is -1
    while (trav != -1) {
        printf("%d", V.H[trav].elem);
        if (V.H[trav].next != -1) {
            printf(" -> ");
        }
        trav = V.H[trav].next;
    }
    printf("\n");
}

// Display the entire VHeap structure (for debugging)
void displayVHeap(VHeap V) {
    printf("\n=== VHeap Structure ===\n");
    printf("avail = %d\n", V.avail);
    printf("Index | elem | next\n");
    printf("------|------|-----\n");
    for (int i = 0; i < MAX; i++) {
        printf("  %d   |  %2d  |  %2d\n", i, V.H[i].elem, V.H[i].next);
    }
    printf("=====================\n\n");
}

// Main function to demonstrate cursor-based list operations
int main() {
    VHeap V;
    List L = -1;  // Initialize list as empty
    
    printf("=== Cursor Based List - Variation 1 ===\n\n");
    
    // Initialize VHeap
    initialize(&V);
    displayVHeap(V);
    
    // Test insertFirst
    printf("--- Testing insertFirst ---\n");
    insertFirst(&L, &V, 1);
    insertFirst(&L, &V, 2);
    insertFirst(&L, &V, 3);
    display(L, V);
    displayVHeap(V);
    
    // Test insertLast
    printf("--- Testing insertLast ---\n");
    List L2 = -1;
    insertLast(&L2, &V, 10);
    display(L2, V);
    displayVHeap(V);
    
    printf("VHeap is full now, trying to insert more...\n");
    insertLast(&L2, &V, 20);  // Should fail - heap full
    
    // Test delete
    printf("\n--- Testing delete ---\n");
    delete(&L, &V, 2);
    display(L, V);
    displayVHeap(V);
    
    // Now we have space again
    printf("--- Now we have space, inserting more ---\n");
    insertLast(&L2, &V, 20);
    display(L2, V);
    displayVHeap(V);
    
    // Test insertPos
    printf("\n--- Testing insertPos ---\n");
    insertPos(&L, &V, 5, 1);
    display(L, V);
    displayVHeap(V);
    
    // Clean up and test insertSorted
    printf("\n--- Testing insertSorted ---\n");
    List L3 = -1;
    
    // Delete all from L to free space
    while (L != -1) {
        int elem = V.H[L].elem;
        delete(&L, &V, elem);
    }
    
    // Delete all from L2 to free space
    while (L2 != -1) {
        int elem = V.H[L2].elem;
        delete(&L2, &V, elem);
    }
    
    insertSorted(&L3, &V, 3);
    insertSorted(&L3, &V, 1);
    insertSorted(&L3, &V, 5);
    insertSorted(&L3, &V, 2);
    display(L3, V);
    displayVHeap(V);
    
    // Test deleteAllOccurrence
    printf("\n--- Testing deleteAllOccurrence ---\n");
    insertFirst(&L3, &V, 2);  // Add duplicate
    display(L3, V);
    deleteAllOccurrence(&L3, &V, 2);
    display(L3, V);
    displayVHeap(V);
    
    return 0;
}
