#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>


#define MAX_NAME_LEN 100
#define MAX_FRIENDS 10


typedef enum RelStatus {
	NotMentioned,
	Single,
	Engaged,
	Married
} RelStatus;


typedef struct Person {
	char name[MAX_NAME_LEN];
	int age;
	RelStatus status;
	struct Person* friends[MAX_FRIENDS];
	int friends_size;
} Person;

typedef struct Node {
    Person data;
    struct Node* next;
} Node;

typedef Node* LinkedList;

int size_list(LinkedList l);
Person* element_at(LinkedList l, int pos);
LinkedList append(LinkedList l, Person data);

#endif LINKED_LIST_H