#include <stdio.h>
#include <stdlib.h>
#define LENGTH 4

// Structure definition
typedef struct {
    int *elem;
    int count;
    int max;
} List;

// ========== OPERATIONS ==========

// Initialize list
void initialize(List *L) {
    L->elem = (int *)malloc(LENGTH * sizeof(int));
    L->count = 0;
    L->max = LENGTH;
}

// Resize array
void resize(List *L) {
    int newMax = L->max * 2;
    int *newArr = (int *)malloc(newMax * sizeof(int));

    for (int i = 0; i < L->count; i++) {
        newArr[i] = L->elem[i];
    }

    free(L->elem);
    L->elem = newArr;
    L->max = newMax;
}

// Insert at position
void insertPos(List *L, int data, int position) {
    if (position < 0 || position > L->count) {
        printf("Invalid position!\n");
        return;
    }

    if (L->count == L->max) {
        resize(L);
    }

    for (int i = L->count; i > position; i--) {
        L->elem[i] = L->elem[i - 1];
    }

    L->elem[position] = data;
    L->count++;
}

// Delete at position
void deletePos(List *L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return;
    }

    for (int i = position; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }

    L->count--;
}

// Locate element
int locate(List *L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elem[i] == data) return i;
    }
    return -1;
}

// Retrieve element
int retrieve(List *L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return -1;
    }
    return L->elem[position];
}

// Insert sorted
void insertSorted(List *L, int data) {
    if (L->count == L->max) {
        resize(L);
    }

    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) pos++;

    insertPos(L, data, pos);
}

// Display
void display(List *L) {
    for (int i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// Free memory
void makeNULL(List *L) {
    free(L->elem);
    L->elem = NULL;
    L->count = 0;
    L->max = 0;
}

// ========== DEMO ==========
int main() {
    List L;
    initialize(&L);

    insertPos(&L, 1, 0);
    insertPos(&L, 3, 1);
    insertPos(&L, 2, 1);
    display(&L);  // 1 2 3

    deletePos(&L, 1);
    display(&L);  // 1 3

    insertSorted(&L, 5);
    insertSorted(&L, 4);
    display(&L);  // 1 3 4 5

    int pos = locate(&L, 3);
    printf("Element 3 found at position: %d\n", pos);

    printf("Element at position 2: %d\n", retrieve(&L, 2));

    makeNULL(&L);
    return 0;
}
