#include <stdio.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L) {
    L.count = 0;
    return L;
    
    
}

List insertPos(List L, int data, int pos) {
    if (pos < 0 || pos > L.count || L.count == MAX) return L;
    int i;
    for (i = L.count; i > pos; i--) 
        L.elem[i] = L.elem[i-1];
    
    L.elem[pos] = data;
    L.count++;
    return L;
}

List deletePos(List L, int pos) {
    if (pos < 0 || pos >= L.count) return L;
    int i;
	for (i = pos; i < L.count-1; i++) {
        L.elem[i] = L.elem[i+1];
    }
    L.count--;
    return L;
}

int locate(List L, int data) {
    int i;
	for (i = 0; i < L.count; i++) {
        if (L.elem[i] == data) return i;
    }
    return -1;
}

List insertSorted(List L, int data) {
    if (L.count == MAX) return L;
    int i;
    for (i = L.count-1; i >= 0 && L.elem[i] > data; i--) {
        L.elem[i+1] = L.elem[i];
    }
    L.elem[i+1] = data;
    L.count++;
    return L;
}

void display(List L) {
    int i;
	for (i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main() {
    List L;
    L = initialize(L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 15, 2);
    display(L);  // 10 15 20

    L = deletePos(L, 2);
    display(L);  // 10 20

    printf("Locate 20: %d\n", locate(L, 20));

    L = insertSorted(L, 18);
    display(L);  // 10 18 20

    return 0;
}
