// pq.c
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/**
 * Initialize the priority queue structure.
 * Also prints the initialization message to match your test output.
 */
void initQueue(PriorityQueue *pq) {
    if (!pq) return;
    pq->size = 0;
    pq->capacity = MAX_PROCESSES;
    printf("\n--- Scheduler Queue initialized with capacity %d. ---\n", pq->capacity);
}

/**
 * Swap two Process entries (by value).
 */
void swap(Process *a, Process *b) {
    Process tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Heapify down (sift-down) from index to restore Max-Heap property.
 * 0-based indexing.
 */
void heapifyDown(PriorityQueue *pq, int index) {
    if (!pq) return;

    while (1) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < pq->size && pq->heap[left].priority > pq->heap[largest].priority) {
            largest = left;
        }
        if (right < pq->size && pq->heap[right].priority > pq->heap[largest].priority) {
            largest = right;
        }

        if (largest != index) {
            swap(&pq->heap[index], &pq->heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

/**
 * Insert a new process into the priority queue.
 * Maintains Max-Heap by sifting up the newly inserted element.
 * Prints an enqueue message (to match your test output).
 */
void insertProcess(PriorityQueue *pq, Process newProcess) {
    if (!pq) return;

    if (pq->size >= pq->capacity) {
        printf("ENQUEUE FAILED: Queue is full (capacity %d).\n", pq->capacity);
        return;
    }

    // Place at the end
    int idx = pq->size;
    pq->heap[idx] = newProcess;
    pq->size++;

    // Sift up to restore Max-Heap property
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (pq->heap[parent].priority < pq->heap[idx].priority) {
            swap(&pq->heap[parent], &pq->heap[idx]);
            idx = parent;
        } else {
            break;
        }
    }

    // Print the enqueue log to match sample output
    printf("-> ENQUEUED: Process ID %d (Priority: %d)\n", newProcess.pid, newProcess.priority);
}

/**
 * Extract the process with the highest priority (root of the Max-Heap).
 * Returns a dummy process with pid = -1 if queue is empty.
 */
Process extractMax(PriorityQueue *pq) {
    Process dummy = {.pid = -1, .priority = -1};

    if (!pq) return dummy;

    if (pq->size == 0) {
        // Empty queue
        return dummy;
    }

    // Root is the max
    Process root = pq->heap[0];

    // Replace root with last element and shrink
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    // Restore heap property by sifting down
    if (pq->size > 0) {
        heapifyDown(pq, 0);
    }

    return root;
}