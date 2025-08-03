---
title: "L20: Structs, Strings and GDB"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---



## Recall Structs: Rectangle Example


```c
#include<stdio.h>
struct rectangle {
	float length;
	float breadth;
};

float compute_area(struct rectangle r) {
	return r.length * r.breadth;
}

void print_rectangle(struct rectangle r) {
	printf("Rectangle with length %f and breadth %f\n", r.length, r.breadth);
}

int main()
{
	struct rectangle rect = { 1.5, 3.2 }; // Initializer 		
	print_rectangle(rect);
	printf("Area of the rectangle is %f \n", compute_area(rect) );
} 
```
---
## Struct with Typedef
```c
#include<stdio.h>
typedef struct rectangle {
	float length;
	float breadth;
} rectangle;

float compute_area(rectangle r) {
	return r.length*r.breadth;
}

rectangle scale(rectangle r, float s) {
	r.length = r.length*s;
	r.breadth = r.breadth*s;
	return r;
}

int main()
{
	rectangle rect = {  .breadth = 1.0, .length = 3.0} /* {3.0, 1.0 }*/; 		
	// rect.length = 3.2;
	// rect.breadth = 1.2;
	printf("Area of the rectangle is %f \n", compute_area(rect));
	rectangle rp = scale(rect, 5);
	printf("Area of the rectangle is %f \n", compute_area(rp));
	printf("Area of the rectangle is %f \n", compute_area(rect));
} 
```
---
## Passing using pointers
```c
#include<stdio.h>
typedef struct rectangle {
	float length;
	float breadth;
} rectangle;

float compute_area(rectangle r) {
	return r.length*r.breadth;
}

rectangle* scale(rectangle* r, float s) {
	r->length = r->length*s;
	r->breadth = r->breadth*s;
	return r;
}

int main()
{
	rectangle rect = {  .breadth = 1.0, .length = 3.0} /* {3.0, 1.0 }*/; 		
	// rect.length = 3.2;
	// rect.breadth = 1.2;
	printf("Area of the rectangle is %f \n", compute_area(rect));
	rectangle* rp = scale(&rect, 5);
	printf("Area of the rectangle is %f \n", compute_area(*rp));
	printf("Area of the rectangle is %f \n", compute_area(rect));
} 
```
---


## Strings in C
- as a pointer to char
```c
char *p = "abcde";
```
- as an array of char
```c
char s[] = "abcde";
```

![](string_fig.png)

```c
print("%d %d", sizeof(p), sizeof(s));
```
---
## String Function Implementation

```c
#include "stdio.h"

int strlenB(char* s) {
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

char* strcpyB(char *s, char *d) {
	int len_s = strlenB(s);
	for(int i = 0; i <= len_s;i++) {
		d[i] = s[i];
	}
	return d;
}

char* str_rev(char *s, char *d) {
	int len_s = strlenB(s);
	for(int i = 0; i< len_s; i++) {
		d[i] = s[len_s - 1 - i];
	}
	d[len_s] = '\0';
	return d;
}

int main() {
	char *p = "xyz\0dsalkfjds";
	char s[] = "abcde\0kjdakfjsh"; // abcde\0

	// printf("%d %d\n",sizeof(p),sizeof(s));
	// printf("%s %s\n",p, s);
	// printf("%d %d\n", strlen(p), strlen(s));
	// strcpy(s,p);
	printf("%s\n",str_rev(p, s));

	return 1;
}
```
---
## String Functions

`#include <string.h>`

- `int strlen(char *s)`: returns the length of the string pointed by s (ie lenth upto the first `\0` in memory).
- `char* strcat(char* s1, char* s2)`: concatenates s1 with s2, stores it in s1 and returns s1.
- `int strcmp(char *s1,char *s2)`: returns negative int if s1 is lex. smaller than s2, returns 0 if equal, returns positive int if s1 is lex. greater than s2.
- `char* strcpy(char* s1, char* s2)`: copies s2 in to s1 and returns s1.

---
## Debugger



[GDB Cheatsheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)   

[GDB Tutorial Slides UMD](https://www.cs.umd.edu/~srhuang/teaching/cmsc212/gdb-tutorial-handout.pdf)  

---

## Summary
- Struct with Typedef
- Passing Struct with Pointer
- Struct pointer accessing fields notation
- Recalling Strings in C
- Debugger