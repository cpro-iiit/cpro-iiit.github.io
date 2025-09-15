---
title: "L11: More Soring and Recursion"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---


# Insertion Sort in C

---

## What is Insertion Sort?
- A simple sorting algorithm
- Works like sorting playing cards in your hand
- Builds the final sorted array **one item at a time**

---

## Algorithm Idea
1. Start from the **second element**  
2. Compare with elements before it  
3. Shift larger elements to the right  
4. Insert the element into the correct position  
5. Repeat until array is sorted  


---

## C Implementation
```c
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

[Pythontutor](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0Avoid%20insertionSort%28int%20arr%5B%5D,%20int%20n%29%20%7B%0A%20%20for%20%28int%20i%20%3D%201%3B%20i%20%3C%20n%3B%20i%2B%2B%29%20%7B%0A%20%20%20%20int%20key%20%3D%20arr%5Bi%5D%3B%0A%20%20%20%20int%20j%20%3D%20i%20-%201%3B%0A%0A%20%20%20%20while%20%28j%20%3E%3D%200%20%26%26%20arr%5Bj%5D%20%3E%20key%29%20%7B%0A%20%20%20%20%20%20%20%20arr%5Bj%20%2B%201%5D%20%3D%20arr%5Bj%5D%3B%0A%20%20%20%20%20%20%20%20j--%3B%0A%20%20%20%20%20%20%7D%0A%20%20%20%20arr%5Bj%20%2B%201%5D%20%3D%20key%3B%0A%20%20%7D%0A%7D%0A%0Avoid%20print_array%28int%20arr%5B%5D,%20int%20size%29%20%7B%0A%20%20for%28int%20i%20%3D%200%3B%20i%20%3C%20size%3B%20i%2B%2B%29%20%7B%0A%20%20%20%20printf%28%22%25d%20%22,%20arr%5Bi%5D%29%3B%0A%20%20%7D%0A%20%20printf%28%22%5Cn%22%29%3B%0A%7D%0A%0Aint%20main%28%29%20%7B%0A%20%20int%20arr%5B%5D%20%3D%20%7B%204,%203,%202,%201%7D%3B%0A%20%20insertionSort%28arr,%204%29%3B%0A%20%20print_array%28arr,%204%29%3B%0A%20%0A%7D&cumulative=false&curInstr=37&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)

---
## Inserstion Sort vs Selection Sort

Suppose the input was sorted, Selection Sort will still do n(n+1)/2 iterations but insertion sort only does n. (Prove this)


For a reverse sorted array, both will do n(n+1)/2 iterations.


---


## What is Binary Search?
- Efficient algorithm for finding an element in a **sorted array**
- Works by repeatedly dividing the search interval in half
- Compare target with the middle element:
  - If equal → found
  - If smaller → search left half
  - If larger → search right half

---

## Algorithm Idea
1. Start with `low = 0`, `high = n-1`
2. Compute `mid = (low + high) / 2`
3. Compare `arr[mid]` with `key`
   - If `arr[mid] == key` → return `mid`
   - If `arr[mid] > key` → search left half
   - Else → search right half
4. Repeat until `low > high`

---

## Recursive Implementation (C)

```c
int binarySearchRec(int arr[], int low, int high, int key) {
    if (low > high) return -1;

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;
    else if (arr[mid] > key)
        return binarySearchRec(arr, low, mid - 1, key);
    else
        return binarySearchRec(arr, mid + 1, high, key);
}
```
[Pythontutor](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0A//%20Recursive%20binary%20search%20function%0Aint%20binarySearch%28int%20arr%5B%5D,%20int%20low,%20int%20high,%20int%20key%29%20%7B%0A%20%20%20%20if%20%28low%20%3E%20high%29%0A%20%20%20%20%20%20%20%20return%20-1%3B%20%20//%20key%20not%20found%0A%0A%20%20%20%20int%20mid%20%3D%20%28low%20%2B%20high%29%20/%202%3B%0A%0A%20%20%20%20if%20%28arr%5Bmid%5D%20%3D%3D%20key%29%0A%20%20%20%20%20%20%20%20return%20mid%3B%20%20//%20key%20found%0A%20%20%20%20else%20if%20%28arr%5Bmid%5D%20%3C%20key%29%0A%20%20%20%20%20%20%20%20return%20binarySearch%28arr,%20mid%20%2B%201,%20high,%20key%29%3B%20//%20search%20right%0A%20%20%20%20else%0A%20%20%20%20%20%20%20%20return%20binarySearch%28arr,%20low,%20mid%20-%201,%20key%29%3B%20//%20search%20left%0A%7D%0A%0Aint%20main%28%29%20%7B%0A%20%20%20%20//%20Test%20Case%201%0A%20%20%20%20int%20arr1%5B%5D%20%3D%20%7B2,%204,%206,%208,%2010,%2012,%2014%7D%3B%0A%0A%20%20%20%20int%20result1%20%3D%20binarySearch%28arr1,%200,%206,%2010%29%3B%0A%20%20%20%20if%20%28result1%20!%3D%20-1%29%0A%20%20%20%20%20%20%20%20printf%28%22Test%20Case%201%3A%20Element%20%25d%20found%20at%20index%20%25d%5Cn%22,%2010,%20result1%29%3B%0A%20%20%20%20else%0A%20%20%20%20%20%20%20%20printf%28%22Test%20Case%201%3A%20Element%20%25d%20not%20found%5Cn%22,%2010%29%3B%0A%0A%20%20%20%20//%20Test%20Case%202%0A%20%20%20%20int%20arr2%5B%5D%20%3D%20%7B5,%2015,%2025,%2035,%2045,%2055%7D%3B%0A%20%20%20%20int%20result2%20%3D%20binarySearch%28arr2,%200,%205,%2020%29%3B%0A%20%20%20%20if%20%28result2%20!%3D%20-1%29%0A%20%20%20%20%20%20%20%20printf%28%22Test%20Case%202%3A%20Element%20%25d%20found%20at%20index%20%25d%5Cn%22,%2020,%20result2%29%3B%0A%20%20%20%20else%0A%20%20%20%20%20%20%20%20printf%28%22Test%20Case%202%3A%20Element%20%25d%20not%20found%5Cn%22,%2020%29%3B%0A%0A%20%20%20%20return%200%3B%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)
---

## Runtime of Binary Search

Suppose the array is already sorted and we need to check for a single key, runtime of BinarySearch is only $C \log n$ (were C is some constant). (Prove this).

Runtime of linear search is $C n$. 

---

## When to use

If you include the runtime for sorting also, the total runtime for checking if $m$ elements are part of the array is: $n(n+1)/2 + m C \log n$.

For linear search it will be $m n$.

So when $m >> n$ (much larger), sorting + binary search wins.

---

## Example Dry Run
Array: {1, 3, 5, 7, 9, 11, 13}
Search for 7

low=0, high=6 → mid=3 → arr[3]=7 → found at index 3

Search for 6

low=0, high=6 → mid=3 → arr[3]=7 (too big)

low=0, high=2 → mid=1 → arr[1]=3 (too small)

low=2, high=2 → mid=2 → arr[2]=5 (too small)

low=3, high=2 → stop → not found

---


## What is the Fibonacci Sequence?
- Each number is the sum of the two preceding numbers
- Defined as:
  - F(0) = 0
  - F(1) = 1
  - F(n) = F(n-1) + F(n-2), for n ≥ 2

Example sequence:
0, 1, 1, 2, 3, 5, 8, 13, ...

---

## Recursive Definition in C
```c
int fibonacci(int n) {
    if (n == 0) return 0;  // base case
    if (n == 1) return 1;  // base case
    return fibonacci(n-1) + fibonacci(n-2); // recursion
}
```
You can call the same funtion mutliple times in the same line!

---

## Example Trace: F(5)

```c
fibonacci(5)
= fibonacci(4) + fibonacci(3)
= (fibonacci(3) + fibonacci(2)) + (fibonacci(2) + fibonacci(1))
= ...
= 5
```

---

## Tree of calls (partial):

```
            F(5)
          /     \
       F(4)     F(3)
      /   \     /   \
   F(3)  F(2) F(2)  F(1)
   ...
```
Note that same F(3) value that was computed initially was forgotten and we had to recompute it again.

---
