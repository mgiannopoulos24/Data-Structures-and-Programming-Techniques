#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Δομή για την προτεραιότητα ουράς
typedef struct PriorityQueue PriorityQueue;

// Συναρτήσεις
PriorityQueue* createPriorityQueue();   // Δημιουργία προτεραιότητας ουράς
void enqueue(PriorityQueue* pq, int item, int priority);  // Εισαγωγή στην ουρά
int dequeue(PriorityQueue* pq);  // Αφαίρεση από την ουρά
int peek(PriorityQueue* pq);     // Επιστροφή του πρώτου στοιχείου χωρίς αφαίρεση
int isEmpty(PriorityQueue* pq);  // Έλεγχος αν η ουρά είναι άδεια
void clear(PriorityQueue* pq);   // Εκκαθάριση όλων των στοιχείων
void destroyPriorityQueue(PriorityQueue* pq);   // Καταστροφή της ουράς

#endif /* PRIORITY_QUEUE_H */
