#include <stdio.h>
#include <string.h>
#include "cursorList.h"

// Initialize the virtual heap and list
void initializeVirtualHeap(VirtualHeap VH, List *list) {
    // Initialize the available list (free nodes)
    for (int i = 0; i < MAX_CELLS - 1; i++) {
        VH[i].next = i + 1;
    }
    VH[MAX_CELLS - 1].next = -1;  // End of available list
    
    list->avail = 0;   // Available list starts at index 0
    list->head = -1;   // Data list is empty
}

// Allocate space from the virtual heap
int allocSpace(VirtualHeap VH, List *list) {
    int index = list->avail;
    if (index != -1) {
        list->avail = VH[index].next;
    }
    return index;
}

// Deallocate space and return to available list
void deallocSpace(VirtualHeap VH, List *list, int index) {
    if (index >= 0 && index < MAX_CELLS) {
        VH[index].next = list->avail;
        list->avail = index;
    }
}

// GUIDE QUESTION 1: Function for inserting a new article
void insertArticle(VirtualHeap VH, List *list, Article article, int position) {
    // Allocate space for new article
    int newIndex = allocSpace(VH, list);
    
    if (newIndex == -1) {
        printf("Knowledge base is full! Cannot add more articles.\n");
        return;
    }
    
    // Store the article data
    VH[newIndex].data = article;
    
    // Insert at the beginning (position 0) or empty list
    if (position == 0 || list->head == -1) {
        VH[newIndex].next = list->head;
        list->head = newIndex;
        printf("Article \"%s\" (ID: %d) inserted successfully.\n", article.title, article.id);
        return;
    }
    
    // Insert at the end (position -1)
    if (position == -1) {
        if (list->head == -1) {
            list->head = newIndex;
            VH[newIndex].next = -1;
        } else {
            int current = list->head;
            while (VH[current].next != -1) {
                current = VH[current].next;
            }
            VH[current].next = newIndex;
            VH[newIndex].next = -1;
        }
        printf("Article \"%s\" (ID: %d) inserted at the end successfully.\n", article.title, article.id);
        return;
    }
    
    // Insert at specific position
    int current = list->head;
    int prev = -1;
    int count = 0;
    
    while (current != -1 && count < position) {
        prev = current;
        current = VH[current].next;
        count++;
    }
    
    if (prev != -1) {
        VH[newIndex].next = VH[prev].next;
        VH[prev].next = newIndex;
        printf("Article \"%s\" (ID: %d) inserted at position %d successfully.\n", 
               article.title, article.id, position);
    }
}

// View all articles in the list
void viewArticles(VirtualHeap VH, List list) {
    if (list.head == -1) {
        printf("No articles in the knowledge base.\n");
        return;
    }
    
    printf("\n=== KNOWLEDGE BASE ARTICLES ===\n");
    printf("%-5s | %-60s\n", "ID", "Title");
    printf("------+--------------------------------------------------------------\n");
    
    int current = list.head;
    while (current != -1) {
        printf("%-5d | %-60s\n", VH[current].data.id, VH[current].data.title);
        current = VH[current].next;
    }
    printf("================================\n");
}

// GUIDE QUESTION 2: Function for searching an article
Article* searchArticle(VirtualHeap VH, List list, int id) {
    int current = list.head;
    
    while (current != -1) {
        if (VH[current].data.id == id) {
            return &VH[current].data;
        }
        current = VH[current].next;
    }
    
    return NULL;  // Article not found
}

// GUIDE QUESTION 3: Function for deleting an article
bool deleteArticle(VirtualHeap VH, List *list, int id) {
    if (list->head == -1) {
        return false;  // List is empty
    }
    
    int current = list->head;
    int prev = -1;
    
    // Search for the article
    while (current != -1 && VH[current].data.id != id) {
        prev = current;
        current = VH[current].next;
    }
    
    // Article not found
    if (current == -1) {
        return false;
    }
    
    // Article found, remove it
    if (prev == -1) {
        // Deleting the first node
        list->head = VH[current].next;
    } else {
        // Deleting a middle or last node
        VH[prev].next = VH[current].next;
    }
    
    // Deallocate the space
    deallocSpace(VH, list, current);
    
    return true;
}

// Display a single article's details
void displayArticle(Article *article) {
    if (article != NULL) {
        printf("\n=== ARTICLE DETAILS ===\n");
        printf("ID: %d\n", article->id);
        printf("Title: %s\n", article->title);
        printf("Content:\n%s\n", article->content);
        printf("========================\n");
    } else {
        printf("Article not found!\n");
    }
}
