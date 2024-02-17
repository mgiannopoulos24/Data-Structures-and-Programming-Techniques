#include <stdio.h>
#include <stdlib.h>

// Δομή για τον κόμβο της λίστας
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Δομή για τη διπλά συνδεδεμένη λίστα
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Συνάρτηση για δημιουργία μιας κενής λίστας
DoublyLinkedList* create() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Συνάρτηση για επιστροφή του αριθμού των στοιχείων της λίστας
int size(DoublyLinkedList* list) {
    return list->size;
}

// Συνάρτηση για έλεγχο αν η λίστα είναι κενή
int isEmpty(DoublyLinkedList* list) {
    return list->size == 0;
}

// Συνάρτηση για επιστροφή του πρώτου κόμβου της λίστας
Node* getFirst(DoublyLinkedList* list) {
    return list->head;
}

// Συνάρτηση για επιστροφή του τελευταίου κόμβου της λίστας
Node* getLast(DoublyLinkedList* list) {
    return list->tail;
}

// Συνάρτηση για επιστροφή του προηγούμενου κόμβου ενός δοσμένου κόμβου
Node* getPrev(Node* node) {
    return node->prev;
}

// Συνάρτηση για επιστροφή του επόμενου κόμβου ενός δοσμένου κόμβου
Node* getNext(Node* node) {
    return node->next;
}

// Συνάρτηση για εισαγωγή νέου κόμβου πριν από έναν δοσμένο κόμβο
void addBefore(DoublyLinkedList* list, Node* v, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = v->prev;
    newNode->next = v;
    if (v->prev != NULL)
        v->prev->next = newNode;
    else
        list->head = newNode;
    v->prev = newNode;
    list->size++;
}

// Συνάρτηση για εισαγωγή νέου κόμβου μετά από έναν δοσμένο κόμβο
void addAfter(DoublyLinkedList* list, Node* v, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = v;
    newNode->next = v->next;
    if (v->next != NULL)
        v->next->prev = newNode;
    else
        list->tail = newNode;
    v->next = newNode;
    list->size++;
}

// Συνάρτηση για εισαγωγή νέου κόμβου στην αρχή της λίστας
void addFirst(DoublyLinkedList* list, int data) {
    if (isEmpty(list)) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->size++;
    } else {
        addBefore(list, list->head, data);
    }
}

// Συνάρτηση για εισαγωγή νέου κόμβου στο τέλος της λίστας
void addLast(DoublyLinkedList* list, int data) {
    if (isEmpty(list)) {
        addFirst(list, data);
    } else {
        addAfter(list, list->tail, data);
    }
}

// Συνάρτηση για αφαίρεση κόμβου από τη λίστα
void removeNode(DoublyLinkedList* list, Node* node) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    free(node);
    list->size--;
}

// Συνάρτηση για εκτύπωση των στοιχείων της λίστας
void printList(DoublyLinkedList* list){
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    DoublyLinkedList* list = create();

    addFirst(list, 10);
    addLast(list, 20);
    addLast(list, 30);
    addFirst(list, 5);

    printf("List: ");
    printList(list); // Αναμένεται έξοδος: 5 10 20 30

    printf("Size: %d\n", size(list)); // Αναμένεται έξοδος: 4

    Node* firstNode = getFirst(list);
    Node* lastNode = getLast(list);
    printf("First node: %d\n", firstNode->data); // Αναμένεται έξοδος: 5
    printf("Last node: %d\n", lastNode->data); // Αναμένεται έξοδος: 30

    printf("Removing first node...\n");
    removeNode(list, firstNode);
    printf("List after removal: ");
    printList(list); // Αναμένεται έξοδος: 10 20 30

    printf("Size after removal: %d\n", size(list)); // Αναμένεται έξοδος: 3

    // Αποδέσμευση μνήμης
    while (!isEmpty(list)) {
        removeNode(list, list->head);
    }
    free(list);

    return 0;
}