# Quiz-1 Practice Problems - C Pro

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

### Question 10: 2D Array Access Pattern
What will this code print? Explain how 2D arrays are stored in memory:
```c
#include <stdio.h>
int main() {
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    printf("Method - Normal access:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
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

### Question 14: Short-Circuit Evaluation in Complex Expressions
Predict the output and explain the evaluation order:
```c
#include <stdio.h>
int test1() {
    printf("test1() called ");
    return 0;
}

int test2() {
    printf("test2() called ");
    return 1;
}

int test3() {
    printf("test3() called ");
    return 1;
}

int main() {
    printf("Expression 1: ");
    int result1 = test1() && test2() && test3();
    printf("Result: %d\n", result1);
    
    printf("Expression 2: ");
    int result2 = test3() || test1() || test2();
    printf("Result: %d\n", result2);
    
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

### Question 17: Ternary Operator and Precedence
Analyze these complex ternary expressions:
```c
#include <stdio.h>
int main() {
    int a = 5, b = 10, c = 3;
    
    // Simple ternary
    int max1 = (a > b) ? a : b;
    printf("max1 = %d\n", max1);
    
    // Nested ternary
    int max2 = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    printf("max2 = %d\n", max2);
    
    // Ternary with side effects
    int x = 0;
    int result1 = (x++ > 0) ? x : ++x;
    printf("x after result1: %d, result1: %d\n", x, result1);
    
    // Complex ternary with logical operators
    int y = 5, z = 0;
    int result2 = (y && z) ? (y + z) : (y || z) ? y : z;
    printf("result2 = %d\n", result2);
    
    // Ternary operator precedence
    int result3 = a > b ? a : b > c ? b : c;
    printf("result3 = %d\n", result3);
    
    return 0;
}
```

### Question 18: Character-by-Character Processing
What will this string processing code output?

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char text[] = "Hello World 123!";
    int letters = 0, digits = 0, spaces = 0, others = 0;
    
    printf("Original: '%s'\n", text);
    printf("Processing each character:\n");
    
    for (int i = 0; text[i] != '\0'; i++) {
        printf("text[%d] = '%c' (%d) - ", i, text[i], text[i]);
        
        if (isalpha(text[i])) {
            letters++;
            printf("Letter");
        } else if (isdigit(text[i])) {
            digits++;
            printf("Digit");
        } else if (isspace(text[i])) {
            spaces++;
            printf("Space");
        } else {
            others++;
            printf("Other");
        }
        printf("\n");
    }
    
    printf("Summary: %d letters, %d digits, %d spaces, %d others\n", 
           letters, digits, spaces, others);
    
    return 0;
}
```


### Question 19: String Reversal
What will be the output? Explain the reversal algorithm:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Programming";
    char reversed[50];
    int len = strlen(str);
    
    printf("Original: '%s' (length: %d)\n", str, len);
    
    // Method 1: Copy in reverse order
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    
    printf("Reversed (copy): '%s'\n", reversed);
    
    // Method 2: In-place reversal
    char str2[] = "Programming";
    for (int i = 0; i < len / 2; i++) {
        char temp = str2[i];
        str2[i] = str2[len - 1 - i];
        str2[len - 1 - i] = temp;
    }
    
    printf("Reversed (in-place): '%s'\n", str2);
    
    return 0;
}
```

### Question 20: String Pattern Matching
Analyze this simple pattern search implementation:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char text[] = "ababcababa";
    char pattern[] = "abab";
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int matches = 0;
    
    printf("Text: '%s'\n", text);
    printf("Pattern: '%s'\n", pattern);
    printf("Searching for pattern...\n");
    
    for (int i = 0; i <= text_len - pattern_len; i++) {
        int match = 1;
        
        for (int j = 0; j < pattern_len; j++) {
            if (text[i + j] != pattern[j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            matches++;
            printf("Pattern found at position %d: '", i);
            for (int k = i; k < i + pattern_len; k++) {
                printf("%c", text[k]);
            }
            printf("'\n");
        }
    }
    
    printf("Total matches: %d\n", matches);
    
    return 0;
}
```
