#include <stdio.h>
#include <stdlib.h>

#define Key int
#define Item int
#define NULLitem -1

typedef struct STnode* link;
struct STnode {
    Item item;
    link l, r;
    int N;
};

static link head, z;

link NEW(Item item, link l, link r, int N) {
    link x = (link)malloc(sizeof(struct STnode));
    x->item = item; 
    x->l = l; 
    x->r = r; 
    x->N = N;
    return x;
}

void STinit() {
    head = (z = NEW(NULLitem, NULL, NULL, 0));
}

Item searchR(link h, Key v) {
    if (h == z) 
        return NULLitem;
    if (v == h->item) 
        return h->item;
    if (v < h->item) 
        return searchR(h->l, v);
    else 
        return searchR(h->r, v);
}

Item STsearch(Key v) {
    return searchR(head, v);
}

link insertR(link h, Item item) {
    if (h == z) 
        return NEW(item, z, z, 1);
    if (item < h->item)
        h->l = insertR(h->l, item);
    else 
        h->r = insertR(h->r, item);
    (h->N)++;
    return h;
}

void STinsert(Item item) {
    head = insertR(head, item);
}

void sortR(link h, void (*visit)(Item)) {
    if (h == z) 
        return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}

void STsort(void (*visit)(Item)) {
    sortR(head, visit);
}

link deleteR(link h, Key v) {
    if (h == z) 
        return z;
    if (v < h->item) 
        h->l = deleteR(h->l, v);
    else if (v > h->item) 
        h->r = deleteR(h->r, v);
    else {
        if (h->l == z) {
            link x = h->r;
            free(h);
            return x;
        }
        if (h->r == z) {
            link x = h->l;
            free(h);
            return x;
        }
        link t = h;
        h = h->r;
        while (h->l != z) 
            h = h->l;
        t->item = h->item;
        h->item = v;
        h->r = deleteR(h->r, v);
    }
    return h;
}

void STdelete(Key v) {
    head = deleteR(head, v);
}

int main() {
    // Example usage
    STinit();
    STinsert(5);
    STinsert(3);
    STinsert(7);
    printf("%d\n", STsearch(3)); // Output: 3
    printf("%d\n", STsearch(6)); // Output: -1 (not found)
    STdelete(3);
    printf("%d\n", STsearch(3)); // Output: -1 (deleted)
    return 0;
}
