#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

int main() {
    // Κώδικας για αρχικοποίηση και εισαγωγή στοιχείων στο σύμβολο πίνακα
    
    STinsert(10);
    STinsert(5);
    STinsert(15);
    STinsert(10);
    STinsert(20);
    STinsert(10);
    
    printf("Before deletion:\n");
    printf("Count: %d\n", STcount());
    printf("Keys:\n");
    STsort(ITEMshow);
    printf("\n");
    
    // Διαγραφή όλων των στοιχείων με κλειδί 10
    STdeleteAll(10);
    
    printf("\nAfter deletion:\n");
    printf("Count: %d\n", STcount());
    printf("Keys:\n");
    STsort(ITEMshow);
    
    return 0;
}
