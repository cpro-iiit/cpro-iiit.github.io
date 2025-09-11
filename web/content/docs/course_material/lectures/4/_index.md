---
title: "L04: Operators, Precedence, Conditionals, Loops"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

## Lecture 4
__Girish Varma__
 

---

# C Programming Basics

### Focus Topics:
1. Operators & Precedence
2. Conditionals & Loops
3. Nested Conditionals
4. Switch Case
5. Loops (While, For, Do-While)

---

## Operators & Precedence

**Operators** are symbols that tell the compiler to perform specific mathematical or logical operations.

**Examples:**
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Relational: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Logical: `&&`, `||`, `!`
- Assignment: `=`, `+=`, `-=`, etc.

---
**Operator Precedence Table (Simplified)**  
From high → low priority:

1. `()`  
2. `*` `/` `%`  
3. `+` `-`  
4. `<` `<=` `>` `>=`  
5. `==` `!=`  
6. `&&`  
7. `||`  
8. `=` `+=` `-=` etc.

---

## Example: Operator Precedence

```c
#include <stdio.h>
int main() {
    int result = 10 + 20 * 3;
    printf("%d\n", result); // 70 (not 90)
    return 0;
}
```
---
## Exercise: Operators
Predict the output without running:
```c
int x = 5, y = 10;
int z = x + y * x / y;
printf("%d\n", z);
```
---
## Conditionals

Conditionals control decision-making in programs.
```c
if (condition) {
    // code if condition is true
} else {
    // code if condition is false
}

```


---
## Nested Conditionals

```c
if (condition1) {
    if (condition2) {
        // executes if both condition1 and condition2 are true
    } else {
        // executes if condition1 is true, condition2 is false
    }
} else {
    // executes if condition1 is false
}
```

---
## Example from last class

```c
if (marks >= 90 && marks <= 100) {
    printf("Grade: A\n");
} else if (marks >= 80) {
    printf("Grade: B\n");
} else if (marks >= 70) {
    printf("Grade: C\n");
} else if (marks >= 60) {
    printf("Grade: D\n");
} else {
    printf("Grade: F\n");
}
```

---
## Switch Case

```c
switch (expression) {
    case constant1:
        // code block
        break;
    case constant2:
        // code block
        break;
    ...
    default:
        // default code block
}

```
---
## Example

```c
#include <stdio.h>
int main() {
    int day = 3;
    switch (day) {
        case 1: printf("Monday\n"); break;
        case 2: printf("Tuesday\n"); break;
        case 3: printf("Wednesday\n"); break;
        default: printf("Invalid day\n");
    }
    return 0;
}
```

---
## Loops

---
## While

```c
int count = 1;
while (count <= 5) {
    printf("%d\n", count);
    count++; // update
}

```
---
### Fibonacci
$f_0 = 0$
$f_1 = 1$
$f_n = f_{n-1} = f_{n-2}$

So $f_2 = 1, f_3 = 2, f_4 = 3, f_5= 5, \cdots$.

Given input $n$, find $f_{n}$.

---
### Fibonacci Program

```c
int n = 10;
int i = 1;
long long c = 0, f = 0 , t = 1;
while (i < n) {
    c = f + t;
    f = t;
    t = c;
    i = i + 1;
    printf("%d\n", c);
}
```

---
### Exercise: Euclid's GCD
Read Euclid's GCD Algorithm and implement it using a loop.
```
Start → Input a, b
        ↓
    a != b?
     /   \
   Yes    No → Print a as GCD → End
   / \
a>b?  No
 /       \
a=a-b   b=b-a
```
---
## Exercises

Practice problems for this lecture: [L-04 Exercise Questions](exercises-l04.md)


---
