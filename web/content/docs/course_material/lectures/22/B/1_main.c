#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_FRIENDS 10
#define MAX_MEMBERS 100

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
	struct Person friends[MAX_FRIENDS];
	int friends_size;
} Person;

typedef struct SocialNet {
	Person members[MAX_MEMBERS];
	int size;
} SocialNet;


void print_person(Person* p, SocialNet* s) {
	char status_string[4][30] = {
		{ "Not Mentioned"},
		{ "Single" },
		{ "Engaged"},
		{ "Married" }
	};
	printf("%s\t%d\t%s\t\t", p->name, p->age, status_string[p->status]);
	for (int i = 0; i < p->friends_size; i++) {
		printf("%s, ", (s->members[p->friends[i]]).name);
	}
	printf("\n");
}	

void print_socialnet(SocialNet *s) {
	printf("------------------------------\n");
	printf("Name\tAge\tRelationship Status\tFriends\n");
	printf("------------------------------\n");
	for (int i = 0; i < s->size; i++ ) {
		// HomeWork: change the code to print all the names of friends of the person in 4th column
		print_person(&(s->members[i]), s);
	}
	printf("------------------------------\n");
}


int main() {
	SocialNet s = {
		.members = {
			{ "Ramu", 19, Single, {1,2}, 2},
			{ "Ammu", 21, Engaged, {2}, 1},
			{ "Vinod", 24, Married, {0}, 1}
		},
		.size = 3
	};
	print_socialnet(&s);

	
	return 0;
}


