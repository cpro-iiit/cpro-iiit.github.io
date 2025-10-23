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
  printf("--- list ---\n");
  while (list != NULL) {
    printf("%s\t%d\n", list->data.name, list->data.age);
    list = list->next;
  }
    printf("--- end ---\n");

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

Node* insert(Person p, int pos, Node* l) {
    // TODO
    
    Node* n = malloc(sizeof(Node));
    n->data = p;
    n->next = NULL;
    Node* head = l;
    
    if (pos > 0) {
      int i = pos - 1;
      while (i > 0 && l != NULL) {
        l = l->next;
        i--;
      }
      
      Node* tmp = l->next;
      l->next = n;
      n->next = tmp;
      return head;
    } else {
      n->next = l;
      return n;
    }
    
}

// remove the elment at the position 'pos' in the linked
// list 'l' and return the pointer to the 0th element of
// the modified linked list.
Node* remove_element(int pos, Node* l) {
    Node* head = l;
    if (pos > 0) {
      int i = pos - 1;
      while (i > 0 && l != NULL) {
        l = l->next;
        i--;
      }
      
      Node* tmp = l->next;
      l->next = tmp->next;;
      free(tmp);
    } else {
      head = l->next;
      free(l);
    }
    
    return head;
}



Node* reverse(Node* l) {
    // TODO
    if (l == NULL) return l;

    Node* current_node = l->next;
    Node* previous_node = l;
    previous_node->next = NULL;

    while (current_node != NULL) {
      Node* tmp = current_node->next;
      current_node->next = previous_node;
      previous_node = current_node;
      current_node = tmp;
    }
    return previous_node;

}

Node* concat(Node* l1, Node* l2) {
    // TODO
    if (l1 == NULL) return l2;
    Node* head  = l1;
    while(l1 != NULL && l1->next != NULL) {
      l1 = l1->next;
    }
    l1->next = l2;
    return head;
}

int main() {

  Person A = {"Alice", 22};
  Person B = {"Bob", 26};
  Person C = {"Charlie", 20};
  Person D = { "Diestel", 27 };

  Node* list1 = NULL; //empty list
  list1 = append(list1, &A);
  print_list(list1);
  list1 = insert(B, 0, list1);
  print_list(list1);

  Node* list2 = NULL;
  list2 = append(list2, &C);
  list2 = append(list2, &D);
  print_list(list2);

  Node* full = concat(list1, list2);
  print_list(full);

  Node* rev = reverse(full);
  print_list(rev);


  

  return 0;
}