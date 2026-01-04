#ifndef CLOSEDHASH_H
#define CLOSEDHASH_H

#include <stdbool.h>

#define PRIMARY_SIZE 10
#define SECONDARY_SIZE 10
#define TOTAL_SIZE 20
#define CODE_LENGTH 4

// Node in the cursor-based hash table
typedef struct {
    char code[CODE_LENGTH];
    int next;
} HashNode;

// Virtual Heap
typedef HashNode VirtualHeap[TOTAL_SIZE];

// Dictionary structure
typedef struct {
    int avail;
} Dictionary;

// Function declarations
void initializeVirtualHeap(VirtualHeap VH, Dictionary *dict);
int hashFunction(char *code);
int allocSpace(VirtualHeap VH, Dictionary *dict);
void deallocSpace(VirtualHeap VH, Dictionary *dict, int index);
bool insert(VirtualHeap VH, Dictionary *dict, char *code);
int search(VirtualHeap VH, char *code);
void displayVirtualHeap(VirtualHeap VH);
void displayHashIndices(VirtualHeap VH, char codes[][CODE_LENGTH], int count);

#endif
