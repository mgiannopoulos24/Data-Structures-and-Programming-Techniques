#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

typedef struct STnode* link;
struct STnode { Item item; link l, r; int N };

static link head, z;

link NEW(Item item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->N = N;
    return x;
}

void STinit() {
    head = (z = NEW(NULLitem, NULL, NULL, 0));
}

int STcount() {
    return head->N;
}

Item searchR(link h, Key v) {
    Key t = key(h->item);
    if (h == z) return NULLitem;
    if eq(v, t) return h->item;
    if (less(v, t)) return searchR(h->l, v);
    else return searchR(h->r, v);
}

Item STsearch(Key v) {
    return searchR(head, v);
}

link insertR(link h, Item item) {
    Key v = key(item), t = key(h->item);
    if (h == z) return NEW(item, z, z, 1);
    if (less(v, t))
        h->l = insertR(h->l, item);
    else h->r = insertR(h->r, item);
    (h->N)++;
    return h;
}

void STinsert(Item item) {
    head = insertR(head, item);
}

void sortR(link h, void (*visit)(Item)) {
    if (h == z) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}

void STsort(void (*visit)(Item)) {
    sortR(head, visit);
}

link rotR(link h) {
    link x = h->l; h->l = x->r; x->r = h;
    return x;
}

link rotL(link h) {
    link x = h->r; h->r = x->l; x->l = h;
    return x;
}

link insertT(link h, Item item) {
    Key v = key(item);
    if (h == z) return NEW(item, z, z, 1);
    if (less(v, key(h->item))) {
        h->l = insertT(h->l, item);
        h = rotR(h);
    } else {
        h->r = insertT(h->r, item);
        h = rotL(h);
    }
    return h;
}

void STinsert(Item item) {
    head = insertT(head, item);
}

Item selectR(link h, int k) {
    int t = h->l->N;
    if (h == z) return NULLitem;
    if (t > k) return selectR(h->l, k);
    if (t < k) return selectR(h->r, k - t - 1);
    return h->item;
}

Item STselect(int k) {
    return selectR(head, k);
}

link partR(link h, int k) {
    int t = h->l->N;
    if (t > k) {
        h->l = partR(h->l, k);
        h = rotR(h);
    }
    if (t < k) {
        h->r = partR(h->r, k - t - 1);
        h = rotL(h);
    }
    return h;
}

link joinLR(link a, link b) {
    if (b == z) return a;
    b = partR(b, 0);
    b->l = a;
    return b;
}

link deleteR(link h, Key v) {
    link x;
    Key t = key(h->item);
    if (h == z) return z;
    if (less(v, t)) h->l = deleteR(h->l, v);
    if (less(t, v)) h->r = deleteR(h->r, v);
    if (eq(v, t)) {
        x = h;
        h = joinLR(h->l, h->r);
        free(x);
    }
    return h;
}

void STdelete(Key v) {
    head = deleteR(head, v);
}

link STjoin(link a, link b) {
    if (b == z) return a;
    if (a == z) return b;
    
    b = insertR(b, a->item);
    
    b->l = STjoin(a->l, b->l);
    b->r = STjoin(a->r, b->r);
    
    free(a);
    
    return b;
}

void deleteAllR(link h, Key v) {
    if (h == z) return;
    
    deleteAllR(h->l, v);
    deleteAllR(h->r, v);
    
    if (eq(key(h->item), v)) {
        STdelete(h->item);
    }
}

void STdeleteAll(Item item) {
    deleteAllR(head, key(item));
}