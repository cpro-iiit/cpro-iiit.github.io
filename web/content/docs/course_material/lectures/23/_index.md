---
title: "L23: Linked Lists"
bookHidden: true
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# Linked Lists

---

## Problem: Large Arrays!
```c
#define MAX_MEMBERS 100

Person members[MAX_MEMBERS];
```

---
## Linked List: A array that grows according to needs


---

## Linked List: Code
```c
typedef struct Node {
    Person data;
    struct Node* next;
} Node;


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

Node* list = &first;



```
[Pythontutor](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0Atypedef%20struct%20Person%20%7B%0A%20%20char%20name%5B10%5D%3B%0A%20%20int%20age%3B%0A%20%20struct%20Person*%20friends%5B3%5D%3B%0A%7D%20Person%3B%0A%0Atypedef%20struct%20Node%20%7B%0A%20%20Person%20data%3B%0A%20%20struct%20Node*%20next%3B%0A%7D%20Node%3B%0A%0Avoid%20print_list%28Node*%20list%29%20%7B%0A%20%20while%20%28list%20!%3D%20NULL%29%20%7B%0A%20%20%20%20printf%28%22%25s%5Ct%25d%5Cn%22,%20list-%3Edata.name,%20list-%3Edata.age%29%3B%0A%20%20%20%20list%20%3D%20list-%3Enext%3B%0A%20%20%7D%0A%7D%0A%0A%0Aint%20main%28%29%20%7B%0A%0A%20%20Node%20third%20%3D%20%7B%0A%20%20%20%20%7B%22Alice%22,%2022%7D,%0A%20%20%20%20NULL%0A%20%20%7D%3B%0A%20%20%0A%20%20Node%20second%20%3D%20%7B%0A%20%20%20%20%7B%22Bob%22,%2026%7D,%0A%20%20%20%20%26third%0A%20%20%7D%3B%0A%20%20%0A%20%20Node%20first%20%3D%20%7B%0A%20%20%20%20%7B%22Charlie%22,%2020%7D,%0A%20%20%20%20%26second%0A%20%20%7D%3B%0A%20%20%0A%20%20print_list%28%26first%29%3B%0A%0A%20%20return%200%3B%0A%7D&cumulative=false&curInstr=18&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)
---
## Size of a Liniked List
```c
int size(Node* l) {
    int s = 0;
    while (l != NULL) {
        l = l->next;
        s ++;
    }
    return s;
}
```
### A recursive solution
```c
int size(Node* l) {
    return l==NULL? 0: size(l->next) + 1;
}
```
---
## Printing elements of a linked list

```c
void print_list(Node* l) {
    while (l != NULL) {
        printf("%s\t\t%d\n",l->data.name, l->data.age);
        l = l->next;   
    }
}
```
---

## Find the element at the ith position
```c
Person* element_at(int pos, Node* l) {
    int s = 0;
    while (l != NULL) {
        if (s == pos) return &(l->data);
        l = l->next;
        s ++;
    }
    return NULL;
}
```
### A recursive solution
```c
Person* element_at_recursive(int pos, Node* l) {
    // TODO
    if (l==NULL) return NULL;
    if (pos == 0)   {return &(l->data);}
    else { return element_at(pos-1, l->next); }
    
    // return pos == 0 ? &(l->data): element_at(pos-1, l->next);
}
```
---
## Append element to end of the list
```c
Node* append(Person p, Node* l) {
    // Node D = {{"Raj", 18}, NULL}; Local Variable! Will not work.
    Node* D = (Node *) malloc(sizeof(Node));
    D->data = p;
    D->next = NULL;
    if (l == NULL) return D; // if l is empty just return D.
    Node* i = l;
    while (i->next != NULL) {
        i = i->next;
    }
    i->next = D;
    return l;
}
```
---
## Full code
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
  char name[10];
  int age;
  struct Person* friends[3];
} Person;

typedef struct Node {
  Person data;
  struct Node* next;
} Node;

void print_list(Node* list) {
  while (list != NULL) {
    printf("%s\t%d\n", list->data.name, list->data.age);
    list = list->next;
  }
}

int size(Node* list) {
 // return number of elements in the list 
// int s = 0;
//   while (list != NULL) {
//     s++;
//     list = list->next;
//   }
// return s;
  return list == NULL? 0: 1+ size(list->next);
}

Person* element_at(Node* list, int pos) {
  // return the element at the 'pos' position of the linked list
  int s = 0;
  while (list != NULL) {
    if (s == pos) return &(list->data);
    s++;
    list = list->next;
  }
  return NULL;
  // return pos == 0? &(list->data) : element_at(list->next, pos-1);
}

Node* append(Node* list, Person* data) {
  // add new person data as the last element in the list
  // and return the pointer to the first element in the list.
  
  Node* new_element = malloc(sizeof(Node));
  new_element->data = *data;
  new_element->next = NULL;

  if (list != NULL) {
    Node* head = list;
    while (list->next != NULL) {
      list = list->next;
    }
    list->next = new_element;
    return head;
  } else return new_element;
  
}


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
  
  print_list(&first);
  int s = size(&first);
  printf("size of list is %d.\n", s);
  for (int i = 0; i < s; i++) {
    Node* s = element_at(&first, i);
    printf("%dth element is %s.\n", i, s->data.name);
  }
  
  Person new_person = { "Diestel", 27 };
  Node* list = append(&first, &new_person);
  print_list(&first);
  s = size(&first);
  printf("size of list is %d.\n", s);
  for (int i = 0; i < s; i++) {
    Node* s = element_at(&first, i);
    printf("%dth element is %s.\n", i, s->data.name);
  }

  return 0;
}
```
---
## HW: Insert element at a position in the list
```c
LinkedList insert(Person p, int pos, LinkedList l) {
    // TODO
}
```

---
## HW: Concatenate 2 lists
```c
LinkedList concat(LinkedList l1, LinkedList l2) {
    // TODO
}
```


---
## HW: Reverse a list
```c
LinkedList reverse(LinkedList l) {
    // TODO
}
```