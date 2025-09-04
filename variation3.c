#include <stdio.h>
#include <stdlib.h>
#define LENGTH 4   // initial capacity

// Structure definition
typedef struct {
    int *elem;   // pointer to dynamically allocated array
    int count;   // current number of elements
    int max;     // maximum capacity
} List;

// ========== OPERATIONS ==========

// Initialize list
List initialize(List L) {
    L.elem = (int *)malloc(LENGTH * sizeof(int));
    L.count = 0;
    L.max = LENGTH;
    return L;
}

// Resize the array (double capacity)
List resize(List L) {
    int newMax = L.max * 2;
    int *newArr = (int *)malloc(newMax * sizeof(int));

    for (int i = 0; i < L.count; i++) {
        newArr[i] = L.elem[i];
    }

    free(L.elem);
    L.elem = newArr;
    L.max = newMax;

    return L;
}

// Insert at position
List insertPos(List L, int data, int position) {
    if (position < 0 || position > L.count) {
        printf("Invalid position!\n");
        return L;
    }

    if (L.count == L.max) {
        L = resize(L);
    }

    for (int i = L.count; i > position; i--) {
        L.elem[i] = L.elem[i - 1];
    }

    L.elem[position] = data;
    L.count++;
    return L;
}

// Delete at position
List deletePos(List L, int position) {
    if (position < 0 || position >= L.count) {
        printf("Invalid position!\n");
        return L;
    }

    for (int i = position; i < L.count - 1; i++) {
        L.elem[i] = L.elem[i + 1];
    }

    L.count--;
    return L;
}

// Locate element
int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elem[i] == data) return i;
    }
    return -1;
}

// Insert while keeping sorted order
List insertSorted(List L, int data) {
    if (L.count == L.max) {
        L = resize(L);
    }

    int pos = 0;
    while (pos < L.count && L.elem[pos] < data) pos++;

    L = insertPos(L, data, pos);
    return L;
}

// Display
void display(List L) {
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

// Free memory
void makeNULL(List L) {
    free(L.elem);
}

// ========== DEMO ==========
int main() {
    List L;
    L = initialize(L);

    L = insertPos(L, 1, 0);
    L = insertPos(L, 3, 1);
    L = insertPos(L, 2, 1);
    display(L);  // 1 2 3

    L = deletePos(L, 1);
    display(L);  // 1 3

    L = insertSorted(L, 5);
    L = insertSorted(L, 4);
    display(L);  // 1 3 4 5

    int pos = locate(L, 3);
    printf("Element 3 found at position: %d\n", pos);

    makeNULL(L);
    return 0;
}
