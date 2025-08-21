---
title: "L-06: Arrays, Strings"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---



# Arrays in C Programming

---

## What is an Array?

- An **array** is a collection of elements of the **same data type** stored in contiguous memory locations.
- Each element is accessed using an **index**.
- In C, array indices start from **0**.

**Syntax:**
```c
data_type array_name[size];
```
---
## Example: Declaring Arrays

```c
int marks[5];           // Array of 5 integers
float prices[10];       // Array of 10 floats
char name[20];          // Array of 20 characters
```

Memory is allocated contiguously.

marks[0], marks[1], ... marks[4]

[code](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0Aint%20main%28%29%20%7B%0A%20%20%20%20int%20marks%5B5%5D%20%3D%20%7B90,%2085,%2088,%2092,%2075%7D%3B%0A%20%20%20%20for%20%28int%20i%20%3D%200%3B%20i%20%3C%205%3B%20i%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20printf%28%22marks%5B%25d%5D%20%3D%20%25d%5Cn%22,%20i,%20marks%5Bi%5D%29%3B%0A%20%20%20%20%7D%0A%20%20%20%20return%200%3B%0A%7D&cumulative=false&curInstr=14&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)

---
## Example: Input from user

```c
#include <stdio.h>

int main() {
    int arr[5];
    for (int i = 0; i < 5; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &arr[i]);
    }

    printf("You entered: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
```
---
## Example: Sum of elements

```c
#include <stdio.h>

int main() {
    int arr[5] = {2, 4, 6, 8, 10};
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    printf("Sum = %d\n", sum);
    return 0;
}
```

---

## Example: Find duplicates in an array

```c
#include <stdio.h>

int main() {
    int marks[5] = {90, 85, 88, 92, 88};
    for (int i = 0; i < 5; i++) {
      for(int j = i + 1; j < 5; j++) {
        if (marks[i] == marks[j]) {
          printf("Found duplicate number %d in %d, %d positions\n", marks[i], i, j);
          return 0;
        }
      }
    }
    printf("No duplicates\n");
    return 0;
}
```

[Step by Step Execution](
https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0Aint%20main%28%29%20%7B%0A%20%20%20%20int%20marks%5B5%5D%20%3D%20%7B90,%2085,%2088,%2092,%2088%7D%3B%0A%20%20%20%20for%20%28int%20i%20%3D%200%3B%20i%20%3C%205%3B%20i%2B%2B%29%20%7B%0A%20%20%20%20%20%20for%28int%20j%20%3D%20i%20%2B%201%3B%20j%20%3C%205%3B%20j%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20if%20%28marks%5Bi%5D%20%3D%3D%20marks%5Bj%5D%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20printf%28%22Found%20duplicate%20number%20%25d%20in%20%25d,%20%25d%20positions%5Cn%22,%20marks%5Bi%5D,%20i,%20j%29%3B%0A%20%20%20%20%20%20%20%20%20%20return%200%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%7D%0A%20%20%20%20%7D%0A%20%20%20%20printf%28%22No%20duplicates%5Cn%22%29%3B%0A%20%20%20%20return%200%3B%0A%7D&cumulative=false&heapPrimitives=nevernest&mode=edit&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)
---
## Exercise
Print all duplicates in the array (previous program stopped at the first time duplicate is found). Only if no duplicates are found, print "No duplicates".

---

# Strings in C Programming

---

## What is a String?

- A **string** in C is an **array of characters** ending with a special character `'\0'` (null terminator).
- Unlike some other languages, C does not have a **built-in string type** — they are handled using **character arrays**.

**Syntax:**
```c
char str[size];
```
---
## Declaring and Initializing Strings
```c
char name[20] = "Alice";
```
Other Ways
```c
char name[] = "Alice";        // Size auto-determined
char name[6] = {'A','l','i','c','e','\0'};
```
---
## Input and Output of Strings

```c
#include <stdio.h>

int main() {
    char name[50];

    printf("Enter your name: ");
    scanf("%s", name);   // Reads until space

    printf("Hello %s!\n", name);
    return 0;
}
```
---


## Example Problem: Count Vowels in a String

```c

  #include <stdio.h>
  #include <string.h>

  int main() {
      char str[100] = "Hello World!";
      int count = 0;

      for(int i=0; str[i] != '\0'; i++) {
          char c = str[i];
          if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U') {
              count++;
          }
      }
      printf("Number of vowels = %d\n", count);
      return 0;
  }
```

---


## Next Class

- String Library
- Multidimensional Arrays