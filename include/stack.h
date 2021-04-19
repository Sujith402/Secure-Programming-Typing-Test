#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Stack {
    struct Node* tail;
};

struct Stack* init_stack ();
struct Node* create_node (int data, struct Node* prev);
void push (struct Stack* st, int data);
int pop (struct Stack* st);
