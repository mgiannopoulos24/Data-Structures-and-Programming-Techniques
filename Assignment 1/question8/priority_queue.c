#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

// Δομή για τον κόμβο της προτεραιότητας ουράς
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// Δομή για την προτεραιότητα ουράς
struct PriorityQueue {
    Node* front;
};

// Συνάρτηση για δημιουργία νέου κόμβου
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

// Συνάρτηση για δημιουργία νέας προτεραιότητας ουράς
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

// Συνάρτηση για εισαγωγή στοιχείου στην προτεραιότητα ουρά
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

// Συνάρτηση για αφαίρεση και επιστροφή του στοιχείου με τη μεγαλύτερη προτεραιότητα από την προτεραιότητα ουρά
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

// Συνάρτηση για επιστροφή του στοιχείου με τη μεγαλύτερη προτεραιότητα από την προτεραιότητα ουρά χωρίς αφαίρεση
int peek(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        exit(EXIT_FAILURE);
    }
    return pq->front->data;
}

// Συνάρτηση για έλεγχο αν η προτεραιότητα ουρά είναι άδεια
int isEmpty(PriorityQueue* pq) {
    return pq->front == NULL;
}

// Συνάρτηση για εκκαθάριση όλων των στοιχείων από την προτεραιότητα ουρά
void clear(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
}

// Συνάρτηση για καταστροφή της προτεραιότητας ουράς και απελευθέρωση της δεσμευμένης μνήμης
void destroyPriorityQueue(PriorityQueue* pq) {
    clear(pq);
    free(pq);
}

int main() {
    // Δημιουργία προτεραιότητας ουράς
    PriorityQueue* pq = createPriorityQueue();

    // Εισαγωγή στοιχείων στην προτεραιότητα ουρά με προτεραιότητα (προτεραιότητα = τιμή του στοιχείου)
    enqueue(pq, 5, 5);
    enqueue(pq, 3, 3);
    enqueue(pq, 8, 8);

    // Αφαίρεση στοιχείων από την προτεραιότητα ουρά
    printf("Στοιχεία προτεραιότητας ουράς: ");
    while (!isEmpty(pq)) {
        printf("%d ", dequeue(pq));
    }
    printf("\n");

    // Καταστροφή της προτεραιότητας ουράς
    destroyPriorityQueue(pq);

    return 0;
}