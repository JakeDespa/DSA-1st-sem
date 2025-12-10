/*
 * Variation 3: Bit Vector Set using Boolean/enum Array
 * Uses array where index represents element and value (true/false) represents membership
 * Less space-efficient but simpler to understand
 */

#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 8

// Set is just an array of booleans (or integers)
typedef bool Set[ARRAY_SIZE];

// Initialize set to empty (all false)
void initialize(Set set) {
    // Iterate through every index from 0 to ARRAY_SIZE-1
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Set value at each index to false
        set[i] = false;
    }
}

// Insert element into set
void insert(Set set, int element) {
    // Safety check: ensure element index is within array range
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0-%d]\n", element, ARRAY_SIZE - 1);
        return;
    }
    
    // Use 'element' value as array index
    // Set value at that index to true
    set[element] = true;
}

// Delete element from set
void delete(Set set, int element) {
    // Safety check: ensure element index is within array range
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0-%d]\n", element, ARRAY_SIZE - 1);
        return;
    }
    
    // Use 'element' value as array index
    // Set value at that index to false
    set[element] = false;
}

// Find if element exists in set
bool find(Set set, int element) {
    // Safety check: ensure element index is within array range
    if (element < 0 || element >= ARRAY_SIZE) {
        return false;
    }
    
    // Access array index corresponding to element
    // Value at that index (true/false) directly indicates presence
    return set[element];
}

// Union of two sets (A OR B) - result stored in C
void setUnion(Set A, Set B, Set C) {
    // Iterate through every possible element index
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Resulting set element is true if present in A OR B
        C[i] = A[i] || B[i];
    }
}

// Intersection of two sets (A AND B) - result stored in C
void intersection(Set A, Set B, Set C) {
    // Iterate through every possible element index
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Resulting set element is true if present in A AND B
        C[i] = A[i] && B[i];
    }
}

// Difference of two sets (A - B) - result stored in C
void difference(Set A, Set B, Set C) {
    // Iterate through every possible element index
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Resulting set element is true ONLY if present in A AND NOT in B
        C[i] = A[i] && !B[i];
    }
}

// Display set elements
void display(Set set) {
    printf("{");
    bool first = true;
    
    // Iterate and list elements that are TRUE
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (set[i]) {
            if (!first) {
                printf(", ");
            }
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

// Helper function to display set with array representation
void displayFull(Set set, const char* label) {
    printf("%s = [", label);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", set[i] ? 1 : 0);
        if (i < ARRAY_SIZE - 1) {
            printf(",");
        }
    }
    printf("] ");
    display(set);
    printf("\n");
}

// Main function to demonstrate bit vector set operations
int main() {
    Set A, B, C;
    
    printf("=== Bit Vector Set - Variation 3 (Boolean/enum Array) ===\n");
    printf("Using bool array[%d] - elements 0-%d\n\n", ARRAY_SIZE, ARRAY_SIZE - 1);
    
    // Initialize and insert
    printf("--- Initialize and Insert ---\n");
    initialize(A);
    displayFull(A, "A");
    
    printf("\ninsert(A, 0);\n");
    insert(A, 0);
    displayFull(A, "A");
    
    printf("\ninsert(A, 2);\n");
    insert(A, 2);
    displayFull(A, "A");
    
    printf("\ninsert(A, 7);\n");
    insert(A, 7);
    displayFull(A, "A");
    printf("Final set: ");
    display(A);
    printf("\n");
    
    // Test delete
    printf("\n--- Delete Operations ---\n");
    displayFull(A, "A");
    
    printf("\ndelete(A, 0);\n");
    delete(A, 0);
    displayFull(A, "A");
    
    printf("\ndelete(A, 7);\n");
    delete(A, 7);
    displayFull(A, "A");
    printf("Final set: ");
    display(A);
    printf("\n");
    
    // Set up for set operations
    printf("\n--- Set Operations ---\n");
    initialize(A);
    insert(A, 0);
    insert(A, 2);
    insert(A, 7);
    displayFull(A, "A");
    
    initialize(B);
    insert(B, 2);
    insert(B, 4);
    insert(B, 5);
    displayFull(B, "B");
    
    // Union
    printf("\nunion(A, B, C);\n");
    setUnion(A, B, C);
    displayFull(C, "C");
    
    // Intersection
    printf("\nintersection(A, B, C);\n");
    intersection(A, B, C);
    displayFull(C, "C");
    
    // Difference
    printf("\ndifference(A, B, C);\n");
    difference(A, B, C);
    displayFull(C, "C");
    
    // Test find
    printf("\n--- Find Operation ---\n");
    initialize(A);
    insert(A, 1);
    insert(A, 3);
    insert(A, 6);
    insert(A, 7);
    displayFull(A, "A");
    
    printf("\nfind(A, 3) = %s\n", find(A, 3) ? "true" : "false");
    printf("find(A, 5) = %s\n", find(A, 5) ? "true" : "false");
    
    // Memory comparison
    printf("\n--- Memory Information ---\n");
    printf("sizeof(Set) = %zu bytes (1 byte per element)\n", sizeof(Set));
    printf("Compare to Variation 1 (bitmask): 1 byte for all elements\n");
    printf("This variation uses %dx more space\n", (int)(sizeof(Set) / sizeof(unsigned char)));
    
    return 0;
}
