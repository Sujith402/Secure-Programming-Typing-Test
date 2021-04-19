#include "stack.h"

struct Stack* init_stack () {
    struct Stack* temp = (struct Stack*) malloc (sizeof (struct Stack));
    temp->tail = NULL;
    return temp;
}

struct Node* create_node (int data, struct Node* prev) {
    struct Node* temp = (struct Node*) malloc (sizeof (struct Node));
    temp->data = data;
    temp->prev = prev;
    temp->next = NULL;
    return temp;
}

void push (struct Stack* st, int data) {
    if (!st->tail) {
        st->tail = create_node (data, NULL);
    } else {
        st->tail->next = create_node (data, st->tail);
        st->tail = st->tail->next;
    }
}

int pop (struct Stack* st) {
    int retval = -1;
    if (st->tail) {
        retval = st->tail->data;
        st->tail = st->tail->prev;
        if (st->tail) {
            if (st->tail->next) free (st->tail->next);
            st->tail->next = NULL;
        }
    }
    return retval;
}
