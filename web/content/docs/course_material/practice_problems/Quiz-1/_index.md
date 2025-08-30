# Quiz-1 Practice Problems

### Question 1: Scanf Buffer Issues
Analyze this code and explain what happens when user enters "123 A":
```c
#include <stdio.h>
int main() {
    int num;
    char ch1, ch2;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Enter first char: ");
    scanf("%c", &ch1);
    printf("Enter second char: ");
    scanf("%c", &ch2);
    
    printf("num=%d, ch1='%c', ch2='%c'\n", num, ch1, ch2);
    return 0;
}
```


### Question 2: Operator Precedence Challenge
Trace through this code step by step. What will be the final values?
```c
#include <stdio.h>
int main() {
    int a = 10, b = 5, c = 3;
    int result1 = a + b * c / a - b % c;
    int result2 = (a + b) * c / (a - b) % c;
    int result3 = a++ + ++b - c-- * --a;
    
    printf("a=%d, b=%d, c=%d\n", a, b, c);
    printf("result1=%d, result2=%d, result3=%d\n", result1, result2, result3);
    return 0;
}
```


### Question 3: Short-Circuit Evaluation and Side Effects
Predict the output and explain why certain parts might not execute:
```c
#include <stdio.h>
int main() {
    int a = 0, b = 5, c = 10;
    
    printf("Before: a=%d, b=%d, c=%d\n", a, b, c);
    
    if (a && (b = 20)) {
        printf("First condition true\n");
    }
    
    if (c || (a = 15)) {
        printf("Second condition true\n");
    }
    
    printf("After: a=%d, b=%d, c=%d\n", a, b, c);
    return 0;
}
```


### Question 4: Assignment vs Comparison
Find the error in this code and explain why it produces unexpected results:
```c
#include <stdio.h>
int main() {
    int score = 85;
    
    if (score = 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else {
        printf("Grade: C\n");
    }
    
    printf("Final score: %d\n", score);
    return 0;
}
```

### Question 5: Tilde Operator (~) in C
Analyze this code and explain what the tilde operator does:
```c
#include <stdio.h>
int main() {
    int a = 5;
    int b = -3;
    unsigned int c = 10;
    
    printf("a = %d, ~a = %d\n", a, ~a);
    printf("b = %d, ~b = %d\n", b, ~b);
    printf("c = %u, ~c = %u\n", c, ~c);
    
    // Practical example: checking even/odd
    if (~a & 1) {
        printf("%d is even\n", a);
    } else {
        printf("%d is odd\n", a);
    }
    
    return 0;
}
```

### Question 6: Nested If vs Switch
Compare these two code segments. When would each be more appropriate?
```c
// Version 1: Nested If
if (grade >= 90) {
    if (grade <= 100) {
        printf("A\n");
    } else {
        printf("Invalid\n");
    }
} else if (grade >= 80) {
    printf("B\n");
} else if (grade >= 70) {
    printf("C\n");
} else {
    printf("F\n");
}

// Version 2: Switch
switch (grade / 10) {
    case 10:
    case 9:
        printf("A\n");
        break;
    case 8:
        printf("B\n");
        break;
    case 7:
        printf("C\n");
        break;
    default:
        printf("F\n");
}
```

### Question 7: Break vs Continue
Trace through this code and predict the output:
```c
#include <stdio.h>
int main() {
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            continue;
        }
        if (i > 7) {
            break;
        }
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
```

### Question 8: Nested Loops with Control
What pattern will this code produce? Explain the role of break in nested loops:
```c
#include <stdio.h>
int main() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (i + j > 4) {
                break;
            }
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
```

### Question 9: Array Initialization and Access
What will be printed by this code? Explain array initialization behavior:
```c
#include <stdio.h>
int main() {
    int arr1[5] = {1, 2, 3};
    int arr2[5] = {0};
    int arr3[5];
    
    for (int i = 0; i < 5; i++) {
        printf("arr1[%d]=%d, arr2[%d]=%d, arr3[%d]=%d\n", 
               i, arr1[i], i, arr2[i], i, arr3[i]);
    }
    return 0;
}
```


### Question 11: Two's Complement Representation
Analyze this code that demonstrates two's complement arithmetic:
```c
#include <stdio.h>
int main() {
    int a = 5;
    int b = -5;
    
    printf("a = %d (binary representation)\n", a);
    printf("b = %d (two's complement)\n", b);
    printf("a + b = %d\n", a + b);
    
    // Demonstrating overflow
    int max_int = 2147483647;  // Assuming 32-bit int
    printf("max_int = %d\n", max_int);
    printf("max_int + 1 = %d\n", max_int + 1);
    
    // Two's complement calculation
    int x = 10;
    int neg_x = ~x + 1;
    printf("x = %d, two's complement = %d\n", x, neg_x);
    
    return 0;
}
```

### Question 12: Bitwise Operations in Practice
What will be the output? Explain each bitwise operation:
```c
#include <stdio.h>
int main() {
    int a = 12;  // 1100 in binary
    int b = 7;   // 0111 in binary
    
    printf("a = %d, b = %d\n", a, b);
    printf("a & b = %d\n", a & b);    // AND
    printf("a | b = %d\n", a | b);    // OR
    printf("a ^ b = %d\n", a ^ b);    // XOR
    printf("~a = %d\n", ~a);          // NOT
    printf("a << 2 = %d\n", a << 2);  // Left shift
    printf("a >> 2 = %d\n", a >> 2);  // Right shift
    
    // Practical example: Check if number is power of 2
    int num = 16;
    if ((num & (num - 1)) == 0 && num != 0) {
        printf("%d is power of 2\n", num);
    } else {
        printf("%d is not power of 2\n", num);
    }
    
    return 0;
}
```

### Question 13: Floating Point Representation Issues
Why does this code produce unexpected results? Explain IEEE 754 representation:
```c
#include <stdio.h>
int main() {
    float a = 0.1;
    float b = 0.2;
    float sum = a + b;
    
    if (sum == 0.3) {
        printf("Sum is exactly 0.3\n");
    } else {
        printf("Sum is not exactly 0.3\n");
        printf("Actual sum: %.20f\n", sum);
        printf("Expected: %.20f\n", 0.3f);
    }
    
    // Epsilon comparison
    float epsilon = 0.0001;
    if (fabs(sum - 0.3) < epsilon) {
        printf("Sum is approximately 0.3 (using epsilon)\n");
    }
    
    // Zero representation
    float zero1 = 0.0;
    float zero2 = -0.0;
    printf("zero1 = %f, zero2 = %f\n", zero1, zero2);
    printf("Are they equal? %s\n", (zero1 == zero2) ? "Yes" : "No");
    
    return 0;
}
```

### Question 15: Mixed Type Logical Evaluation
What will be the output? Explain how C evaluates different types in logical contexts:
```c
#include <stdio.h>
int main() {
    int x = 5, y = 0, z = -3;
    float a = 0.0, b = 2.5, c = -1.2;
    char ch1 = 'A', ch2 = '\0';
    
    printf("Integer evaluations:\n");
    printf("x && y: %d\n", x && y);
    printf("x || y: %d\n", x || y);
    printf("!z: %d\n", !z);
    
    printf("Float evaluations:\n");
    printf("a && b: %d\n", a && b);
    printf("b || c: %d\n", b || c);
    printf("!a: %d\n", !a);
    
    printf("Character evaluations:\n");
    printf("ch1 && ch2: %d\n", ch1 && ch2);
    printf("ch1 || ch2: %d\n", ch1 || ch2);
    printf("!ch2: %d\n", !ch2);
    
    // Mixed type evaluations
    printf("Mixed type evaluations:\n");
    printf("x && a: %d\n", x && a);
    printf("ch1 && z: %d\n", ch1 && z);
    printf("b || y: %d\n", b || y);
    
    return 0;
}
```

### Question 16: Equality vs Assignment in Conditions
Find all the errors and explain the behavior:
```c
#include <stdio.h>
int main() {
    int score = 85;
    int grade = 0;
    
    // Error-prone conditions
    if (score = 90) {
        grade = 4;
    } else if (score = 80) {
        grade = 3;
    } else if (score = 70) {
        grade = 2;
    } else {
        grade = 1;
    }
    
    printf("Final score: %d, Grade: %d\n", score, grade);
    
    // Another problematic example
    int flag = 1;
    if (flag == 1 = 0) {  // What's wrong here?
        printf("This won't compile\n");
    }
    
    return 0;
}
```


---
## do while loops
Predict output of the following programs:

```c
#include <stdio.h>
int main() {
    int x = 5;
    do {
        printf("%d ", x);
        x++;
    } while (x < 5);
    return 0;
}
```

```c
#include <stdio.h>
int main() {
    int i = 1;
    do {
        printf("%d ", i);
        i++;
    } while (i <= 3);
    return 0;
}
```

```c
#include <stdio.h>
int main() {
    int n = 3;
    do {
        printf("%d ", n);
        n--;
    } while (n > 0);
    return 0;
}
```

```c
#include <stdio.h>
int main() {
    int i = 1;
    do {
        printf("%d ", i);
        i += 2;
    } while (i < 10);
    return 0;
}
```

```c
#include <stdio.h>
int main() {
    int i = 1, j;
    do {
        j = 1;
        do {
            printf("(%d,%d) ", i, j);
            j++;
        } while (j <= 2);
        i++;
        printf("\n");
    } while (i <= 2);
    return 0;
}
```

```c
#include <stdio.h>
int main() {
    int x = 0;
    do {
        printf("%d ", x);
        x += 2;
    } while (x == 1);
    return 0;
}
```
---

## char and int overflows

predict output of following programs

Problem 1 (Basic Signed char Overflow)

```c
#include <stdio.h>
int main() {
    char c = 127;   // max value for signed char
    c = c + 1;
    printf("%d\n", c);
    return 0;
}
```

Problem 2 (Unsigned char Wrap-Around)
```c
#include <stdio.h>
int main() {
    unsigned char c = 255;
    c = c + 1;
    printf("%u\n", c);
    return 0;
}
```

Problem 3 (Signed Overflow in int)

```c
#include <stdio.h>
int main() {
    int x = 2147483647;
    printf("%d\n", x + 1);
    return 0;
}
```

Problem 4 (Unsigned int Wrap)

```c
#include <stdio.h>
int main() {
    unsigned int x = 4294967295; //uint max on 32 bit
    printf("%u\n", x + 1);
    return 0;
}
```

Problem 5 (Mixing Signed and Unsigned)
```c
#include <stdio.h>
int main() {
    int a = -1;
    unsigned int b = 1;
    if (a < b)
        printf("a < b\n");
    else
        printf("a >= b\n");
    return 0;
}
```

Problem 6 (Unsigned Promotion in Expression)
```c
#include <stdio.h>
int main() {
    unsigned int x = 0;
    int y = -1;
    if (y > x)
        printf("y > x\n");
    else
        printf("y <= x\n");
    return 0;
}
```

Problem 7 (Tricky Char Wrap)

```c
#include <stdio.h>
int main() {
    signed char c = -128;
    c = c - 1;
    printf("%d\n", c);
    return 0;
}
```

Problem 8 (Unsigned Arithmetic Overflow Cascade)
```c
#include <stdio.h>
int main() {
    unsigned int x = 4294967295;  // UINT_MAX on 32-bit
    unsigned int y = 10;
    unsigned int z = x + y;
    printf("%u\n", z);
    return 0;
}
```

---
## semicolons, spacing

predict output of following programs

Problem 1 (Stray Semicolon in if)

```c
#include <stdio.h>
int main() {
    int x = 5;
    if (x > 0);
        printf("Positive\n");
    return 0;
}
```

Problem 2 (While with Null Body)

```c
#include <stdio.h>
int main() {
    int i = 0;
    while (i < 3);
    {
        printf("%d ", i);
        i++;
    }
    return 0;
}
```

Problem 3 (For Loop with Empty Body)

```c
#include <stdio.h>
int main() {
    int i;
    for (i = 0; i < 5; i++);
    printf("%d\n", i);
    return 0;
}
```
Problem 4 (Multiple Semicolons)
```c
#include <stdio.h>
int main() {
    int x = 10;
    if (x == 10);;;;
    {
        printf("Hello\n");
    }
    return 0;
}
```
Problem 5 (Spacing Misleading Indentation)
```c
#include <stdio.h>
int main() {
    int x = 0;
    if (x == 0)
        printf("One\n");
        printf("Two\n");
    return 0;
}
```
Problem 6 (Do-While Null Loop)
```c
#include <stdio.h>
int main() {
    int i = 0;
    do
        i++;
    while (i < 3);
    printf("%d\n", i);
    return 0;
}
```
---

