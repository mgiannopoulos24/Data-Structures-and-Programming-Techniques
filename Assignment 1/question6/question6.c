#include <stdio.h>
#include <stdlib.h>

// Δήλωση του τύπου δεδομένων για έναν κόμβο της λίστας
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Συνάρτηση για τη δημιουργία ενός νέου κόμβου
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Σφάλμα: Δεν είναι δυνατή η δέσμευση μνήμης\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Συνάρτηση για την εισαγωγή ενός κόμβου σε ταξινομημένη λίστα
Node* insertSorted(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL || data < head->data) {
        newNode->next = head;
        return newNode;
    }
    Node* current = head;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Συνάρτηση για ταξινόμηση μιας απλά συνδεδεμένης λίστας με τον αλγόριθμο εισαγωγής
Node* insertionSort(Node* head) {
    Node* sortedList = NULL;
    Node* current = head;
    while (current != NULL) {
        sortedList = insertSorted(sortedList, current->data);
        current = current->next;
    }
    return sortedList;
}

// Συνάρτηση για τυπώνει τα περιεχόμενα της λίστας
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Κύρια συνάρτηση για τον έλεγχο της λειτουργίας του αλγορίθμου
int main() {
    // Δημιουργία της απλά συνδεδεμένης λίστας
    Node* head = createNode(5);
    head->next = createNode(2);
    head->next->next = createNode(7);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(1);

    printf("Initial List: ");
    printList(head);

    // Ταξινόμηση της λίστας με τον αλγόριθμο εισαγωγής
    head = insertionSort(head);

    printf("Sorted List: ");
    printList(head);

    return 0;
}
