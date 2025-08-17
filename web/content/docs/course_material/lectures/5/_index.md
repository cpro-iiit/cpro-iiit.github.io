---
title: "L-05: Advanced Loops, Nested Loops, Loop Control"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

## Lecture 5
 
---
## Recall: Basic Loops

---
### While Loop (Review)

```c
#include <stdio.h>

int main() {
    int i = 1;
    while (i <= 5) {
        printf("%d ", i);
        i++;
    }
    return 0;
}
```
**Output:** `1 2 3 4 5`

---
## For Loop

More compact way to write loops when we know the number of iterations.

```c
#include <stdio.h>

int main() {
    int i;
    for (i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    return 0;
}
```
**Output:** `1 2 3 4 5`

---
### For Loop Structure

```c
for (initialization; condition; update) {
    // code to execute
}
```

**Example:**
```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

---
## Do-While Loop

Executes at least once, then checks condition.

```c
#include <stdio.h>

int main() {
    int i = 1;
    do {
        printf("%d ", i);
        i++;
    } while (i <= 5);
    return 0;
}
```
**Output:** `1 2 3 4 5`

---
### Difference: While vs Do-While

```c
// While loop - may not execute at all
int i = 10;
while (i < 5) {
    printf("%d ", i);  // Never prints
    i++;
}

// Do-while loop - executes at least once
int j = 10;
do {
    printf("%d ", j);  // Prints 10
    j++;
} while (j < 5);
```

---
## Nested Loops

Loop inside another loop.

```c
#include <stdio.h>

int main() {
    int i, j;
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    return 0;
}
```

---
### Output of Nested Loop

```
(1,1) (1,2) (1,3) 
(2,1) (2,2) (2,3) 
(3,1) (3,2) (3,3) 
```

**Inner loop** completes all iterations for each iteration of **outer loop**.

---
## Pattern Printing

### Pattern 1: Rectangle
```c
int rows = 4, cols = 5;
for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= cols; j++) {
        printf("* ");
    }
    printf("\n");
}
```
**Output:**
```
* * * * * 
* * * * * 
* * * * * 
* * * * * 
```

---
### Pattern 2: Right Triangle
```c
int n = 5;
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
        printf("* ");
    }
    printf("\n");
}
```
**Output:**
```
* 
* * 
* * * 
* * * * 
* * * * * 
```

---
### Pattern 3: Number Triangle
```c
int n = 4;
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
        printf("%d ", j);
    }
    printf("\n");
}
```
**Output:**
```
1 
1 2 
1 2 3 
1 2 3 4 
```

---
## Loop Control: Break

**Break** statement exits the loop immediately.

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            break;  // Exit loop when i is 6
        }
        printf("%d ", i);
    }
    return 0;
}
```
**Output:** `1 2 3 4 5`

---
## Loop Control: Continue

**Continue** statement skips current iteration and goes to next.

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        printf("%d ", i);
    }
    return 0;
}
```
**Output:** `1 3 5 7 9`

---
### Break in Nested Loops

Break only exits the **innermost** loop.

```c
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        if (j == 2) {
            break;  // Only exits inner loop
        }
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
```
**Output:**
```
(1,1) 
(2,1) 
(3,1) 
```

---
## Multiplication Table

```c
#include <stdio.h>

int main() {
    int n = 5;
    printf("Multiplication Table for %d:\n", n);
    
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", n, i, n * i);
    }
    return 0;
}
```

---
## Finding Prime Numbers

```c
#include <stdio.h>

int main() {
    int n = 29;
    int isPrime = 1;  // Assume prime
    
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            isPrime = 0;  // Not prime
            break;
        }
    }
    
    if (isPrime)
        printf("%d is prime\n", n);
    else
        printf("%d is not prime\n", n);
    return 0;
}
```

---
## Sum of Digits

```c
#include <stdio.h>

int main() {
    int num = 12345;
    int sum = 0;
    
    while (num > 0) {
        sum += num % 10;  // Add last digit
        num /= 10;        // Remove last digit
    }
    
    printf("Sum of digits: %d\n", sum);
    return 0;
}
```

---
### Exercise: Star Patterns

Write programs to print these patterns:

**Pattern A:**
```
*****
****
***
**
*
```

**Pattern B:**
```
    *
   ***
  *****
 *******
*********
```

---
### Exercise: Number Patterns

**Pattern C:**
```
1
22
333
4444
55555
```

**Pattern D:**
```
12345
1234
123
12
1
```

---
## Nested While Loops

```c
#include <stdio.h>

int main() {
    int i = 1;
    while (i <= 3) {
        int j = 1;
        while (j <= 4) {
            printf("%d ", j);
            j++;
        }
        printf("\n");
        i++;
    }
    return 0;
}
```
**Output:**
```
1 2 3 4 
1 2 3 4 
1 2 3 4 
```

---
## Menu-Driven Program

```c
#include <stdio.h>

int main() {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Print Numbers 1-10\n");
        printf("2. Print Even Numbers\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                for (int i = 1; i <= 10; i++) {
                    printf("%d ", i);
                }
                printf("\n");
                break;
            case 2:
                for (int i = 2; i <= 20; i += 2) {
                    printf("%d ", i);
                }
                printf("\n");
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    
    return 0;
}
```

---
### Exercise: Enhanced Calculator

Create a calculator that:
- Shows menu repeatedly until user chooses to exit
- Performs basic operations (+, -, *, /, %)
- Uses do-while for menu loop
- Uses switch case for operations
- Validates input (no division by zero)

---
### Exercise: Pattern Challenge

Create this diamond pattern using nested loops:
```
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
```

---
### Exercise: Perfect Numbers

Write a program to find all perfect numbers up to 1000.
- A perfect number equals sum of its proper divisors
- Example: 6 = 1 + 2 + 3 (divisors of 6 except 6)
- Use nested loops: outer for numbers, inner for divisors

---
## Common Loop Mistakes

### Infinite Loop
```c
int i = 1;
while (i <= 10) {
    printf("%d ", i);
    // Missing i++ - infinite loop!
}
```

### Off-by-One Error
```c
// Wrong: prints 0 to 9 (10 numbers)
for (int i = 0; i <= 10; i++) {
    printf("%d ", i);
}

// Correct: prints 1 to 10 (10 numbers)
for (int i = 1; i <= 10; i++) {
    printf("%d ", i);
}
```

---
## Loop Efficiency Tips

### Reduce Work in Inner Loop
```c
// Less efficient
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        int temp = i * i;  // Calculated n times!
        printf("%d ", temp + j);
    }
}

// More efficient
for (int i = 0; i < n; i++) {
    int temp = i * i;  // Calculated once
    for (int j = 0; j < n; j++) {
        printf("%d ", temp + j);
    }
}
```

---
### Exercise: Number System Converter

Write a program that:
- Takes a decimal number as input
- Converts it to binary using loops
- Displays the binary representation
- Use do-while loop for conversion process

---
### Exercise: Grade Statistics

Create a program that:
- Reads marks for 10 students using loops
- Calculates average using nested logic
- Counts how many students got each grade (A, B, C, D, F)
- Uses multiple nested loops for processing

---
## Advanced: Loop Optimization

### Early Exit
```c
// Finding if number exists in array
int found = 0;
for (int i = 0; i < n && !found; i++) {
    if (arr[i] == target) {
        found = 1;
        printf("Found at position %d\n", i);
    }
}
```

---
## Reading 

**Next: Arrays, Strings, Functions**

### Textbooks:
- **Chapter 4 & 5:** Computer Science: A Structured Programming Approach Using C - Behrouz A. Forouzan, Richard F. Gilberg

### Online Resources:
- **Practice Compiler:** https://tinyurl.com/bdd55vwn (Programiz Online C Compiler)
- **Pattern Programming:** https://www.programiz.com/c-programming/examples/pyramid-pattern
- **Loop Tutorials:** https://www.tutorialspoint.com/cprogramming/c_loops.htm

### Interactive Learning:
- **Visualizing Loops:** https://pythontutor.com/c.html#mode=edit (Step-by-step code execution)
- **Pattern Practice:** https://www.geeksforgeeks.org/programs-printing-pyramid-patterns-c/

### Video Resources:
- **C Programming Loops:** Search "C programming nested loops" on YouTube
- **Pattern Programming:** Look for "C star pattern programs" tutorials

### Documentation:
- **C Reference:** https://en.cppreference.com/w/c/language/for
- **Loop Control:** https://www.cprogramming.com/tutorial/c/lesson3.html

<!-- 
Topics covered:
- For loops introduction
- Do-while loops
- Nested loops (for and while)
- Loop control (break, continue)
- Pattern printing
- Menu-driven programs
- Common mistakes and optimization
-->
