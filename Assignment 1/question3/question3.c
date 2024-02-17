#include <stdio.h>
#include <stdlib.h>

// Δομή για τον κόμβο της λίστας
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Αναδρομική συνάρτηση για τον εύρεση του μέγιστου στοιχείου σε συνδεδεμένη λίστα
int findMaxRecursive(Node* head) {
    if (head == NULL) {
        // Αν η λίστα είναι κενή, επιστρέφουμε την ελάχιστη τιμή int
        return INT_MIN;
    } else {
        // Αναδρομική κλήση για το μέγιστο στοιχείο της υπόλοιπης λίστας
        int max = findMaxRecursive(head->next);
        // Επιστροφή του μέγιστου μεταξύ του τρέχοντος στοιχείου και του μέγιστου της υπόλοιπης λίστας
        return (head->data > max) ? head->data : max;
    }
}

// Κύριο πρόγραμμα για δοκιμή
int main() {
    // Δημιουργία της λίστας: 1 -> 3 -> 5 -> 2 -> 4
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 1;

    head->next = (Node*)malloc(sizeof(Node));
    head->next->data = 3;

    head->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->data = 5;

    head->next->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next->data = 2;

    head->next->next->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next->next->data = 4;

    head->next->next->next->next->next = NULL;

    // Κλήση της αναδρομικής συνάρτησης για τον εύρεση του μέγιστου στοιχείου
    int max = findMaxRecursive(head);

    // Εκτύπωση του μέγιστου στοιχείου
    printf("Max element in the linked list is: %d\n", max);

    // Αποδέσμευση μνήμης
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
