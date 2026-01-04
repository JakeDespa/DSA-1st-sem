#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cursorList.h"

// Function to generate the next article ID
int generateArticleID(VirtualHeap VH, List list) {
    if (list.head == -1) {
        return 1;  // First article starts with ID 1
    }
    
    int maxID = 0;
    int current = list.head;
    
    while (current != -1) {
        if (VH[current].data.id > maxID) {
            maxID = VH[current].data.id;
        }
        current = VH[current].next;
    }
    
    return maxID + 1;
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    VirtualHeap virtualHeap;
    List knowledgeBase;
    
    // Initialize the virtual heap and list
    initializeVirtualHeap(virtualHeap, &knowledgeBase);
    
    int choice, position, searchID, deleteID;
    Article newArticle;
    
    printf("=== KNOWLEDGE BASE MANAGEMENT SYSTEM ===\n");
    printf("Secure internal documentation system\n");
    printf("Maximum capacity: %d articles\n\n", MAX_CELLS);
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Insert New Article\n");
        printf("2. View List of Articles\n");
        printf("3. Search for an Article\n");
        printf("4. Delete an Article\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                // Insert new article
                printf("\n--- Insert New Article ---\n");
                
                // Auto-generate ID
                newArticle.id = generateArticleID(virtualHeap, knowledgeBase);
                printf("Article ID (auto-generated): %d\n", newArticle.id);
                
                // Get title
                printf("Enter article title: ");
                fgets(newArticle.title, MAX_TITLE, stdin);
                newArticle.title[strcspn(newArticle.title, "\n")] = '\0';  // Remove newline
                
                // Get content
                printf("Enter article content: ");
                fgets(newArticle.content, MAX_CONTENT, stdin);
                newArticle.content[strcspn(newArticle.content, "\n")] = '\0';  // Remove newline
                
                // Get position
                printf("Enter position to insert (-1 for end): ");
                scanf("%d", &position);
                clearInputBuffer();
                
                // Insert the article
                insertArticle(virtualHeap, &knowledgeBase, newArticle, position);
                break;
                
            case 2:
                // View all articles
                viewArticles(virtualHeap, knowledgeBase);
                break;
                
            case 3:
                // Search for an article
                printf("\n--- Search for Article ---\n");
                printf("Enter article ID: ");
                scanf("%d", &searchID);
                clearInputBuffer();
                
                Article* foundArticle = searchArticle(virtualHeap, knowledgeBase, searchID);
                displayArticle(foundArticle);
                break;
                
            case 4:
                // Delete an article
                printf("\n--- Delete Article ---\n");
                printf("Enter article ID to delete: ");
                scanf("%d", &deleteID);
                clearInputBuffer();
                
                if (deleteArticle(virtualHeap, &knowledgeBase, deleteID)) {
                    printf("Article with ID %d deleted successfully.\n", deleteID);
                } else {
                    printf("Article with ID %d not found.\n", deleteID);
                }
                break;
                
            case 5:
                printf("Exiting Knowledge Base System. Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
