---
title: "L14: Pointers "
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

# Pointers 

---

## 🧩 What is a Pointer?

A **pointer** is a variable that stores the **memory address** of another variable.

```c
int x = 10;
int *p = &x; // p stores address of x
printf("%d", *p); // prints 10
```

- `&x` gives the **address** of x.
- `*p` gives the **value stored at that address**.

---

## 🧮 Memory Visualization

| Variable | Address | Value |
|-----------|----------|--------|
| x         | 1000     | 10     |
| p         | 2000     | 1000   |

`*p` → value at address 1000 → 10

---

## 🧠 Example 1: Swapping Two Numbers

### ❌ Without Pointers
```c
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
```

`a` and `b` are **copies** of the arguments. The swap doesn’t affect the original numbers.

### ✅ With Pointers
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

```c
int x = 5, y = 10;
swap(&x, &y);
printf("%d %d", x, y); // 10 5 ✅
```

📈 **Runtime & Memory Advantage**
- Only addresses passed → small data movement.
- No extra copies.

---

## Example 2: Passing Arrays to Functions

Arrays are automatically passed by reference (address).

```c
void doubleArray(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] *= 2;
}

int main() {
    int arr[] = {1, 2, 3};
    doubleArray(arr, 3);
}
```

✅ Works directly on the original array.  
✅ No duplication — only base address passed.

---


## Example 3: Returning Multiple Values

Without pointers → only one return value possible.

✅ Using pointers:
```c
void compute(int a, int b, int *sum, int *prod) {
    *sum = a + b;
    *prod = a * b;
}
```

```c
int s, p;
compute(5, 10, &s, &p);
printf("Sum=%d Product=%d", s, p);
```
---


##  Null Pointer?

```c
int *ptr = NULL;
```

- A **null pointer** is a pointer that points to **nothing** — i.e., **memory address 0**.
- It’s a **sentinel value** used to indicate that the pointer isn’t initialized or points to no valid object.
- Trying to **dereference** a null pointer causes a **runtime error**.

✅ **Use case:**  
Initialize pointers to `NULL` to avoid undefined behavior when checking their validity later.

---

## ⚠️ Slide 2: Common Mistake — Dereferencing NULL

```c
int *p = NULL;
printf("%d", *p);  // ❌ Segmentation Fault
```

- Dereferencing a null pointer leads to a **segmentation fault (SIGSEGV)**.
- The operating system prevents access to memory address `0x0`.
- Such crashes are common in unsafe pointer operations.

✅ **Best practice:**  
Always check before dereferencing:
```c
if (p != NULL)
    printf("%d", *p);
```

---

## 💥 Slide 3: Segmentation Faults

A **segmentation fault** occurs when a program tries to access **restricted or invalid memory**.

### Common Causes:
1. Dereferencing a `NULL` pointer  
2. Using an **uninitialized pointer**  
3. Accessing **freed memory**  
4. Writing **out of bounds** of an array  

---

## 🧨 Slide 4: Example — Uninitialized Pointer

```c
int *p;     // Not initialized
*p = 5;     // ❌ Undefined behavior — random memory location
```

- The pointer contains **garbage value**.
- Program may crash or corrupt memory.

✅ Always initialize pointers:
```c
int *p = NULL;
```

---

## 🔐 Slide 5: Security Bugs due to Bad Pointers

| Type | Description | Example |
|------|--------------|----------|
| **Use-after-free** | Accessing memory after it’s freed | Freeing pointer but still dereferencing |
| **Buffer overflow** | Writing outside array bounds | Writing past array end corrupts memory |
| **Dangling pointer** | Pointer to freed/deleted object | Forgetting to set pointer to `NULL` after `free()` |



---

## Pointer Arithmetic

---



## 🧩 1. Pointer Arithmetic

### 📘 Basic Rules
If `p` is a pointer to an element of an array, then:
- `p + 1` points to the **next** element.
- `p - 1` points to the **previous** element.
- Difference of pointers gives the **number of elements** between them.

### 🧮 Example
```c
#include <stdio.h>
int main() {
    int arr[] = {10, 20, 30, 40};
    int *p = arr;
    printf("%d\n", *(p + 2)); // prints 30
    printf("%ld\n", (p + 3) - p); // prints 3
    return 0;
}
```

---

## 🧮 2. Pointer Arithmetic on Arrays

You can iterate through arrays using pointers.

```c
#include <stdio.h>
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;

    for(int i = 0; i < 5; i++)
        printf("%d ", *(ptr + i)); // pointer arithmetic
}
```

✅ Saves overhead of indexing, especially in performance-critical loops.

---

Based on the pointer type, addresses are incremented by appropriate sizes:
```c
#include <stdio.h>
int main() {
  long long x[] = {1,2,3,4,5,6};
  long long* p = x;
  printf("%d\n", sizeof(x[0]));
  int y = p+1;
  char* pc = x;  
  printf("%d %d %d %d\n",p, y, pc, pc+1);
  return 0;
}
```
For a char pointer +1, increments address by 1 and for long long increments by 8!

---

## 🧭 3. Pointer Casting

You can **cast one pointer type to another**, but must be careful with alignment and type sizes.

### ⚙️ Example: Casting between `int*` and `char*`
```c
#include <stdio.h>
int main() {
    int x = 0x12345678;
    char *p = (char*)&x;
    printf("First byte: %x\n", *p); // prints 78 on little-endian
}
```

🧠 **Use case:** Byte-level manipulation, file I/O, or network communication.


---