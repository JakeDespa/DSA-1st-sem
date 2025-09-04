// STRUCT DEFINITIONS (same as above)
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} List;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} List;

// INITIALIZE
List* initialize() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->count = 0;
    return list;
}

// INSERT FIRST
void insertFirst(List* list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

// DELETE START
void deleteStart(List* list) {
    if (list->head != NULL) {
        Node* temp = list->head;
        list->head = temp->next;
        free(temp);
        list->count--;
    }
}

// RETRIEVE
int retrieve(List* list, int index) {
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}
