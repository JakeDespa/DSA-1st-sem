#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/**
 * @brief Deletes a node with the given key from the BST.
 * @param root The current root of the BST.
 * @param key_data The string key to delete.
 * @return BST The new root of the BST after deletion.
 */
BST deleteNode(BST root, const char *key_data) {
    BST current = root;
    BST parent = NULL;

    // 1. Find the node to delete ('current') and its parent ('parent')
    while (current != NULL && strcmp(current->key, key_data) != 0) {
        parent = current;
        if (strcmp(key_data, current->key) < 0) {
            current = current->LC;
        } else {
            current = current->RC;
        }
    }

    // If key was not found, return root unchanged
    if (current == NULL) {
        printf("Key \"%s\" not found for deletion.\n", key_data);
        return root;
    }

    // 2. Handle Case 3: Node with 2 children
    if (current->LC != NULL && current->RC != NULL) {
        // Find the in-order successor (minimum node in the right subtree)
        BST successor = current->RC;
        BST successorParent = current;

        while (successor->LC != NULL) {
            successorParent = successor;
            successor = successor->LC;
        }

        // Copy successor's key to the current node
        // Note: We assume the node's key buffer is large enough (MAX_KEY_LEN)
        strcpy(current->key, successor->key);

        // Update 'current' and 'parent' to delete the successor node instead
        current = successor;
        parent = successorParent;
    }

    // 3. Case 1 & 2: Node with 0 or 1 child
    BST child;
    if (current->LC != NULL) {
        child = current->LC;
    } else {
        child = current->RC; // Will be NULL if it's a leaf
    }

    // Remove the node from the tree structure
    if (parent == NULL) {
        // We are deleting the root
        root = child;
    } else {
        if (parent->LC == current) {
            parent->LC = child;
        } else {
            parent->RC = child;
        }
    }

    // Free the memory
    if (current->key) {
        free(current->key); // Free the string memory
    }
    free(current); // Free the node memory

    return root;
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Building BST for Deletion Test ---\n");
    // Keys: Apple, Banana, Grape, Kiwi, Mango(ROOT), Orange, Pineapple
    insert(&myTree, "Mango");      // Root
    insert(&myTree, "Apple");      // Left of Mango
    insert(&myTree, "Pineapple");  // Right of Mango
    insert(&myTree, "Banana");     // Right of Apple
    insert(&myTree, "Grape");      // Left of Pineapple
    insert(&myTree, "Orange");     // Right of Grape
    insert(&myTree, "Kiwi");       // Left of Orange

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(myTree);
    printf("\n");

    // --- Deletion Tests ---

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    // Kiwi is a leaf node (0 children)
    myTree = deleteNode(myTree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    // Apple has 1 child (Banana)
    myTree = deleteNode(myTree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango - the Root) ---\n");
    // Mango is replaced by its successor (Orange)
    myTree = deleteNode(myTree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Key (Zebra) ---\n");
    myTree = deleteNode(myTree, "Zebra");
    printf("No change expected: ");
    inorderTraversal(myTree);
    printf("\n");

    // 2. Clean up memory
    destroyTree(myTree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}