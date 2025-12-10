/*
 * Variation 1: Bit Vector Set using Computer Word / Bitmask
 * Most common and space-efficient implementation
 * Uses unsigned char (8 bits) - can represent elements 0-7
 * Elements are added by setting corresponding bit using bitwise OR
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_BITS (8 * sizeof(unsigned char))  // 8 bits for unsigned char

// Representation guide:
//  N  = decimal value
// ( ) = Binary value
// { } = Set elements

// Initialize set to empty (all bits 0)
void initialize(unsigned char *set) {
    *set = 0;
}

// Insert element into set by setting corresponding bit
void insert(unsigned char *set, int element) {
    // Safety check: ensure element index is within bit range
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS - 1);
        return;
    }
    
    // Create a bitmask for the element's position (1 << element)
    unsigned char mask = 1 << element;
    
    // Perform Bitwise OR assignment to set the bit
    *set |= mask;
}

// Delete element from set by clearing corresponding bit
void delete(unsigned char *set, int element) {
    // Safety check: ensure element index is within bit range
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS - 1);
        return;
    }
    
    // Create a mask for the element's position
    unsigned char mask = 1 << element;
    
    // Invert the mask (0 at target bit, 1s everywhere else)
    mask = ~mask;
    
    // Perform Bitwise AND assignment to clear the bit
    *set &= mask;
}

// Find if element exists in set
bool find(unsigned char set, int element) {
    // Safety check
    if (element < 0 || element >= MAX_BITS) {
        return false;
    }
    
    // Create a mask for the element's position
    unsigned char mask = 1 << element;
    
    // Use Bitwise AND to check if bit is set
    return (set & mask) != 0;
}

// Union of two sets (A OR B)
unsigned char setUnion(unsigned char A, unsigned char B) {
    // Union is achieved by Bitwise OR operation
    return A | B;
}

// Intersection of two sets (A AND B)
unsigned char intersection(unsigned char A, unsigned char B) {
    // Intersection is achieved by Bitwise AND operation
    return A & B;
}

// Difference of two sets (A - B)
unsigned char difference(unsigned char A, unsigned char B) {
    // Difference is achieved by A AND (NOT B)
    return A & (~B);
}

// Display set elements
void display(unsigned char set) {
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
void displayFull(unsigned char set, const char* label) {
    printf("%s = %d ", label, set);
    display(set);
    printf(" (");
    // Print binary representation
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (set >> i) & 1);
    }
    printf(")\n");
}

// Main function to demonstrate bit vector set operations
int main() {
    unsigned char A, B, C;
    
    printf("=== Bit Vector Set - Variation 1 (Computer Word/Bitmask) ===\n");
    printf("Using unsigned char (8 bits) - elements 0-7\n\n");
    
    // Initialize set A
    printf("--- Initialize and Insert ---\n");
    initialize(&A);
    displayFull(A, "A");
    
    // Insert elements
    printf("\ninsert(&A, 1);\n");
    insert(&A, 1);
    displayFull(A, "A");
    
    printf("\ninsert(&A, 6);\n");
    insert(&A, 6);
    displayFull(A, "A");
    
    // Test delete
    printf("\n--- Delete Operations ---\n");
    printf("delete(&A, 6);\n");
    delete(&A, 6);
    displayFull(A, "A");
    
    printf("\ndelete(&A, 1);\n");
    delete(&A, 1);
    displayFull(A, "A");
    
    // Set up for union/intersection/difference examples
    printf("\n--- Set Operations ---\n");
    initialize(&A);
    insert(&A, 1);
    insert(&A, 6);
    displayFull(A, "A");
    
    initialize(&B);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);
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
    printf("find(A, 5) = %s\n", find(A, 5) ? "true" : "false");
    
    // Test boundary
    printf("\n--- Boundary Test ---\n");
    printf("Attempting to insert element 8 (out of range):\n");
    insert(&A, 8);
    
    return 0;
}
