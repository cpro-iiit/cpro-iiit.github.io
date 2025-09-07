---
title: "Quiz 1 Practice Problems"
bookHidden: True
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:100px](IIIT_Hyderabad_Logo.jpg)'
---


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
