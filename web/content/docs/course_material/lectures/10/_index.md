---
title: "L10: Recursion and Sorting"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---


## L10: Recursion and Sorting


---


# Euclid’s Algorithm & Recursion  

### Greatest Common Divisor (GCD) in C  

---

## What is GCD?
- **GCD (Greatest Common Divisor)** of two integers `a` and `b`  
  = the largest integer that divides both without remainder.  

Examples:  
- gcd(12, 8) = 4  
- gcd(20, 28) = 4  
- gcd(17, 5) = 1 (they are coprime)  

---

## Euclid’s Algorithm (Concept)
- Based on this property:  
  - `gcd(a, b) = gcd(b, a % b)`  
  - Continue until remainder = 0  
- When `b = 0`, `gcd(a, b) = a`  

---

## Euclid’s Algorithm (Steps)
Find gcd(48, 18):  
1. gcd(48, 18) = gcd(18, 48 % 18) = gcd(18, 12)  
2. gcd(18, 12) = gcd(12, 6)  
3. gcd(12, 6) = gcd(6, 0)  
4. gcd = 6 ✅  

---

## Iterative GCD in C
```c
#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```
---
## Recursive GCD in C
```c
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int x = 48, y = 18;
    printf("GCD of %d and %d is %d\n", x, y, gcd(x, y));
    return 0;
}
```
---

## Dry Run (Recursive Example)

gcd(48, 18):

gcd(48, 18) → gcd(18, 12)

gcd(18, 12) → gcd(12, 6)

gcd(12, 6) → gcd(6, 0)

Return 6 ✅

---

## Ternary Operator


---

## Recursive GCD in C
```c
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int gcd_single_line(int a, int b) {
  return b==0 ? a: gcd_single_line(b, a % b) ;
}
```

---

## Factorial using Ternary operator?

```c
int factorial_single_line(int n) {
  return n==0 ? 1: n * factorial_single_line(n-1); 
}
```

---

# Sorting

arranging elements of an array in ascending or descending order. 
---


## Sorting Algorithms
- Common sorting algorithms:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort, Quick Sort (advanced)  

---


## Selection Sort
- Find the **minimum element** in the unsorted part of the array  
- Swap it with the **first unsorted element**  
- Move boundary forward  
- Repeat until sorted  

---


## Recursive Idea
- Base case: if starting index = last index → done  
- Recursive case:
  1. Find minimum element from `start` to `end`  
  2. Swap with element at `start`  
  3. Recur for subarray `start+1 ... end`  

---

## Recursive Selection Sort in C
```c
#include <stdio.h>

// Find index of minimum element between indices 
int minIndex(int arr[], int index, int n) {
    int min_index = index;
    for (int k = index + 1; k < n; k++) {
      if (arr[k] < arr[min_index]) min_index = k;
    }
    return min_index;
}

// Recursive Selection Sort
void Sort(int arr[], int n, int index) {
    if (index == n) return;  // base case
    // Find minimum element index in subarray
    int k = minIndex(arr, index, n);
    // Swap
    if (k != index) {
        int temp = arr[k];
        arr[k] = arr[index];
        arr[index] = temp;
    }
    // Recur for the rest
    Sort(arr, n, index+1);
}

int main() {
  int a[] = { 6,7,5,4,3,2,1};
  Sort(a, 7, 0);
  return 0;
}
```

---


## Example Walkthrough

Array = [64, 25, 12, 22, 11]

Find min (11), swap with 64 → [11, 25, 12, 22, 64]

Recur on [25,12,22,64] → min=12 → [11,12,25,22,64]

Next → [11,12,22,25,64]

Sorted ✅

---