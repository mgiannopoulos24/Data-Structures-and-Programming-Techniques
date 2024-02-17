// priority_queue.c

#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

// Node structure for the priority queue
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// Priority queue structure
struct PriorityQueue {
    Node* front;
};

// Function to create a new node
Node* createNode(int item, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = item;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

// Function to insert an element into the priority queue
void enqueue(PriorityQueue* pq, int item, int priority) {
    Node* newNode = createNode(item, priority);
    if (pq->front == NULL || priority > pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        Node* current = pq->front;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the element with the highest priority from the priority queue
int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        exit(EXIT_FAILURE);
    }
    Node* temp = pq->front;
    int item = temp->data;
    pq->front = pq->front->next;
    free(temp);
    return item;
}

// Function to return the element with the highest priority from the priority queue without removing it
int peek(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        exit(EXIT_FAILURE);
    }
    return pq->front->data;
}

// Function to check if the priority queue is empty
int isEmpty(PriorityQueue* pq) {
    return pq->front == NULL;
}

// Function to clear all elements from the priority queue
void clear(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
}

// Function to destroy the priority queue and free allocated memory
void destroyPriorityQueue(PriorityQueue* pq) {
    clear(pq);
    free(pq);
}


int main() {
    // Create a priority queue
    PriorityQueue* pq = createPriorityQueue();

    // Insert elements into the priority queue with priority (priority = value of the element)
    enqueue(pq, 5, 5);
    enqueue(pq, 3, 3);
    enqueue(pq, 8, 8);

    // Dequeue elements from the priority queue
    printf("Priority Queue elements: ");
    while (!isEmpty(pq)) {
        printf("%d ", dequeue(pq));
    }
    printf("\n");

    // Destroy the priority queue
    destroyPriorityQueue(pq);

    return 0;
}
