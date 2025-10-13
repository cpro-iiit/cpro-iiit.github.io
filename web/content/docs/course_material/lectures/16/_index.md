---
title: "L16: Dynamic Memory Allocation "
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---



# Dynamic Memory Allocation   

---

## What is Dynamic Memory Allocation?

Dynamic memory allocation allows programs to **request memory at runtime** rather than compile time.

Used when:
- The amount of data is not known beforehand.
- Data structures need to grow or shrink during execution.

---

## Why Not Static Allocation?

| Static Memory | Dynamic Memory |
|----------------|----------------|
| Size fixed at compile time | Size determined at runtime |
| Allocated on stack | Allocated on heap |
| Automatically freed | Must be freed manually |
| Limited size | Flexible and scalable |

---

## Functions in `<stdlib.h>`

| Function | Description |
|-----------|--------------|
| `malloc(size)` | Allocates uninitialized memory |
| `calloc(n, size)` | Allocates and zero-initializes memory |
| `realloc(ptr, size)` | Changes the size of an existing allocation |
| `free(ptr)` | Frees allocated memory |

---

## 🧩 Example 1: Using `malloc()`

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) arr[i] = i * i;

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    free(arr);
    return 0;
}
```

✅ Allocates memory for `n` integers on the heap.

---

## 🧩 Example 2: `calloc()` for Zero Initialization

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    free(arr);
}
```

✅ `calloc()` ensures all elements are initialized to 0.

---

## 🧩 Example 3: `realloc()` for Resizing

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) arr[i] = i + 1;

    arr = realloc(arr, 5 * sizeof(int));
    arr[3] = 4; arr[4] = 5;

    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    free(arr);
}
```

✅ Expands or shrinks a previously allocated block.

---

## 🔹 Common Use Case 1: Dynamic Arrays

When user input size is unknown at compile time.

```c
int *arr = malloc(n * sizeof(int));
```

---

## 🔹 Common Use Case 2: Social Networks

Different people can have different number of friends. So we need something like a 2d array with different rows having different sizes.

```c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[10];
    // friends is an array of person pointers
    struct Person** friends; 
    int num_friends;
} Person;

int main() {

  Person* a = malloc(sizeof(Person));
  strcpy(a->name, "Alice");
  
  Person* b = malloc(sizeof(Person));
  strcpy(b->name, "Bob");
  
  Person* c = malloc(sizeof(Person));
  strcpy(c->name, "Charlie");
  
  Person* d = malloc(sizeof(Person));
  strcpy(c->name, "Diestel");
  
  // a has 2 friends: b, c
  a->friends = malloc(2*sizeof(Person*));
  a->friends[0] = b;
  a->friends[1] = c;
  a->num_friends = 2;
  
  // b has 2 friends: c, a
  b->friends = malloc(2*sizeof(Person*));
  b->friends[0] = c;
  b->friends[1] = a;
  b->num_friends = 2;
  
  // c has 1 friend: d
  c->friends = malloc(1*sizeof(Person*));
  c->friends[0] = d;
  c->num_friends = 1;
  
  // d has no friends
  d->friends = NULL;
  d->num_friends = 0;

  return 0;
}


```
[Pythontutor](https://pythontutor.com/render.html#code=%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%23include%20%3Cstring.h%3E%0A%0Atypedef%20struct%20Person%20%7B%0A%20%20%20%20char%20name%5B10%5D%3B%0A%20%20%20%20//%20friends%20is%20an%20array%20of%20person%20pointers%0A%20%20%20%20struct%20Person**%20friends%3B%20%0A%20%20%20%20int%20num_friends%3B%0A%7D%20Person%3B%0A%0Aint%20main%28%29%20%7B%0A%0A%20%20Person*%20a%20%3D%20malloc%28sizeof%28Person%29%29%3B%0A%20%20strcpy%28a-%3Ename,%20%22Alice%22%29%3B%0A%20%20%0A%20%20Person*%20b%20%3D%20malloc%28sizeof%28Person%29%29%3B%0A%20%20strcpy%28b-%3Ename,%20%22Bob%22%29%3B%0A%20%20%0A%20%20Person*%20c%20%3D%20malloc%28sizeof%28Person%29%29%3B%0A%20%20strcpy%28c-%3Ename,%20%22Charlie%22%29%3B%0A%20%20%0A%20%20Person*%20d%20%3D%20malloc%28sizeof%28Person%29%29%3B%0A%20%20strcpy%28c-%3Ename,%20%22Diestel%22%29%3B%0A%20%20%0A%20%20a-%3Efriends%20%3D%20malloc%282*sizeof%28Person*%29%29%3B%0A%20%20a-%3Efriends%5B0%5D%20%3D%20b%3B%0A%20%20a-%3Efriends%5B1%5D%20%3D%20c%3B%0A%20%20a-%3Enum_friends%20%3D%202%3B%0A%20%20%0A%20%20%0A%20%20b-%3Efriends%20%3D%20malloc%282*sizeof%28Person*%29%29%3B%0A%20%20b-%3Efriends%5B0%5D%20%3D%20c%3B%0A%20%20b-%3Efriends%5B1%5D%20%3D%20a%3B%0A%20%20b-%3Enum_friends%20%3D%202%3B%0A%20%20%0A%20%20c-%3Efriends%20%3D%20malloc%281*sizeof%28Person*%29%29%3B%0A%20%20c-%3Efriends%5B0%5D%20%3D%20d%3B%0A%20%20c-%3Enum_friends%20%3D%201%3B%0A%20%20%0A%20%20d-%3Efriends%20%3D%20NULL%3B%0A%20%20d-%3Enum_friends%20%3D%200%3B%0A%0A%20%20return%200%3B%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)

💡 Used in:
- Dynamic table storage
- Graph adjacency matrices
- Image data buffers



---

## 🔹 Common Use Case 3: Linked Lists

Each node is created dynamically to store data. Data can be stored in different memory locations without needing to be contigous. 

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {

    // Linkedlist in Stack
    // Node a, b, c;
    // a.data = 1;
    // a.next = &b;
    // b.data = 2;
    // b.next = &c;
    // c.data = 3;
    // c.next = NULL;
    
    // LinkedList in Heap
    
    Node* a = malloc(sizeof(Node));
    Node* b = malloc(sizeof(Node));
    Node* c = malloc(sizeof(Node));
    a->data = 1;
    a->next = b;
    b->data = 2;
    b->next = c;
    c->data = 3;
    c->next = NULL;
    
    
    return 0;
}
```

[pythontutor](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0Atypedef%20struct%20Node%20%7B%0A%20%20%20%20int%20data%3B%0A%20%20%20%20struct%20Node*%20next%3B%0A%7D%20Node%3B%0A%0Aint%20main%28%29%20%7B%0A%0A%20%20%20%20//%20Linkedlist%20in%20Stack%0A%20%20%20%20//%20Node%20a,%20b,%20c%3B%0A%20%20%20%20//%20a.data%20%3D%201%3B%0A%20%20%20%20//%20a.next%20%3D%20%26b%3B%0A%20%20%20%20//%20b.data%20%3D%202%3B%0A%20%20%20%20//%20b.next%20%3D%20%26c%3B%0A%20%20%20%20//%20c.data%20%3D%203%3B%0A%20%20%20%20//%20c.next%20%3D%20NULL%3B%0A%20%20%20%20%0A%20%20%20%20//%20LinkedList%20in%20Heap%0A%20%20%20%20%0A%20%20%20%20Node*%20a%20%3D%20malloc%28sizeof%28Node%29%29%3B%0A%20%20%20%20Node*%20b%20%3D%20malloc%28sizeof%28Node%29%29%3B%0A%20%20%20%20Node*%20c%20%3D%20malloc%28sizeof%28Node%29%29%3B%0A%20%20%20%20a-%3Edata%20%3D%201%3B%0A%20%20%20%20a-%3Enext%20%3D%20b%3B%0A%20%20%20%20b-%3Edata%20%3D%202%3B%0A%20%20%20%20b-%3Enext%20%3D%20c%3B%0A%20%20%20%20c-%3Edata%20%3D%203%3B%0A%20%20%20%20c-%3Enext%20%3D%20NULL%3B%0A%20%20%20%20%0A%20%20%20%20%0A%20%20%20%20return%200%3B%0A%7D&cumulative=false&curInstr=10&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)

---



## ⚠️ Memory Management Best Practices

✅ Always check if `malloc()` returned `NULL`.  
✅ Always `free()` memory after use.  
✅ Avoid **memory leaks** and **dangling pointers**.  
✅ Use tools like Valgrind to detect leaks.

---

## 🚫 Common Errors

| Error | Cause |
|--------|--------|
| Segmentation fault | Using uninitialized or freed pointer |
| Memory leak | Forgetting to call `free()` |
| Double free | Freeing the same pointer twice |
| Buffer overflow | Writing beyond allocated memory |

---

## 🧠 Summary

| Function | Use | Key Point |
|-----------|-----|------------|
| `malloc()` | Allocate memory | Uninitialized memory |
| `calloc()` | Allocate + zero initialize | Slower, safer |
| `realloc()` | Resize memory | Retains old data |
| `free()` | Release memory | Must call manually |

---

## 💡 Exercises

1. Implement a dynamically growing array that doubles in size.
2. Create a linked list of student records using dynamic memory.
3. Write a function to dynamically allocate a 2D array.
4. Simulate dynamic allocation of memory for a tree.

---

## 🏁 Takeaway

> Dynamic memory makes C powerful — but with great power comes great responsibility.

Always pair every `malloc()` with a matching `free()`!


---

## References

- [https://www.cs.cmu.edu/~guna/15-123S11/Lectures/Lecture08.pdf](https://www.cs.cmu.edu/~guna/15-123S11/Lectures/Lecture08.pdf)
- [https://web.eecs.utk.edu/~bvanderz/teaching/cs140fa08/labs/lab1/cs102/malloc.html](https://web.eecs.utk.edu/~bvanderz/teaching/cs140fa08/labs/lab1/cs102/malloc.html)
- [Section 6.8 in the book linked](https://karadev.net/uroci/filespdf/files/a%20book%20on%20c.pdf)