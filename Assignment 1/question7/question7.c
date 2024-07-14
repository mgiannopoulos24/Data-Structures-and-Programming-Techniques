#include <stdio.h>
#include <stdlib.h>

// Δομή για τον κόμβο της λίστας
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Συνάρτηση για τη δημιουργία νέου κόμβου
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Αποτυχία εκχώρησης μνήμης.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Συνάρτηση για εισαγωγή κόμβου στην αρχή της λίστας
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Συνάρτηση για εκτύπωση της λίστας
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Συνάρτηση για ταξινόμηση με εισαγωγή (insertion sort) στη λίστα
void insertionSort(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Η λίστα είναι ήδη ταξινομημένη ή περιέχει μόνο ένα στοιχείο
    }

    Node* sorted = NULL; // Αρχικοποίηση της ταξινομημένης λίστας
    Node* current = *head;

    while (current != NULL) {
        Node* next = current->next; // Κρατάμε τον επόμενο κόμβο
        Node* prev = NULL; // Αρχικοποίηση δείκτη προηγούμενου

        // Βρίσκουμε τη θέση για εισαγωγή του τρέχοντος κόμβου στην ταξινομημένη λίστα
        while (sorted != NULL && sorted->data < current->data) {
            prev = sorted;
            sorted = sorted->next;
        }

        // Εισαγωγή του τρέχοντος κόμβου στην ταξινομημένη λίστα
        if (prev == NULL) {
            current->next = sorted;
            sorted = current;
        } else {
            prev->next = current;
            current->next = sorted;
        }

        current = next; // Μετακινούμαστε στον επόμενο κόμβο για ταξινόμηση
    }

    *head = sorted; // Ορίζουμε την αρχή της λίστας στην ταξινομημένη λίστα
}

// Συνάρτηση για απελευθέρωση της μνήμης της λίστας
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Συνάρτηση για συγχώνευση και ταξινόμηση δύο λιστών και επιστροφή της νέας ταξινομημένης λίστας
Node* mergeAndSortLists(Node* head1, Node* head2) {
    Node* mergedList = NULL;

    // Συγχώνευση των δύο λιστών σε μια νέα λίστα
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            insertAtBeginning(&mergedList, head1->data);
            head1 = head1->next;
        } else {
            insertAtBeginning(&mergedList, head2->data);
            head2 = head2->next;
        }
    }

    // Αν κάποια λίστα έχει περισσότερα στοιχεία από την άλλη
    while (head1 != NULL) {
        insertAtBeginning(&mergedList, head1->data);
        head1 = head1->next;
    }

    while (head2 != NULL) {
        insertAtBeginning(&mergedList, head2->data);
        head2 = head2->next;
    }

    return mergedList;
}

int main() {
    // Δημιουργία και ταξινόμηση της πρώτης λίστας
    Node* list1 = NULL;
    insertAtBeginning(&list1, 5);
    insertAtBeginning(&list1, 3);
    insertAtBeginning(&list1, 8);
    printf("Αρχική λίστα 1:\n");
    printList(list1);
    insertionSort(&list1);
    printf("Ταξινομημένη λίστα 1:\n");
    printList(list1);

    // Δημιουργία και ταξινόμηση της δεύτερης λίστας
    Node* list2 = NULL;
    insertAtBeginning(&list2, 2);
    insertAtBeginning(&list2, 7);
    insertAtBeginning(&list2, 4);
    printf("\nΑρχική λίστα 2:\n");
    printList(list2);
    insertionSort(&list2);
    printf("Ταξινομημένη λίστα 2:\n");
    printList(list2);

    // Συγχώνευση και ταξινόμηση των δύο ταξινομημένων λιστών
    Node* mergedList = mergeAndSortLists(list1, list2);
    printf("\nΣυγχωνευμένη και ταξινομημένη λίστα:\n");
    printList(mergedList);

    // Απελευθέρωση της μνήμης των λιστών
    freeList(list1);
    freeList(list2);
    freeList(mergedList);

    return 0;
}
