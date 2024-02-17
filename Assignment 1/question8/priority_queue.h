#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Define the data type for the priority queue
typedef struct PriorityQueue PriorityQueue;

// Function prototypes
PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue* pq, int item, int priority);
int dequeue(PriorityQueue* pq);
int peek(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
void clear(PriorityQueue* pq);
void destroyPriorityQueue(PriorityQueue* pq);

#endif /* PRIORITY_QUEUE_H */
