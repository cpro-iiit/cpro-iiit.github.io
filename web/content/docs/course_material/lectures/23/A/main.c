#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node* LinkedList;

void print_list(LinkedList l) {
    if(l != NULL) {
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
    } else {
        return -1;
    }

}

LinkedList append(LinkedList l, int data) {
    Node* n = (Node *) malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    if (l == NULL) {
        return n;
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
    LinkedList l = NULL; //empty Linked List
    Node A = { 1, NULL};
    Node B = { 2, NULL};
    l = &A; // l is a size 1
    l->next = &B; // l is a linkedlist of size 2

    print_list(l);
    l = append(l, 3);
    print_list(l);
    printf("%d\n", element_at(l, 1));
    return 0;
}