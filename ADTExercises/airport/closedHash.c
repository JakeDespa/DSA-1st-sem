#include <stdio.h>
#include <string.h>
#include "closedHash.h"

// Initialize the virtual heap and dictionary
void initializeVirtualHeap(VirtualHeap VH, Dictionary *dict) {
    // Initialize primary area (0-9) - all empty (next = -1)
    for (int i = 0; i < PRIMARY_SIZE; i++) {
        strcpy(VH[i].code, "");
        VH[i].next = -1;
    }
    
    // Initialize secondary area (10-19) as available list
    for (int i = PRIMARY_SIZE; i < TOTAL_SIZE - 1; i++) {
        strcpy(VH[i].code, "");
        VH[i].next = i + 1;
    }
    VH[TOTAL_SIZE - 1].code[0] = '\0';
    VH[TOTAL_SIZE - 1].next = -1;
    
    dict->avail = PRIMARY_SIZE;  // Avail starts at index 10
}

// Hash function: ((code[0] - 'A') * 26 * 26 + (code[1] - 'A') * 26 + (code[2] - 'A')) % 10
int hashFunction(char *code) {
    if (code == NULL || strlen(code) < 3) {
        return -1;
    }
    
    int hash = ((code[0] - 'A') * 26 * 26 + 
                (code[1] - 'A') * 26 + 
                (code[2] - 'A')) % PRIMARY_SIZE;
    
    return hash;
}

// Allocate space from the secondary area (progressive overflow)
int allocSpace(VirtualHeap VH, Dictionary *dict) {
    int index = dict->avail;
    if (index != -1 && index >= PRIMARY_SIZE) {
        dict->avail = VH[index].next;
    }
    return index;
}

// Deallocate space and return to available list
void deallocSpace(VirtualHeap VH, Dictionary *dict, int index) {
    if (index >= PRIMARY_SIZE && index < TOTAL_SIZE) {
        strcpy(VH[index].code, "");
        VH[index].next = dict->avail;
        dict->avail = index;
    }
}

// Insert a code into the hash table using progressive overflow
bool insert(VirtualHeap VH, Dictionary *dict, char *code) {
    int hashIndex = hashFunction(code);
    
    if (hashIndex == -1) {
        printf("Invalid code format!\n");
        return false;
    }
    
    // Case 1: Primary slot is empty
    if (strlen(VH[hashIndex].code) == 0) {
        strcpy(VH[hashIndex].code, code);
        VH[hashIndex].next = -1;
        return true;
    }
    
    // Case 2: Collision - need to use progressive overflow
    // Find the last node in the chain
    int current = hashIndex;
    while (VH[current].next != -1) {
        current = VH[current].next;
    }
    
    // Allocate space from secondary area
    int newIndex = allocSpace(VH, dict);
    
    if (newIndex == -1) {
        printf("Hash table is full! Cannot insert %s\n", code);
        return false;
    }
    
    // Link the new node to the chain
    strcpy(VH[newIndex].code, code);
    VH[newIndex].next = -1;
    VH[current].next = newIndex;
    
    return true;
}

// Search for a code in the hash table
int search(VirtualHeap VH, char *code) {
    int hashIndex = hashFunction(code);
    
    if (hashIndex == -1) {
        return -1;
    }
    
    // Search through the chain
    int current = hashIndex;
    while (current != -1) {
        if (strcmp(VH[current].code, code) == 0) {
            return current;
        }
        current = VH[current].next;
    }
    
    return -1;  // Not found
}

// Display the final state of the virtual heap
void displayVirtualHeap(VirtualHeap VH) {
    printf("\n=== FINAL STATE OF VIRTUAL HEAP ===\n\n");
    
    printf("PRIMARY AREA (Indices 0-9):\n");
    printf("%-6s | %-10s | %-6s\n", "Index", "Code", "Next");
    printf("-------|------------|--------\n");
    for (int i = 0; i < PRIMARY_SIZE; i++) {
        printf("%-6d | %-10s | ", i, strlen(VH[i].code) > 0 ? VH[i].code : "EMPTY");
        if (VH[i].next == -1) {
            printf("NULL\n");
        } else {
            printf("%d\n", VH[i].next);
        }
    }
    
    printf("\nSECONDARY AREA (Indices 10-19):\n");
    printf("%-6s | %-10s | %-6s\n", "Index", "Code", "Next");
    printf("-------|------------|--------\n");
    for (int i = PRIMARY_SIZE; i < TOTAL_SIZE; i++) {
        printf("%-6d | %-10s | ", i, strlen(VH[i].code) > 0 ? VH[i].code : "EMPTY");
        if (VH[i].next == -1) {
            printf("NULL\n");
        } else {
            printf("%d\n", VH[i].next);
        }
    }
    
    printf("\n====================================\n");
}

// Display hash indices for each code
void displayHashIndices(VirtualHeap VH, char codes[][CODE_LENGTH], int count) {
    printf("\n=== HASH INDICES FOR EACH CODE ===\n\n");
    printf("%-10s | %-12s | %-15s\n", "Code", "Hash Index", "Actual Index");
    printf("-----------|--------------|----------------\n");
    
    for (int i = 0; i < count; i++) {
        int hashIndex = hashFunction(codes[i]);
        int actualIndex = search(VH, codes[i]);
        
        printf("%-10s | %-12d | %-15d\n", codes[i], hashIndex, actualIndex);
    }
    
    printf("\n===================================\n");
}
