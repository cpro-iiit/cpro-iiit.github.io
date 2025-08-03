#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node* LinkedList;

void print_list(LinkedList l) {
    if (l != NULL) {
        printf("%d\t", l->data);
        print_list(l->next);
    } else {
        printf("\n");
    }
}

int size_list(LinkedList l) {
    // if (l == NULL) {
    //     return 0;
    // } else {
    //     return 1 + size_list(l->next);
    // }
    return l==NULL? 0 : 1 + size_list(l->next);
}

int element_at(LinkedList l, int pos) {
    if (l != NULL) {
        if (pos == 0) {
            return l->data;
        } else {
            return element_at(l->next, pos - 1);
        }
    }
}



LinkedList append(LinkedList l, int data) {
    Node* n = (Node *) malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    if (l == NULL) {
        l=n;
        return l;
        //return n;
    } else {
        LinkedList i = l;
        while (i->next != NULL) {
            i = i->next;
        }
        i->next = n;
        return l;
    }
}

int main() {
    LinkedList l = NULL; // corresponds to a empty list
    Node A = { 1, NULL};
    l = &A; // list of size 1
    Node B = { 2, NULL};
    A.next = &B;
    l = &A ; // list of size 2
    print_list(l);

    return 0;
}