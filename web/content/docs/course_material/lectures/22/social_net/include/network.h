#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100
#define FILENAME "network.txt"

// ===== STRUCTS =====
typedef struct Person {
    char name[30];
    struct Person** friends;
    int num_friends;
} Person;

typedef struct Network {
    Person* people[MAX_PEOPLE];
    int num_people;
} Network;

// ===== NETWORK OPERATIONS =====
Network* create_network();
void free_network(Network* net);
Person* create_person(const char* name);
void add_person(Network* net, const char* name);
Person* find_person(Network* net, const char* name);
void print_network(Network* net);
void print_person_friends(Person* p);

// ===== FILE I/O =====
void save_network(Network* net);
void load_network(Network* net);

// ===== FRIENDS OF FRIENDS =====
void find_fof_recursive(Network* net, Person* p, Person* origin, int current_depth, int max_depth, int* visited);

#endif
