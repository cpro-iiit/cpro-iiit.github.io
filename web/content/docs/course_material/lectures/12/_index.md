---
title: "L12: Recursion and Merge Sort"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 25)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

# Recursion and Sorting III

---


## Towers of Hanoi 
- You have **3 pegs**: Source (A), Auxiliary (B), Destination (C)
- **n disks** of different sizes are stacked on Source peg
- Goal: Move all disks to Destination peg
- Rules:
  1. Only one disk moved at a time
  2. A disk can only be placed on an empty peg or on a larger disk
  3. Disks must maintain order

---

## Recursive Idea
To move `n` disks from A → C using B:
1. Move `n-1` disks from A → B (using C)
2. Move the largest disk from A → C
3. Move `n-1` disks from B → C (using A)

---


## Example for 3 Disks
1. Move 2 disks from A → B
2. Move disk 3 from A → C
3. Move 2 disks from B → C

Moves:
A → C
A → B
C → B
A → C
B → A
B → C
A → C

---

## C Implementation
```c
#include <stdio.h>

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n - 1, aux, to, from);
}
```
[Pythontutor](https://pythontutor.com/visualize.html#code=%23include%20%3Cstdio.h%3E%0A%0Avoid%20hanoi%28int%20n,%20char%20from,%20char%20to,%20char%20aux%29%20%7B%0A%20%20%20%20if%20%28n%20%3D%3D%201%29%20%7B%0A%20%20%20%20%20%20%20%20printf%28%22Move%20disk%201%20from%20%25c%20to%20%25c%5Cn%22,%20from,%20to%29%3B%0A%20%20%20%20%20%20%20%20return%3B%0A%20%20%20%20%7D%0A%20%20%20%20hanoi%28n%20-%201,%20from,%20aux,%20to%29%3B%0A%20%20%20%20printf%28%22Move%20disk%20%25d%20from%20%25c%20to%20%25c%5Cn%22,%20n,%20from,%20to%29%3B%0A%20%20%20%20hanoi%28n%20-%201,%20aux,%20to,%20from%29%3B%0A%7D%0A%0Aint%20main%28%29%20%7B%0A%20%20%20%20int%20n%20%3D%203%3B%0A%20%20%20%20hanoi%28n,%20'A',%20'C',%20'B'%29%3B%0A%20%20%20%20return%200%3B%0A%7D&cumulative=false&heapPrimitives=nevernest&mode=edit&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)

---

## What is Merge Sort?
- A **Divide and Conquer** sorting algorithm
- Steps:
  1. Divide array into two halves
  2. Recursively sort both halves
  3. Merge the two sorted halves
- **Always O(n log n)** time complexity

---

## Algorithm Outline
1. If array has 0 or 1 elements → already sorted  
2. Otherwise:
   - Divide array into left and right halves
   - Recursively sort each half
   - Merge two sorted halves into one sorted array

---

## Merge Function
```c
// merges the subarrays from indices l to m and m+1 to r
// assumes that the subarrays are sorted
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1; // length of first subarray 
    int n2 = r - m; // length of second subarray

    // create new arrays for the subarrays and copy data there
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // compare the current index elements of L, R and 
    // insert the smaller into the orginal array 'arr'
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    // once one of the subarray is exhausted, copy remaining
    // elements from the other subarray to the orginal array
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
```

---

## Merge Sort Function
```c
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Recursively sort left and right halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge sorted halves
        merge(arr, l, m, r);
    }
}
```
---
Example Dry Run
Array = {12, 11, 13, 5, 6, 7}

Divide → {12, 11, 13} and {5, 6, 7}

Recursively sort:

{12, 11, 13} → {11, 12, 13}

{5, 6, 7} → {5, 6, 7}

Merge:

{11, 12, 13} and {5, 6, 7} → {5, 6, 7, 11, 12, 13}

---

## Visualization of Recursive Calls

```c
mergeSort([12,11,13,5,6,7])
 → mergeSort([12,11,13])
     → mergeSort([12,11])
        → mergeSort([12]) & mergeSort([11])
        → merge([12], [11]) → [11,12]
     → mergeSort([13]) → [13]
     → merge([11,12], [13]) → [11,12,13]
 → mergeSort([5,6,7]) → [5,6,7]
 → merge([11,12,13], [5,6,7]) → [5,6,7,11,12,13]
 ```
 
 ---


## 🔹 Example: Array of 8 Elements
Level 0: Merge 8 elements → 8 units of work  
Level 1: 2 merges of 4 elements → 2 × 4 = 8 units  
Level 2: 4 merges of 2 elements → 4 × 2 = 8 units  
Level 3: 8 merges of 1 element → trivial (no real work)

---

## 🔹 Pattern Observed
- At each level of recursion tree: **total work = n**
- Number of levels = log₂(n) (because array keeps halving)

Example with n = 8:
- Work per level = 8  
- Number of levels = 3 (halving until single elements)

Total work = 8 + 8 + 8 = 24

---

## 🔹 Generalizing
For an array of size n:
- Each level does **n units** of merging work  
- Number of levels ≈ log₂(n)

So total work ≈ n × log₂(n)

---

## 🔹 Why This Matters

- Merge Sort does the **same work** regardless of input order  
- It’s predictable:  
  - n = 8 → about 24 comparisons  
  - n = 16 → about 64 comparisons  
- Much better than insertion/selection sort (which can need n² comparisons)

---

## ✅ Summary
- We counted actual merging steps  
- Each level = n units of work  
- Levels = log₂(n)  
- Total work ≈ n × log₂(n)  
- Merge Sort is efficient and consistent

---