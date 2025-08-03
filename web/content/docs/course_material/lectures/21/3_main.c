#include <stdio.h>
#include <string.h>

typedef enum RelStatus {
	NotMentioned,
	Single,
	Engaged,
	Married
} RelStatus;


typedef struct Person {
	char name[100];
	int age;
	RelStatus status;
	int friends[10];
	int friends_size;
} Person;

typedef struct SocialNet {
	Person members[100];
	int size;
} SocialNet;


void print_person(Person* p) {
	char status_string[4][30] = {
		{ "Not Mentioned"},
		{ "Single" },
		{ "Engaged"},
		{ "Married" }
	};
	printf("%s\t%d\t%s\n", p->name, p->age, status_string[p->status]);
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


