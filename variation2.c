#include <stdio.h>
#include <stdlib.h>
#define MAX 100   // maximum size of static array

// Structure definition
typedef struct {
    int elem[MAX];  // array elements
    int count;      // current number of elements
} List, *EPtr;

// ========== OPERATIONS ==========

// Initialize the list
void initialize(EPtr L) {
    L->count = 0;
}

// Insert element at given position
void insertPos(EPtr L, int data, int position) {
    if (position < 0 || position > L->count) {
        printf("Invalid position!\n");
        return;
    }
    if (L->count == MAX) {
        printf("List is full!\n");
        return;
    }

    // Shift elements to the right
    for (int i = L->count; i > position; i--) {
        L->elem[i] = L->elem[i - 1];
    }

    L->elem[position] = data;
    L->count++;
}

// Delete element at given position
void deletePos(EPtr L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return;
    }

    // Shift elements to the left
    for (int i = position; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }

    L->count--;
}

// Locate an element (returns index or -1)
int locate(EPtr L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elem[i] == data) {
            return i;
        }
    }
    return -1;
}

// Retrieve element at position
int retrieve(EPtr L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return -1;  // error value
    }
    return L->elem[position];
}

// Insert while keeping the list sorted
void insertSorted(EPtr L, int data) {
    if (L->count == MAX) {
        printf("List is full!\n");
        return;
    }

    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) {
        pos++;
    }
    insertPos(L, data, pos);
}

// Display the list
void display(EPtr L) {
    for (int i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// Free the memory (not needed for static array, but included for ADT consistency)
void makeNULL(EPtr L) {
    L->count = 0;
}

// ========== DEMO PROGRAM ==========
int main() {
    List myList;
    EPtr L = &myList;

    initialize(L);

    insertPos(L, 1, 0);
    insertPos(L, 3, 1);
    insertPos(L, 2, 1);
    display(L);   // 1 2 3

    deletePos(L, 1);
    display(L);   // 1 3

    insertSorted(L, 5);
    insertSorted(L, 4);
    display(L);   // 1 3 4 5

    int pos = locate(L, 3);
    printf("Element 3 found at position: %d\n", pos);

    printf("Element at position 2: %d\n", retrieve(L, 2));

    makeNULL(L);
    display(L);   // (empty)

    return 0;
}
