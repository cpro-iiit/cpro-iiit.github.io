
#include <stdio.h>

#include "social_net.h"



void print_list(LinkedList l) {
    if(l != NULL) {
        print_person(&(l->data));
        print_list(l->next);
    } else {
        printf("\n");
    }
}

void print_person(Person* p) {
	char status_string[4][30] = {
		{ "Not Mentioned"},
		{ "Single" },
		{ "Engaged"},
		{ "Married" }
	};
	printf("%s\t%d\t%s\t\t\t", p->name, p->age, status_string[p->status]);
	for (int i =0; i < p->friends_size; i++) {
		printf("%s,", (p->friends[i])->name);
	}
	printf("\n");
}	

void print_socialnet(SocialNet *s) {
	printf("------------------------------\n");
	printf("Name\tAge\tRelationship Status\tFriends\n");
	printf("------------------------------\n");
	for (int i = 0; i < s->size; i++ ) {
		// HomeWork: change the code to print all the names of friends of the person in 4th column
		print_person(&(s->members[i]));
	}
	printf("------------------------------\n");
}

void add_friend(Person* p, Person* f) {
	p->friends[p->friends_size] = f;
	p->friends_size += 1;
}



