#include "stdio.h"
#include "stdlib.h"
#define MAX_NAME_LEN 100

typedef struct Person {
    char name[MAX_NAME_LEN];
    int age;
} Person;

typedef struct Node {
    Person data;
    struct Node* next;
} Node;

typedef Node* LinkedList;

void print_list(LinkedList l) {
    while (l != NULL) {
        printf("%s\t\t%d\n", l->data.name, l->data.age);
        l = l->next;
    }
}

int size(LinkedList l) {
    int s = 0;
    while (l != NULL) {
        l = l->next;
        s ++;
    }
    return s;
}

Person* element_at(int pos, LinkedList l) {
    // TODO
    if (l==NULL) return NULL;
    if (pos == 0)   {return &(l->data);}
    else { return element_at(pos-1, l->next); }
    
    // return pos == 0 ? &(l->data): element_at(pos-1, l->next);
}

// LinkedList append(Person p, LinkedList l) {
//     // TODO
// }

int main() {
    Node third = {
        {"Alice", 22},
        NULL
    };
    Node second = {
        {"Bob", 26},
        &third
    };
    Node first = {
        {"Charlie", 20},
        &second
    };
    Person D = {"Raj", 18};

    LinkedList l = &first;
    printf("Size of the list is %d\n", size(l));
    print_list(l);
    printf("Element at 1st position: %s\n", element_at(1,l)->name);
    printf("Element at 2nd position: %s\n", element_at(2,l)->name);
    // append(D, l);
    // printf("List after appending\n");
    // print_list(l);
    return 0;
}