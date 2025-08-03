---
title: "L19: Structs"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'

revealjs_config:
  slideNumber: true
---


## Structs


```c
#include "stdio.h"
// For using strcpy, strlen functions
#include "string.h"

// Defining a structure to store the details of a single student
struct Student {
	char name[100];
	char email[100];
	float marks;
};


int main() {

  // create a array of struct Student to store data for the whole class
  // here only 2 students are there as an example
	struct Student class[2] = {
		{ .name = "Raju", .marks = 25.5 }, // initializer syntax
		{ "Ammu", "ammu@research.iiit.ac.in", 45.0 } // initiallizer syntax
	};
	strcpy(class[0].name, "Girish Varma");

	class[0].marks = 80.0;

	printf("%lu\n", sizeof(struct Student));

	 printf("Student Details:\nName:\t %s %lu \nEmail:\t %s\nMarks:\t %f\n", class[0].name, strlen(class[0].name), class[0].email, class[0].marks);
  	printf("Student Details:\nName:\t %s\nEmail:\t %s\nMarks:\t %f\n", class[1].name, class[1].email, class[1].marks);
 
	return 0;
}
```
---
## Summary

- Structs
	- Definition
	- Initialization
	- Accessing Fields
- Strings
	- string.h
	- strcpy
	- strlen

