#include <stdio.h>
#include <stdlib.h>

// Ορισμός της δομής για τον κόμβο της προτεραιότητας
typedef struct PriorityQueueNode {
    int state;       // Τρέχουσα κατάσταση
    int cost;        // Κόστος για την επίτευξη αυτής της κατάστασης
    int heuristic;   // Ευρετική αξιολόγηση
    struct PriorityQueueNode* next;  // Δείκτης προς τον επόμενο κόμβο
} PriorityQueueNode;

typedef struct {
    PriorityQueueNode* front;  // Δομή για την προτεραιότητα
} PriorityQueue;

// Πρωτότυπα συναρτήσεων
PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue* pq, int state, int cost, int heuristic);
int dequeue(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
void clear(PriorityQueue* pq);
void destroyPriorityQueue(PriorityQueue* pq);
int solveCubeProblem(int initial_state, int target_state);

// Υλοποίηση των συναρτήσεων...

int main() {
    int N; // Αριθμός των κύβων
    printf("Εισάγετε τον αριθμό των κύβων: ");
    scanf("%d", &N);

    int initial_state = 0; // Αρχική κατάσταση όπου όλοι οι κύβοι είναι στο τραπέζι
    int target_state = (1 << N) - 1; // Επιθυμητή κατάσταση όπου όλοι οι κύβοι είναι στοίβα

    int moves = solveCubeProblem(initial_state, target_state);

    if (moves == -1) {
        printf("Δεν βρέθηκε λύση.\n");
    } else {
        printf("Ελάχιστες κινήσεις που απαιτούνται για την επίλυση του προβλήματος: %d\n", moves);
    }

    return 0;
}

// Δημιουργία νέας προτεραιότητας
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("Αποτυχία εκχώρησης μνήμης.\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

// Εισαγωγή στοιχείου στην προτεραιότητα
void enqueue(PriorityQueue* pq, int state, int cost, int heuristic) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    if (newNode == NULL) {
        printf("Αποτυχία εκχώρησης μνήμης.\n");
        exit(EXIT_FAILURE);
    }
    newNode->state = state;
    newNode->cost = cost;
    newNode->heuristic = heuristic;
    newNode->next = NULL;

    if (pq->front == NULL || newNode->heuristic < pq->front->heuristic) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        PriorityQueueNode* current = pq->front;
        while (current->next != NULL && current->next->heuristic <= newNode->heuristic) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Αφαίρεση και επιστροφή του στοιχείου με τη μεγαλύτερη προτεραιότητα από την προτεραιότητα
int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Η προτεραιότητα είναι κενή.\n");
        exit(EXIT_FAILURE);
    }
    int state = pq->front->state;
    PriorityQueueNode* temp = pq->front;
    pq->front = pq->front->next;
    free(temp);
    return state;
}

// Έλεγχος εάν η προτεραιότητα είναι κενή
int isEmpty(PriorityQueue* pq) {
    return pq->front == NULL;
}

// Εκκαθάριση όλων των στοιχείων από την προτεραιότητα
void clear(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
}

// Καταστροφή της προτεραιότητας και απελευθέρωση της εκχωρημένης μνήμης
void destroyPriorityQueue(PriorityQueue* pq) {
    clear(pq);
    free(pq);
}

// Λύση του προβλήματος με τους κύβους
int solveCubeProblem(int initial_state, int target_state) {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, initial_state, 0, target_state - initial_state); // Αρχική κατάσταση με ευρετική αξιολόγηση
    int moves = 0;

    while (!isEmpty(pq)) {
        int current_state = dequeue(pq);
        if (current_state == target_state) {
            destroyPriorityQueue(pq);
            return moves;
        }

        // Ανάπτυξη της τρέχουσας κατάστασης και εισαγωγή των επόμενων καταστάσεων στην προτεραιότητα
        for (int i = 0; i < sizeof(int) * 8 - 1; i++) { // Υποθέτουμε 32-bit integer για την αναπαράσταση της κατάστασης
            if ((current_state >> i) & 1) { // Αν ο κύβος i είναι πάνω σε άλλον κύβο
                int next_state = current_state - (1 << i); // Μετακίνηση του κύβου i στο τραπέζι
                enqueue(pq, next_state, moves + 1, target_state - next_state);
            } else { // Αν ο κύβος i είναι στο τραπέζι
                int next_state = current_state + (1 << i); // Μετακίνηση του κύβου i σε άλλον κύβο
                enqueue(pq, next_state, moves + 1, target_state - next_state);
            }
        }
        moves++;
    }

    destroyPriorityQueue(pq);
    return -1; // Δεν βρέθηκε λύση
}
