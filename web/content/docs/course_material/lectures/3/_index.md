---
title: "L-03: Operators, Precedence, Conditionals"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

## Lecture 3
__Girish Varma__
 
---
## Recall Printf, Scanf, Variable

---
### Reading and Printing a number

```c
#include <stdio.h>

int main() {
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);
    printf("You entered: %d\n", number);
    return 0;
}
```

---
## Adding 2 numbers

```c
#include <stdio.h>

int main() {
    int a, b, sum;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    sum = a + b;
    printf("Sum: %d\n", sum);
    return 0;
}
```

---
## Arithmetic Operations

```c
#include <stdio.h>

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Sum: %d\n", a + b);
    printf("Difference: %d\n", a - b);
    printf("Product: %d\n", a * b);
    printf("Quotient: %d\n", a / b);
    printf("Remainder: %d\n", a % b);
    return 0;
}
```
---
## Assignment
### Swapping
```c
#include <stdio.h>

int main() {
    int x, y, temp;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);
    temp = x;
    x = y;
    y = temp;
    printf("After swapping: x = %d, y = %d\n", x, y);
    return 0;
}
```

---
## Conditional Statements

```c
#include <stdio.h>
int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    if (num % 2 == 0)
        printf("Even\n");
    else
        printf("Odd\n");
    return 0;
}
```

---
## Nested Conditional Statements

```c
if (marks >= 90 && marks <= 100) {
        printf("Grade: A\n");
} else {
        if (marks >= 80) {
                printf("Grade: B\n");
        } else {
                if (marks >= 70) {
                        printf("Grade: C\n");
                } else {
                        if (marks >= 60) {
                                printf("Grade: D\n");
                         } else {
                                printf("Grade: F\n");
                        }
                }
        }
}
```


---

## Reading 

**Next: Conditional Statements: if, else, while, switch, break, continue.**

- Chapter 3: Computer Science: A Structured Programming Approach Using C    Behrouz A. Forouzan, Richard F. Gilberg

- More about scanf : https://www.ibm.com/docs/en/i/7.4?topic=functions-scanf-read-data

- Programiz, web editor: https://tinyurl.com/bdd55vwn
- http://courses.washington.edu/mengr477/resources/Precedence.pdf

## Exercises

For practice problems on this lecture, see: [L-03 Exercise Questions](exercises-l03.md)

<!-- Order
spellings
less slides/ -->
