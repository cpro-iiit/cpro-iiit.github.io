# Exercise Questions - L-03: Operators, Precedence, Conditionals

## Basic I/O Operations

### Question 1: Simple Output
Write a C program that displays the following message on the screen:
```
Welcome to Computer Programming!
This is Lecture 3.
```

### Question 2: Variable Declaration and Output
Write a C program that:
- Declares variables for storing your name (string), age (integer), and height (float)
- Initializes them with appropriate values
- Prints all three values using printf with proper format specifiers

### Question 3: Reading User Input
Write a C program that:
- Prompts the user to enter their name, age, and favorite character
- Reads these values using scanf
- Displays them back to the user in a formatted manner

## Arithmetic Operations

### Question 4: Basic Calculator
Write a C program that:
- Takes two integers as input from the user
- Performs all arithmetic operations (+, -, *, /, %)
- Displays the results of each operation
- Handle the case where division by zero might occur

### Question 5: Expression Evaluation
Given the following expression, manually calculate the result and then write a C program to verify your answer:
```c
int a = 15, b = 4, c = 3;
int result = a + b * c - a / b + a % b;
```
What will be the value of `result`?

### Question 6: Area and Perimeter Calculator
Write a C program that:
- Takes length and width of a rectangle as input
- Calculates and displays the area and perimeter
- Use appropriate data types for decimal values

## Assignment Operations and Swapping

### Question 7: Variable Swapping
Write a C program that swaps the values of two variables:
- Method 1: Using a temporary variable (as shown in the lecture)
- Method 2: Without using a temporary variable (using arithmetic operations)
- Method 3: Without using a temporary variable (using XOR operation)

### Question 8: Circular Swapping
Write a C program that performs circular swapping of three variables.
For example: if a=10, b=20, c=30, after swapping: a=30, b=10, c=20

### Question 9: Assignment Chain
What will be the final values of variables x, y, and z after executing the following code?
```c
int x = 5, y = 10, z = 15;
x = y = z = 20;
x = x + y;
y = y - z;
z = x * y;
```

## Conditional Statements

### Question 10: Even or Odd
Write a C program that:
- Takes an integer as input
- Determines whether the number is even or odd
- Displays the appropriate message

### Question 11: Age Category
Write a C program that categorizes a person based on their age:
- Child (0-12 years)
- Teenager (13-19 years)
- Adult (20-59 years)
- Senior Citizen (60+ years)
- Handle invalid age inputs (negative numbers)

### Question 12: Simple Calculator with Menu
Write a C program that:
- Displays a menu with arithmetic operations
- Takes two numbers and an operation choice as input
- Performs the selected operation using if-else statements
- Displays the result

## Nested Conditionals

### Question 13: Grade Calculator Enhancement
Complete and improve the grade calculation program from `main-1.c`:
- Fix any syntax errors in the provided code
- Add validation for marks (0-100 range)
- Add more detailed grade descriptions
- Handle invalid input gracefully

### Question 14: Triangle Classification
Write a C program that:
- Takes three sides of a triangle as input
- First checks if the sides can form a valid triangle
- If valid, classifies the triangle as:
  - Equilateral (all sides equal)
  - Isosceles (two sides equal)
  - Scalene (no sides equal)

### Question 15: Quadratic Equation Solver
Write a C program that solves quadratic equations (ax² + bx + c = 0):
- Take coefficients a, b, c as input
- Calculate discriminant (b² - 4ac)
- Use nested if-else to determine:
  - Two distinct real roots (discriminant > 0)
  - One repeated real root (discriminant = 0)
  - No real roots (discriminant < 0)
- Display appropriate messages for each case

## Operator Precedence

### Question 16: Precedence Challenge 1
Without using a compiler, determine the output of the following expressions:
```c
int a = 12, b = 4, c = 2;
printf("%d\n", a + b * c);
printf("%d\n", (a + b) * c);
printf("%d\n", a / b + c);
printf("%d\n", a % b * c);
printf("%d\n", a + b / c * a);
```

### Question 17: Precedence Challenge 2
What will be the final value of x after executing each line?
```c
int x = 10;
x = x + 5 * 2;        // x = ?
x = x * 2 + 3;        // x = ?
x = x / 4 + 1;        // x = ?
x = x % 3 + 2;        // x = ?
```

### Question 18: Complex Expression
Write a C program that evaluates the following mathematical expression:
**result = (a + b) × (c - d) / (e + f) + g % h**

Where all variables are integers input by the user. Handle division by zero appropriately.

## Comments and Code Documentation

### Question 19: Code Documentation
Add appropriate single-line and multi-line comments to the following code:
```c
#include <stdio.h>
int main() {
    int num1, num2, temp;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    printf("Numbers in ascending order: %d %d\n", num1, num2);
    return 0;
}
```

## Debugging Exercises

### Question 20: Find the Errors
Identify and fix the errors in the following code snippets:

**Code Snippet A:**
```c
#include <stdio.h>
int main() {
    int age;
    printf("Enter your age: ");
    scanf("%d" &age);
    if age >= 18
        printf("You are an adult");
    else
        printf("You are a minor");
    return 0;
}
```

**Code Snippet B:**
```c
#include <stdio.h>
int main() {
    int marks = 85;
    if (marks >= 90 && marks <= 100)
        printf("Grade A");
    else if (marks >= 80)
        printf("Grade B");
    else if (marks >= 70)
        printf("Grade C");
    else if (marks >= 60)
        printf("Grade D");
    else
        printf("Grade F");
    // Missing return statement and braces for clarity
}
```

## Challenge Problems

### Question 21: BMI Calculator
Write a C program that:
- Takes height (in meters) and weight (in kg) as input
- Calculates BMI using the formula: BMI = weight / (height × height)
- Categorizes BMI as:
  - Underweight (< 18.5)
  - Normal weight (18.5 - 24.9)
  - Overweight (25 - 29.9)
  - Obese (≥ 30)

### Question 22: Electricity Bill Calculator
Write a C program to calculate electricity bill based on the following rates:
- First 100 units: ₹2 per unit
- Next 200 units: ₹3 per unit
- Above 300 units: ₹5 per unit
- Add 10% tax on the total bill

### Question 23: Number Properties Analyzer
Write a C program that takes a 3-digit number and:
- Checks if it's a palindrome
- Finds the sum of its digits
- Determines if the sum is even or odd
- Checks if the original number is divisible by the sum of its digits

## Programming Best Practices

### Question 24: Code Improvement
Rewrite the following code using better practices:
```c
#include<stdio.h>
int main(){
int x,y;scanf("%d%d",&x,&y);
if(x>y)printf("x is greater");else printf("y is greater");
return 0;
}
```

Improve it by:
- Adding proper spacing and indentation
- Adding meaningful variable names
- Adding comments
- Handling the case where x equals y
- Adding user-friendly prompts


