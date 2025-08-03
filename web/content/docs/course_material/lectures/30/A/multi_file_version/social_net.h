#ifndef SOCIAL_NET_H
#define SOCIAL_NET_H


#include "linked_list.h"

#define MAX_MEMBERS 100




typedef struct SocialNet {
	//Person members[MAX_MEMBERS];
    LinkedList members;
	int size;
} SocialNet;



void print_list(LinkedList l);
void print_person(Person* p);
void print_socialnet(SocialNet *s);
void add_friend(Person* p, Person* f);

#endif SOCIAL_NET_H

