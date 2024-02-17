#include <stdio.h>
#include <stdlib.h>

// Define the data structure for the priority queue
typedef struct PriorityQueueNode {
    int state;  // Current state
    int cost;   // Cost to reach this state
    int heuristic;  // Heuristic evaluation
    struct PriorityQueueNode* next;
} PriorityQueueNode;

typedef struct {
    PriorityQueueNode* front;
} PriorityQueue;

// Function prototypes
PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue* pq, int state, int cost, int heuristic);
int dequeue(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
void clear(PriorityQueue* pq);
void destroyPriorityQueue(PriorityQueue* pq);
int solveCubeProblem(int initial_state, int target_state);

// Function implementations...

int main() {
    int N; // Number of cubes
    printf("Enter the number of cubes: ");
    scanf("%d", &N);

    int initial_state = 0; // Initial state where all cubes are on the table
    int target_state = (1 << N) - 1; // Target state where all cubes are stacked

    int moves = solveCubeProblem(initial_state, target_state);

    if (moves == -1) {
        printf("No solution found.\n");
    } else {
        printf("Minimum moves required to solve the problem: %d\n", moves);
    }

    return 0;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

void enqueue(PriorityQueue* pq, int state, int cost, int heuristic) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
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

int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    int state = pq->front->state;
    PriorityQueueNode* temp = pq->front;
    pq->front = pq->front->next;
    free(temp);
    return state;
}

int isEmpty(PriorityQueue* pq) {
    return pq->front == NULL;
}

void clear(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
}

void destroyPriorityQueue(PriorityQueue* pq) {
    clear(pq);
    free(pq);
}

int solveCubeProblem(int initial_state, int target_state) {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, initial_state, 0, target_state - initial_state); // Initial state with heuristic evaluation
    int moves = 0;

    while (!isEmpty(pq)) {
        int current_state = dequeue(pq);
        if (current_state == target_state) {
            destroyPriorityQueue(pq);
            return moves;
        }

        // Expand current state and enqueue next states
        for (int i = 0; i < sizeof(int) * 8 - 1; i++) { // Assuming 32-bit integer for state representation
            if ((current_state >> i) & 1) { // If cube i is on another cube
                int next_state = current_state - (1 << i); // Move cube i to the table
                enqueue(pq, next_state, moves + 1, target_state - next_state);
            } else { // If cube i is on the table
                int next_state = current_state + (1 << i); // Move cube i to another cube
                enqueue(pq, next_state, moves + 1, target_state - next_state);
            }
        }
        moves++;
    }

    destroyPriorityQueue(pq);
    return -1; // No solution found
}
