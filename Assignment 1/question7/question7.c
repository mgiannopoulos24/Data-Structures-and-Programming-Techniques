#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to print the list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to perform insertion sort on the list
void insertionSort(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // List is already sorted or contains only one element
    }

    Node* sorted = NULL; // Initialize the sorted list
    Node* current = *head;

    while (current != NULL) {
        Node* next = current->next; // Keep track of the next node
        Node* prev = NULL; // Initialize the previous pointer

        // Find the position to insert the current node in the sorted list
        while (sorted != NULL && sorted->data < current->data) {
            prev = sorted;
            sorted = sorted->next;
        }

        // Insert the current node into the sorted list
        if (prev == NULL) {
            current->next = sorted;
            sorted = current;
        } else {
            prev->next = current;
            current->next = sorted;
        }

        current = next; // Move to the next node for sorting
    }

    *head = sorted; // Set the head of the list to the sorted list
}

// Function to free the memory of the list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to merge and sort two lists and return a new sorted list
Node* mergeAndSortLists(Node* head1, Node* head2) {
    Node* mergedList = NULL;

    // Merge the two lists into a new list
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            insertAtBeginning(&mergedList, head1->data);
            head1 = head1->next;
        } else {
            insertAtBeginning(&mergedList, head2->data);
            head2 = head2->next;
        }
    }

    // If one list has more elements than the other
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
    // Create and sort the first list
    Node* list1 = NULL;
    insertAtBeginning(&list1, 5);
    insertAtBeginning(&list1, 3);
    insertAtBeginning(&list1, 8);
    printf("Original list 1:\n");
    printList(list1);
    insertionSort(&list1);
    printf("Sorted list 1:\n");
    printList(list1);

    // Create and sort the second list
    Node* list2 = NULL;
    insertAtBeginning(&list2, 2);
    insertAtBeginning(&list2, 7);
    insertAtBeginning(&list2, 4);
    printf("\nOriginal list 2:\n");
    printList(list2);
    insertionSort(&list2);
    printf("Sorted list 2:\n");
    printList(list2);

    // Merge and sort the two sorted lists
    Node* mergedList = mergeAndSortLists(list1, list2);
    printf("\nMerged and sorted list:\n");
    printList(mergedList);

    // Free the memory of the lists
    freeList(list1);
    freeList(list2);
    freeList(mergedList);

    return 0;
}
