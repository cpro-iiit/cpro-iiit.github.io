---
title: "L22: More Social Net and Macros"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# Social Nets | Macros


## Social Nets

```c
typedef enum RelStatus {
    NotMentioned,
    Single,
    Engaged,
    Married
} RelStatus;

typedef struct Person {
    char name[100];
    int age;
    RelStatus relstatus;
    int friends[5];
    int num_friends;
} Person;

typedef struct SociaslNet {
    Person members[100];
    int size;
} SocialNet;
```
---

## Social Nets with Macros

```c

#define MAX_FRIENDS 5
#define MAX_MEMBERS 100
#define MAX_NAME_LEN 100

typedef enum RelStatus {
    NotMentioned,
    Single,
    Engaged,
    Married
} RelStatus;

typedef struct Person {
    char name[MAX_NAME_LEN];
    int age;
    RelStatus relstatus;
    int friends[MAX_FRIENDS];
    int num_friends;
} Person;

typedef struct SociaslNet {
    Person members[MAX_MEMBERS];
    int size;
} SocialNet;
```
---


## Social Nets with Person*
```c

#define MAX_FRIENDS 5
#define MAX_MEMBERS 100
#define MAX_NAME_LEN 100

typedef enum RelStatus {
    NotMentioned,
    Single,
    Engaged,
    Married
} RelStatus;

typedef struct Person {
    char name[100];
    int age;
    RelStatus relstatus;
    struct Person* friends[5];
    int num_friends;
} Person;

typedef struct SocialNet {
    Person members[100];
    int size;
} SocialNet;
```
---


## Full Code in the lecture

```c
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_MEMBERS 100
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

typedef struct SocialNet {
	Person members[MAX_MEMBERS];
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
	SocialNet s = {
		.members = {
			{ "Ramu", 19, Single, .friends_size = 0},
			{ "Ammu", 21, Engaged, .friends_size = 0},
			{ "Vinod", 24, Married, .friends_size = 0}
		},
		.size = 3
	};
	add_friend(&(s.members[0]) , &(s.members[1]) );
	add_friend(&(s.members[0]) , &(s.members[2]) );
	add_friend(&(s.members[1]) , &(s.members[2]) );
	add_friend(&(s.members[2]) , &(s.members[0]) );
	
	print_socialnet(&s);

	
	return 0;
}
```

---

## HW: Finding a person by name

```c
Person* find_person(char* name1, SocialNet *sn) {
    // TODO (solution at the end of page)
}
```
---

## HW: Check Mutual Friends by name
```c
bool check_mutual_friends(char *name1, char *name2, SocialNet *sn) {
 // TODO p and q are mutual friends if q is in the friend list of p
 // and p is in the friend list of q
}
```

---
