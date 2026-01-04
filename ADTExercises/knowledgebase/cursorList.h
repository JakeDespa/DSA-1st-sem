#ifndef CURSORLIST_H
#define CURSORLIST_H

#include <stdbool.h>

#define MAX_CELLS 20
#define MAX_TITLE 64
#define MAX_CONTENT 255

// Article structure
typedef struct {
    int id;
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
} Article;

// Node in the cursor-based list
typedef struct {
    Article data;
    int next;
} CursorNode;

// Virtual Heap
typedef CursorNode VirtualHeap[MAX_CELLS];

// List structure
typedef struct {
    int head;
    int avail;
} List;

// Function declarations
void initializeVirtualHeap(VirtualHeap VH, List *list);
int allocSpace(VirtualHeap VH, List *list);
void deallocSpace(VirtualHeap VH, List *list, int index);
void insertArticle(VirtualHeap VH, List *list, Article article, int position);
void viewArticles(VirtualHeap VH, List list);
Article* searchArticle(VirtualHeap VH, List list, int id);
bool deleteArticle(VirtualHeap VH, List *list, int id);
void displayArticle(Article *article);

#endif
