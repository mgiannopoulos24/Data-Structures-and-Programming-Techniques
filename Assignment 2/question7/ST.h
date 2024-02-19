#ifndef ST_H
#define ST_H

#include "Item.h"

void STinit();
int STcount();
void STinsert(Item);
Item STsearch(Key);
void STdelete(Item);
Item STselect(int);
void STdeleteAll(Item);
void STsort(void (*visit)(Item));

#endif /* ST_H */
