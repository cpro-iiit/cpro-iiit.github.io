#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_MEMBERS 100
#define MAX_FRIENDS 10

#include <stdlib.h>




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

void print_list(LinkedList l) {
    if(l != NULL) {
        print_person(l->data);
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

typedef struct SocialNet {
	//Person members[MAX_MEMBERS];
    LinkedList members;
	int size;
} SocialNet;


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


int main() {
	// SocialNet s = {
	// 	.members = {
	// 		{ "Ramu", 19, Single, .friends_size = 0},
	// 		{ "Ammu", 21, Engaged, .friends_size = 0},
	// 		{ "Vinod", 24, Married, .friends_size = 0}
	// 	},
	// 	.size = 3
	// };

    SocialNet s = { .size = 0 };
    Person A = { "Ramu", 19, Single, .friends_size = 0};
    append(s.members, A);
    Person B = { "Ammu", 21, Engaged, .friends_size = 0};
    append(s.members, B);
    Person C = { "Vinod", 24, Married, .friends_size = 0};
    append(s.members, C);
    
    
	add_friend(element_at(s.members, 0) , element_at(s.members, 1) );
	add_friend(&(s.members[0]) , &(s.members[2]) );
	add_friend(&(s.members[1]) , &(s.members[2]) );
	add_friend(&(s.members[2]) , &(s.members[0]) );
	
	print_socialnet(&s);

	
	return 0;
}


