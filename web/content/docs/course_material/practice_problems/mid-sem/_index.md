---
title: "Mid-Sem Practice Problems"
bookHidden: false
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:100px](IIIT_Hyderabad_Logo.jpg)'
---

# Mid Semester Practice Questions

This practice set is in continuation of previous quiz-1 problem set and starts from Lecture-06 Strings and Arrays


### Question 1: 
```c
#include <stdio.h>
int main() {
    int marks[5] = {90, 85, 88, 92, 88};
    for (int i = 0; i <= 5; i++) {
        printf("%d ", marks[i]);
    }
    return 0;
}
```
**What will happen when this code runs? Identify the error and explain why it occurs.**

### Question 2: 
```c
#include <stdio.h>
int main() {
    char name1[5] = "Alice";
    char name2[5] = {'A','l','i','c','e'};
    printf("Length of name1: %lu\n", strlen(name1));
    printf("Length of name2: %lu\n", strlen(name2));
    return 0;
}
```
**Predict the output. What is the difference between the two string initializations?**


### Question 3: 
```c
#include <stdio.h>
int main() {
    char x = 127;
    char y = 1;
    char result = x + y;
    printf("x = %d, y = %d, result = %d\n", x, y, result);
    return 0;
}
```
**What will be the output? Explain what happens during the addition in terms of two's complement representation.**

### Question 4: 
```c
#include <stdio.h>
int main() {
    int a = 12, b = 7;  // a = 1100, b = 0111 in binary
    printf("a & b = %d\n", ____);  // AND operation
    printf("a | b = %d\n", ____);  // OR operation  
    printf("a ^ b = %d\n", ____);  // XOR operation
    printf("a << 2 = %d\n", ____); // Left shift by 2
    return 0;
}
```
**Fill in the blanks with the expected output values and show your binary calculations.**


### Question 5: 
```c
#include <stdio.h>
int main() {
    float sum = 0.0f;
    for(int i = 0; i < 10; i++) {
        sum += 0.1f;
    }
    if(sum == 1.0f) {
        printf("Equal\n");
    } else {
        printf("Not Equal: %.10f\n", sum);
    }
    return 0;
}
```
**What will be the output and why does this happen? How would you fix this comparison?**

### Question 6:  
```c
#include <stdio.h>
int main() {
    int x = 0, y = 5;
    if(x++ > 0 && y++ > 3) {
        printf("Inside if\n");
    }
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
```
**What values will x and y have at the end? Explain the short-circuit evaluation behavior.**


### Question 7:  
```c
#include <stdio.h>
#include <string.h>
int main() {
    char dest[5];
    char src[] = "Programming";
    strcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}
```
**What error will occur when this code runs? How would you fix it using strncpy?**


### Question 8: 
```c
#include <stdio.h>
int gcd(int a, int b) {
    printf("gcd(%d, %d)\n", a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}
int main() {
    int result = gcd(24, 16);
    printf("Result: %d\n", result);
    return 0;
}
```
**Trace through the recursive calls. What will be printed step by step?**

### Question 9: 
```c
#include <stdio.h>
void selectionSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int minIndex = i;
        for(int j = ____; j < ____; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap elements
        int temp = arr[i];
        arr[i] = ____;
        arr[minIndex] = ____;
    }
}
```
**Fill in the blanks to complete the selection sort implementation.**


### Question 10: 
```c
#include <stdio.h>
int binarySearch(int arr[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == key) return mid;
    else if (arr[mid] > key)
        return binarySearch(arr, low, mid - 1, key);
    else
        return binarySearch(arr, mid + 1, high, key);
}
int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int result = binarySearch(arr, 0, 4, 6);
    printf("Result: %d\n", result);
    return 0;
}
```
**What will be the output when searching for 6? Trace through the recursive calls.**

### Question 11:    
```c
#include <stdio.h>
int count = 0;
int fibonacci(int n) {
    count++;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}
int main() {
    int result = fibonacci(5);
    printf("F(5) = %d, Function calls: %d\n", result, count);
    return 0;
}
```
**What will be the output? Why is this implementation inefficient for large values of n?**


### Question 12: 
```c
#include <stdio.h>
int moves = 0;
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        moves++;
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n-1, from, aux, to);
    moves++;
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n-1, aux, to, from);
}
int main() {
    hanoi(3, 'A', 'C', 'B');
    printf("Total moves: %d\n", moves);
    return 0;
}
```
**How many total moves will be printed for 3 disks? Can you derive the formula for n disks?**


### Question 13: 
```c
#include <stdio.h>
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    // What's missing here?
    // Fill in the blanks:
    while (i < n1) arr[k++] = ____;
    while (j < n2) arr[k++] = ____;
}
```
**Fill in the missing code. What happens if these lines are omitted?**


### Question 14: 
```c
#include <stdio.h>
int factorial(int n) {
    printf("Computing factorial(%d)\n", n);
    if (n = 1) return 1;  
    return n * factorial(n - 1);
}
int main() {
    int result = factorial(5);
    printf("Result: %d\n", result);
    return 0;
}
```
**What is wrong with this code? What will happen when it runs and why?**

### Question 15: 
```c
#include <stdio.h>
void generateBinary(int n, char str[], int pos) {
    if (pos == n) {
        str[n] = '\0';
        printf("%s\n", str);
        return;
    }
    
    str[pos] = '0';
    generateBinary(n, str, pos + 1);
    
    str[pos] = '1';
    generateBinary(n, str, pos + 1);
}
int main() {
    char str[10];
    generateBinary(3, str, 0);
    return 0;
}
```
**What will be the complete output? How many binary strings will be printed and in what order?**

### Question 16: 
```c
#include <stdio.h>
int power(int base, int exp) {
    if (exp == 0) return ____;
    if (exp == 1) return ____;
    
    if (exp % 2 == 0) {
        int half = power(base, ____);
        return half * half;
    } else {
        return base * power(base, ____);
    }
}
int main() {
    printf("2^8 = %d\n", power(2, 8));
    printf("3^5 = %d\n", power(3, 5));
    return 0;
}
```
**Fill in the blanks to complete this optimized recursive power function.**

### Question 17: 
```c
#include <stdio.h>
int arraySum(int arr[], int n) {
    if (n <= 0) return 0;
    return arr[n] + arraySum(arr, n - 1);  
}
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int result = arraySum(arr, 5);
    printf("Sum = %d\n", result);
    return 0;
}
```
**What is the error in this recursive sum function? What would be the incorrect result?**

### Question 18: Binary Strings with Exactly k Ones
**Problem Statement:** Write a recursive program that prints all binary strings of length n with exactly k ones.

**Example 1:**
- Input: n = 3, k = 2
- Output: 
  ```
  011
  101
  110
  ```

**Example 2:**
- Input: n = 4, k = 1
- Output:
  ```
  0001
  0010
  0100
  1000
  ```

### Question 19: All Permutations of Numbers 1 to n
**Problem Statement:** Write a recursive program that prints all permutations of numbers from 1 to n.

**Example 1:**
- Input: n = 3
- Output:
  ```
  1 2 3
  1 3 2
  2 1 3
  2 3 1
  3 1 2
  3 2 1
  ```

**Example 2:**
- Input: n = 2
- Output:
  ```
  1 2
  2 1
  ```

### Question 20: Balanced Parentheses Strings
**Problem Statement:** Write a recursive program that prints all balanced parentheses strings of length 2n.

**Example 1:**
- Input: n = 2
- Output:
  ```
  (())
  ()()
  ```

**Example 2:**
- Input: n = 3
- Output:
  ```
  ((()))
  (()())
  (())()
  ()(())
  ()()()
  ```

### Question 21: All Subsets of n Distinct Elements
**Problem Statement:** Take a sequence of n distinct elements as input, and print all subsets of the n element set formed by them.

**Example 1:**
- Input: arr = [1, 2, 3]
- Output:
  ```
  {}
  {1}
  {2}
  {1, 2}
  {3}
  {1, 3}
  {2, 3}
  {1, 2, 3}
  ```

**Example 2:**
- Input: arr = [5, 10]
- Output:
  ```
  {}
  {5}
  {10}
  {5, 10}
  ```

### Question 22: All k-Element Subsets
**Problem Statement:** Take a sequence of n distinct elements and a number k as input, and print all k element subsets of the n element set formed by them.

**Example 1:**
- Input: arr = [1, 2, 3, 4], k = 2
- Output:
  ```
  {1, 2}
  {1, 3}
  {1, 4}
  {2, 3}
  {2, 4}
  {3, 4}
  ```

**Example 2:**
- Input: arr = [5, 10, 15], k = 1
- Output:
  ```
  {5}
  {10}
  {15}
  ```

### Question 23: Count Subsets with Sum k
**Problem Statement:** Given an array, count the number of subsets whose elements add up to k (return the count, don't print the subsets).

**Example 1:**
- Input: arr = [1, 2, 3, 4], k = 5
- Output: 2
- Explanation: Subsets {1, 4} and {2, 3} both sum to 5

**Example 2:**
- Input: arr = [2, 4, 6, 8], k = 10
- Output: 2
- Explanation: Subsets {2, 8} and {4, 6} both sum to 10

**Example 3:**
- Input: arr = [1, 1, 1, 1], k = 2
- Output: 6
- Explanation: Any combination of exactly 2 ones from the 4 available ones
