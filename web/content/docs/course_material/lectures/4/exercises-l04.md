# Exercise Questions - L-04: Operators, Precedence, Conditionals, Loops

## Operator Precedence

### Question 1: Precedence Prediction
Predict the output of the following expressions without using a compiler:

```c
#include <stdio.h>
int main() {
    int a = 10, b = 20, c = 3;
    printf("%d\n", a + b * c);           // Expression 1
    printf("%d\n", a * b / c + a);       // Expression 2
    printf("%d\n", a + b % c * a);       // Expression 3
    printf("%d\n", (a + b) * c % a);     // Expression 4
    return 0;
}
```

### Question 2: Complex Expression Evaluation
Given the following code, trace through the execution step by step:

```c
int x = 5, y = 10, z = 2;
int result = x + y * z / x + y % z;
```

What is the final value of `result`? Show your work using operator precedence rules.

### Question 3: Mixed Operators Challenge
Evaluate these expressions manually, then write a C program to verify:

```c
int a = 12, b = 4, c = 3;
printf("%d\n", a / b + c * a % b);
printf("%d\n", a + b * c / a - b);
printf("%d\n", (a + b) % c + a / b);
```

## Enhanced Conditionals

### Question 4: Grade Calculator Enhancement
Improve the grade calculation program from the lecture materials:
- Add input validation (marks should be between 0-100)
- Add grade point calculation (A=4.0, B=3.0, C=2.0, D=1.0, F=0.0)
- Display both letter grade and grade point
- Handle edge cases gracefully

### Question 5: Multi-Condition Age Classifier
Write a C program that classifies a person based on age and additional criteria:
- Child (0-12): Check if school age (6+)
- Teenager (13-19): Check if eligible for driving (16+)
- Adult (20-64): Check if senior adult (50+)
- Senior (65+): Check if super senior (80+)
- Handle invalid ages

### Question 6: Number Properties Analyzer
Write a C program that takes an integer and determines:
- Whether it's positive, negative, or zero
- If positive, whether it's even or odd
- If it's a single digit, double digit, or multi-digit number
- Whether it's divisible by both 3 and 5

## Switch Case Applications

### Question 7: Enhanced Calculator
Create a calculator using switch case that:
- Displays a menu of operations (+, -, *, /, %, ^)
- Takes two numbers and an operator choice
- Performs the calculation using switch case
- Handles division by zero
- Includes power operation (^ for exponentiation)

### Question 8: Day of Week Calculator
Write a C program using switch case that:
- Takes a number (1-7) representing day of week
- Displays the day name
- Also displays whether it's a weekday or weekend
- Shows the next day
- Handles invalid input

### Question 9: Simple Menu System
Create a menu-driven program using switch case:
```
1. Calculate area of circle
2. Calculate area of rectangle  
3. Calculate area of triangle
4. Exit
```
- Each option should perform the respective calculation
- Use appropriate formulas and handle invalid inputs
- Loop back to menu after each operation until user chooses exit

## While Loops

### Question 10: Number Pattern Generator
Write programs using while loops to generate these patterns:

**Pattern A:**
```
1
12
123
1234
12345
```

**Pattern B:**
```
*
**
***
****
*****
```

**Pattern C:**
```
5
4
3
2
1
```

### Question 11: Fibonacci Sequence Enhanced
Based on the Fibonacci program from lecture, create an enhanced version that:
- Takes n as input from user
- Prints first n Fibonacci numbers
- Also calculates and displays the sum of first n Fibonacci numbers
- Handles the case when n <= 0
- Shows the ratio of consecutive Fibonacci numbers

### Question 12: Digital Root Calculator
Write a C program that calculates the digital root of a number:
- Digital root is obtained by repeatedly summing digits until single digit
- Example: 9875 → 9+8+7+5 = 29 → 2+9 = 11 → 1+1 = 2
- Use a while loop for the repeated summing process

## Mathematical Algorithms

### Question 13: Euclid's GCD Implementation
Implement Euclid's GCD algorithm as mentioned in the lecture:
- Take two positive integers as input
- Use the subtraction method: GCD(a,b) = GCD(a-b,b) if a>b
- Continue until both numbers are equal
- Display step-by-step process
- Also implement the modulo version: GCD(a,b) = GCD(b, a%b)

### Question 14: Factorial Calculator
Write a C program to calculate factorial using while loop:
- Take a non-negative integer as input
- Calculate factorial using while loop
- Handle special cases (0! = 1)
- Display the calculation process
- Check for overflow and display appropriate message

### Question 15: Prime Number Checker
Write a C program that:
- Takes a positive integer as input
- Checks if it's prime using a while loop
- Displays all factors if not prime
- Shows the process of checking divisibility

## Advanced Loop Problems

### Question 16: Perfect Number Finder
Write a C program to check if a number is perfect:
- A perfect number equals the sum of its proper divisors
- Example: 6 = 1 + 2 + 3 (proper divisors of 6)
- Find and display all proper divisors
- Determine if the number is perfect, abundant, or deficient

### Question 17: Armstrong Number Checker
Create a program that checks if a number is an Armstrong number:
- Armstrong number: sum of cubes of digits equals the number
- Example: 153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153
- Handle numbers with different digit counts
- Display the calculation process

### Question 18: Number Reversal and Palindrome
Write a C program that:
- Takes an integer as input
- Reverses the number using a while loop
- Checks if the original number is a palindrome
- Displays both original and reversed numbers

## Loop Control and Nested Structures

### Question 19: Multiplication Table Generator
Create a program that:
- Takes a number n as input
- Displays multiplication table for n (1 to 12)
- Uses proper formatting for output
- Asks if user wants another table
- Continues until user chooses to exit

### Question 20: Sum of Series Calculator
Write programs to calculate these series using while loops:

**Series A:** 1 + 2 + 3 + ... + n

**Series B:** 1² + 2² + 3² + ... + n²

**Series C:** 1/1 + 1/2 + 1/3 + ... + 1/n

**Series D:** 1! + 2! + 3! + ... + n!

## Debugging and Code Analysis

### Question 21: Debug the Loops
Find and fix errors in these code snippets:

**Code A:**
```c
#include <stdio.h>
int main() {
    int i = 1;
    while (i <= 10) {
        printf("%d\n", i);
        // Missing increment
    }
    return 0;
}
```

**Code B:**
```c
#include <stdio.h>
int main() {
    int n = 5;
    int factorial = 0;  // Wrong initialization
    while (n > 0) {
        factorial *= n;
        n--;
    }
    printf("%d\n", factorial);
    return 0;
}
```

### Question 22: Code Optimization
Optimize the following code for better performance and readability:

```c
#include <stdio.h>
int main() {
    int num = 100;
    int i = 2;
    int isPrime = 1;
    while (i < num) {  // Inefficient condition
        if (num % i == 0) {
            isPrime = 0;
        }
        i++;
    }
    if (isPrime == 1)
        printf("Prime\n");
    else
        printf("Not Prime\n");
    return 0;
}
```

## Challenge Problems

### Question 23: Number Guessing Game
Create a number guessing game:
- Program generates a random number between 1-100
- User has maximum 7 attempts to guess
- Provide hints: "too high" or "too low"
- Display number of attempts used
- Ask if user wants to play again

### Question 24: Simple Banking System
Create a simple banking menu system:
```
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Display Transaction History
5. Exit
```
- Use switch case for menu handling
- Use loops for continuous operation
- Validate all inputs (no negative amounts, sufficient balance for withdrawal)
- Keep track of transaction count

### Question 25: Pattern Generator Advanced
Create a program that generates this diamond pattern:
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
- Take the size as input from user
- Use nested loops efficiently
- Handle both upper and lower parts of diamond

## Integration Exercises

### Question 26: Comprehensive Number Analyzer
Write a program that takes an integer and provides complete analysis:
- Basic properties (even/odd, positive/negative)
- Number of digits
- Sum of digits and digital root
- Reverse of the number
- Check if palindrome
- Check if prime
- Check if perfect square
- List all factors

### Question 27: Mathematical Series Menu
Create a menu-driven program for mathematical series:
```
1. Fibonacci Series
2. Prime Numbers up to n
3. Factorial Series
4. Armstrong Numbers up to n
5. Perfect Numbers up to n
6. Exit
```
Use appropriate loops and conditionals for each option.

## Code Quality and Best Practices

### Question 28: Code Documentation
Add comprehensive comments to this Fibonacci code:
```c
#include <stdio.h>
int main() {
    int n = 10;
    int i = 1;
    long long c = 0, f = 0, t = 1;
    while (i < n) {
        c = f + t;
        f = t;
        t = c;
        i = i + 1;
        printf("%lld\n", c);
    }
    return 0;
}
```

### Question 29: Input Validation Framework
Create a robust input validation system:
- Function to validate integer input (within range)
- Function to validate positive numbers
- Function to handle invalid character input
- Apply this to any previous exercise

### Question 30: Performance Comparison
Compare the efficiency of different approaches:
- Calculate factorial using while loop vs for loop
- Find prime numbers using different algorithms
- Measure and discuss the differences in approach
