---
title: "L9: Multidimensional Arrays, String Library and Functions"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---


## L9: Multidimensional Arrays, String Library and Functions


---


## What are Multidimensional Arrays?

- In C, arrays can have **two or more dimensions**.
- Commonly used: **2D arrays** (like a matrix or table).
- General form:
```c
data_type array_name[size1][size2]...[sizeN];
```
Example:
```c
int matrix[3][4]; // 3 rows, 4 columns
```
---

## Memory Layout
Stored in row-major order in C

Example:

```c
int arr[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```
Stored as: 1, 2, 3, 4, 5, 6 in contiguous memory.

--- 

## Example 1: Initializing and Printing
```c
#include <stdio.h>
int main() {
    int a[2][3] = {{1,2,3}, {4,5,6}};
    for(int i=0; i<2; i++) {
        for(int j=0; j<3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```
---

## Example 2: Sum of Elements in 2D Array
<!-- ```c
#include <stdio.h>
int main() {
    int a[2][2] = {{10, 20}, {30, 40}};
    int sum = 0;
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            sum += a[i][j];
        }
    }
    printf("Sum = %d\n", sum);
    return 0;
}
``` -->
---

## Example 3: Matrix Addition
<!-- 
```c
#include <stdio.h>
int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2];

    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            C[i][j] = A[i][j] + B[i][j];
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
``` -->
---

## Example 4: Matrix Multiplication (3x3)
<!-- 
```c
#include <stdio.h>
int main() {
    int A[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    int B[3][3] = {{9,8,7}, {6,5,4}, {3,2,1}};
    int C[3][3] = {0};

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
``` -->
---

## Example 5: 3D Array

```c
#include <stdio.h>
int main() {
    int arr[2][2][2] = {
        { {1,2}, {3,4} },
        { {5,6}, {7,8} }
    };
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++) {
                printf("%d ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
```

---



# Strings in C: `<string.h>`

---

## Introduction

- Strings in C are arrays of `char` ending with `'\0'` (null terminator).
- Standard library `<string.h>` provides functions for:
  - Copying
  - Concatenation
  - Comparison
  - Length calculation
  - Searching

---

## strlen – Find String Length

```c
#include <stdio.h>
#include <string.h>
int main() {
    char str[] = "Hello World";
    printf("Length = %lu\n", strlen(str));
    return 0;
}
```

---

## strcpy & strncpy – Copy Strings

```c
#include <stdio.h>
#include <string.h>
int main() {
    char src[] = "C Programming";
    char dest[20];
    strcpy(dest, src);   // copy whole string
    printf("Copied: %s\n", dest);

    char dest2[10];
    strncpy(dest2, src, 5); // copy first 5 chars
    dest2[5] = '\0';        // add null terminator
    printf("Partial: %s\n", dest2);
    return 0;
}
```

--- 

## strcat & strncat – Concatenate Strings

```c
#include <stdio.h>
#include <string.h>
int main() {
    char str1[30] = "Hello";
    char str2[] = " World";
    strcat(str1, str2);
    printf("%s\n", str1);

    char str3[30] = "Hello";
    strncat(str3, str2, 3); // Append first 3 chars
    printf("%s\n", str3);
    return 0;
}

```
---

## strcmp – Compare Strings

```c
#include <stdio.h>
#include <string.h>
int main() {
    char a[] = "apple", b[] = "banana";
    int res = strcmp(a, b);
    if(res == 0)
        printf("Equal\n");
    else if(res < 0)
        printf("%s comes before %s\n", a, b);
    else
        printf("%s comes after %s\n", a, b);
    return 0;
}
```

---


# Functions in C

---

## What are Functions?

- A **function** is a block of code that performs a specific task.
- Helps in:
  - Code reuse
  - Better readability
  - Modular programming
- Types:
  - **Library functions** (e.g., `printf`, `scanf`, `sqrt`)
  - **User-defined functions**

---

## Function Syntax

```c
return_type function_name(parameter_list) {
    // body of function
    return value; // if return_type is not void
}
```

return_type: type of value returned

function_name: identifier

parameter_list: input arguments (optional)

---
## Example 1: Simple Function

```c
#include <stdio.h>

void greet() {
    printf("Hello, welcome to C programming!\n");
}

int main() {
    greet();   // function call
    return 0;
}
```
---

## Example 2: Function with Parameters

```c
#include <stdio.h>

void printSum(int a, int b) {
    printf("Sum = %d\n", a + b);
}

int main() {
    printSum(5, 7);
    return 0;
}
```
---
##  Example 3: Function with Return Value

```c
#include <stdio.h>

int square(int x) {
    return x * x;
}

int main() {
    int result = square(6);
    printf("Square = %d\n", result);
    return 0;
}
```

---

##  Example 4: Multiple Functions

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}
int multiply(int a, int b) {
    return a * b;
}

int main() {
    printf("Add = %d\n", add(3,4));
    printf("Multiply = %d\n", multiply(3,4));
    return 0;
}
```

---
## Function Declaration & Definition
Declaration (prototype): tells compiler about function
int add(int, int);

Definition: actual code body

```c
int add(int a, int b) { return a + b; }
```

Call: using function name with arguments
```c
int sum = add(5, 6);
```
---
##  Example 5: Recursive Function

```c
#include <stdio.h>

int factorial(int n) {
    if(n == 0) return 1;
    return n * factorial(n - 1);
}

int main() {
    printf("Factorial of 5 = %d\n", factorial(5));
    return 0;
}
```
---

## Key Takeaways
Functions improve modularity and code reuse.

Components:

Declaration (prototype)

Definition (body)

Call (usage)

Can have:

No parameters / no return

Parameters only

Return only

Both parameters and return

Recursion is when a function calls itself.




