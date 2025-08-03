
#include "linked_list.h"



int size_list(LinkedList l) {
    // if (l == NULL) {
    //     return 0;
    // } else {
    //     return 1 + size_list(l->next);
    // }
    return l==NULL? 0 : 1 + size_list(l->next);
}

Person* element_at(LinkedList l, int pos) {
    if (l != NULL) {
        if (pos == 0) {
            return &(l->data);
        } else {
            return element_at(l->next, pos - 1);
        }
    } else {
        return NULL;
    }

}

LinkedList append(LinkedList l, Person data) {
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
