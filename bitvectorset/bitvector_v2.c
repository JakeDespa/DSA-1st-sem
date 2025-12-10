/*
 * Variation 2: Bit Vector Set using Bit Fields
 * Bit fields allow compiler to pack structure members into small number of bits
 * The struct itself holds the bit set
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_BITS 8

// Set structure using bit field
// 'field : 8' defines 'field' to be exactly 8 bits wide
typedef struct {
    unsigned int field : 8;  // 8-bit field to hold set elements 0-7
} Set;

// Initialize set to empty (field = 0)
void initialize(Set *set) {
    // Access the 'field' member via pointer and set to 0
    set->field = 0;
}

// Insert element into set by setting corresponding bit
void insert(Set *set, int element) {
    // Safety check: ensure element index is within bit range
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS - 1);
        return;
    }
    
    // Create the bitmask for element's position
    unsigned int mask = 1 << element;
    
    // Use Bitwise OR to set the corresponding bit within 'field'
    set->field |= mask;
}

// Delete element from set by clearing corresponding bit
void delete(Set *set, int element) {
    // Safety check: ensure element index is within bit range
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS - 1);
        return;
    }
    
    // Create the mask and invert it
    unsigned int mask = 1 << element;
    mask = ~mask;
    
    // Use Bitwise AND NOT to clear the corresponding bit in field
    set->field &= mask;
}

// Find if element exists in set
bool find(Set set, int element) {
    // Safety check
    if (element < 0 || element >= MAX_BITS) {
        return false;
    }
    
    // Create a mask
    unsigned int mask = 1 << element;
    
    // Use Bitwise AND to check status of corresponding bit in field
    return (set.field & mask) != 0;
}

// Union of two sets (A OR B)
Set setUnion(Set A, Set B) {
    Set result;
    // Union is achieved by Bitwise OR operation
    result.field = A.field | B.field;
    return result;
}

// Intersection of two sets (A AND B)
Set intersection(Set A, Set B) {
    Set result;
    // Intersection is achieved by Bitwise AND operation
    result.field = A.field & B.field;
    return result;
}

// Difference of two sets (A - B)
Set difference(Set A, Set B) {
    Set result;
    // Difference is achieved by A AND (NOT B)
    result.field = A.field & (~B.field);
    return result;
}

// Display set elements
void display(Set set) {
    printf("{");
    bool first = true;
    
    // Iterate through all possible elements (0 to 7)
    for (int i = 0; i < MAX_BITS; i++) {
        // Check if bit corresponding to element i is set
        if (find(set, i)) {
            // If present, print the element
            if (!first) {
                printf(", ");
            }
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

// Helper function to display set with all representations
void displayFull(Set set, const char* label) {
    printf("%s.field = %d ", label, set.field);
    display(set);
    printf(" (");
    // Print binary representation
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (set.field >> i) & 1);
    }
    printf(")\n");
}

// Main function to demonstrate bit vector set operations
int main() {
    Set A, B, C;
    
    printf("=== Bit Vector Set - Variation 2 (Bit Fields) ===\n");
    printf("Using struct with 8-bit field - elements 0-7\n\n");
    
    // Initialize and insert
    printf("--- Initialize and Insert ---\n");
    initialize(&A);
    displayFull(A, "A");
    
    printf("\ninsert(&A, 0);\n");
    insert(&A, 0);
    displayFull(A, "A");
    
    printf("\ninsert(&A, 4);\n");
    insert(&A, 4);
    displayFull(A, "A");
    
    printf("\ninsert(&A, 5);\n");
    insert(&A, 5);
    displayFull(A, "A");
    printf("Final set: ");
    display(A);
    printf("\n");
    
    // Test delete
    printf("\n--- Delete Operations ---\n");
    displayFull(A, "A");
    
    printf("\ndelete(&A, 5);\n");
    delete(&A, 5);
    displayFull(A, "A");
    
    printf("\ndelete(&A, 4);\n");
    delete(&A, 4);
    displayFull(A, "A");
    printf("Final set: ");
    display(A);
    printf("\n");
    
    // Set up for set operations
    printf("\n--- Set Operations ---\n");
    initialize(&A);
    insert(&A, 0);
    insert(&A, 4);
    insert(&A, 5);
    displayFull(A, "A");
    
    initialize(&B);
    insert(&B, 2);
    insert(&B, 5);
    displayFull(B, "B");
    
    // Union
    printf("\nC = union(A, B);\n");
    C = setUnion(A, B);
    displayFull(C, "C");
    
    // Intersection
    printf("\nC = intersection(A, B);\n");
    C = intersection(A, B);
    displayFull(C, "C");
    
    // Difference
    printf("\nC = difference(A, B);\n");
    C = difference(A, B);
    displayFull(C, "C");
    
    // Test find
    printf("\n--- Find Operation ---\n");
    initialize(&A);
    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 6);
    insert(&A, 7);
    displayFull(A, "A");
    
    printf("\nfind(A, 3) = %s\n", find(A, 3) ? "true" : "false");
    printf("find(A, 2) = %s\n", find(A, 2) ? "true" : "false");
    
    // Demonstrate struct size
    printf("\n--- Memory Information ---\n");
    printf("sizeof(Set) = %zu byte(s)\n", sizeof(Set));
    printf("sizeof(unsigned int) = %zu byte(s)\n", sizeof(unsigned int));
    
    return 0;
}
