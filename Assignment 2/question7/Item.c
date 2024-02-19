#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMrand(void) {
    return rand();
}

int ITEMscan(Item *x) {
    return scanf("%d", x);
}

void ITEMshow(Item x) {
    printf("%5d ", x);
}
