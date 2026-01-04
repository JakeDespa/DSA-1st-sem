#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


int hashFunction(int rgb[3]) {

    int hash = (rgb[0] * 3 + rgb[1] * 5 + rgb[2] * 7) % PALETTE_SIZE;
    return hash;
}


void createDictionary(Dictionary *dict) {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }
}

Node* createNode(Color newColor) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newNode->data.colorName, newColor.colorName);
    newNode->data.RGBVal[0] = newColor.RGBVal[0];
    newNode->data.RGBVal[1] = newColor.RGBVal[1];
    newNode->data.RGBVal[2] = newColor.RGBVal[2];
    newNode->next = NULL;

    return newNode;
}

void insertColor(Dictionary *dict, Color newColor) {
    int hashIndex = hashFunction(newColor.RGBVal);
    Node *newNode = createNode(newColor);

    newNode->next = dict->buckets[hashIndex];
    dict->buckets[hashIndex] = newNode;

    printf("-> Inserted '%s' (RGB: %d, %d, %d) into bucket [%d].\n",
           newColor.colorName,
           newColor.RGBVal[0],
           newColor.RGBVal[1],
           newColor.RGBVal[2],
           hashIndex);
}

Color* searchColor(Dictionary *dict, int rgb[3]) {
    int hashIndex = hashFunction(rgb);
    printf("Searching for RGB (%d, %d, %d) in bucket [%d]...\n",
           rgb[0], rgb[1], rgb[2], hashIndex);

    Node *current = dict->buckets[hashIndex];
    while (current != NULL) {
        if (current->data.RGBVal[0] == rgb[0] &&
            current->data.RGBVal[1] == rgb[1] &&
            current->data.RGBVal[2] == rgb[2]) {
            return &(current->data);
        }
        current = current->next;
    }

    return NULL;
}