---
title: "L19: Pointer Quirks & Practice Problems"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 25)'

revealjs_config:
  slideNumber: true
---
# Pointer Quirks

- Pointer to Pointers
- Pointers and Multidim Arrays
- Array of Pointers
- Deep/Shallow Copy of Structures
- Advanced Problems

---

## Pointer to Pointer


---

### 🟢 Level 1 — Basic Double Pointer
```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;
    int **q = &p;

    printf("%d %d %d\n", a, *p, **q);
    return 0;
}
```

---

### 🟢 Level 2 — Changing Value Through Double Pointer
```c
#include <stdio.h>

int main() {
    int a = 5;
    int *p = &a;
    int **q = &p;

    **q = 20;
    printf("%d\n", a);
    return 0;
}
```

---

### 🟡 Level 3 — Pointer Reassignment
```c
#include <stdio.h>

int main() {
    int x = 5, y = 10;
    int *p = &x;
    int **q = &p;

    *q = &y;
    **q = 25;

    printf("%d %d\n", x, y);
    return 0;
}
```

---

## Multidimensional Arrays

---

### 🧩  Pointer to Pointer Confusion (Predict the Output)
Problem:

Predict the output of the following code:
```c
#include <stdio.h>
int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int *p[2] = {a[0], a[1]};
    int **q = p;
    printf("%d ", **q);
    printf("%d ", *(*(q + 1) + 1));
    return 0;
}
```

Output: ?

---

### Mix of 2D Arrays and Double Pointers (Hard)
Problem:

Consider the code:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int *p[3];
    for (int i = 0; i < 3; i++) p[i] = a[i];
    int **q = p;

    printf("%d ", *(*(q + 1) + 2));
    printf("%d ", *(*(a + 2) + 0));
    return 0;
}
```

Predict the output.


---

## Array of Pointers

---


### 🟡 Level 4 — Array of Pointers and Pointer to Pointer
```c
#include <stdio.h>

int main() {
    int a = 1, b = 2, c = 3;
    int *arr[] = {&a, &b, &c};
    int **p = arr;

    printf("%d ", **p);
    p++;
    printf("%d ", **p);
    p++;
    printf("%d\n", **p);
    return 0;
}
```

---

### 🟠 Level 5 — Pointer Arithmetic on Double Pointer
```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int *arr[] = {&a, &b, &c};
    int **ptr = arr;

    *(*ptr + 0) = 15;
    ptr++;
    **ptr = 25;

    printf("%d %d %d\n", a, b, c);
    return 0;
}
```

---

## Structure Assignments and Shallow Copy


---


## 📘 What is a Shallow Copy?
A **shallow copy** of a structure means copying all fields **bit by bit** (a member-wise copy).  
If a structure contains **pointer members**, only the **addresses** (not the data they point to) are copied.

---

## 🧱 Example 1: Simple Structure Copy

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
} Student;

int main() {
    Student s1 = {1, "Alice"};
    Student s2 = s1;  // Shallow copy

    strcpy(s2.name, "Bob");

    printf("s1: %d %s\n", s1.id, s1.name);
    printf("s2: %d %s\n", s2.id, s2.name);
    return 0;
}
```
### 🧩 Output
```
s1: 1 Alice
s2: 1 Bob
```
👉 Each struct has its own `name` array, so this copy is **safe**.

---

## ⚠️ Example 2: Shallow Copy with Pointers

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
} Student;

int main() {
    Student s1;
    s1.id = 1;
    s1.name = malloc(20);
    strcpy(s1.name, "Alice");

    Student s2 = s1;   // Shallow copy

    strcpy(s2.name, "Bob");

    printf("s1: %d %s\n", s1.id, s1.name);
    printf("s2: %d %s\n", s2.id, s2.name);

    free(s1.name);
    // free(s2.name);  <-- ⚠️ Double free error!
    return 0;
}
```
### 💥 Output
```
s1: 1 Bob
s2: 1 Bob
```
Both `s1.name` and `s2.name` point to the **same memory** — changing one changes both.

---

## 🧠 Concept Recap

| Operation | What happens | Safe? |
|------------|---------------|-------|
| **Shallow Copy** | Copies memory addresses of pointers | ❌ Unsafe if structs contain pointers |
| **Deep Copy** | Allocates new memory and copies data recursively | ✅ Safe |

---

## 🧩 Example 3: Correct Deep Copy

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
} Student;

void deepCopy(Student *dest, const Student *src) {
    dest->id = src->id;
    dest->name = malloc(strlen(src->name) + 1);
    strcpy(dest->name, src->name);
}

int main() {
    Student s1 = {1, malloc(20)};
    strcpy(s1.name, "Alice");

    Student s2;
    deepCopy(&s2, &s1);

    strcpy(s2.name, "Bob");

    printf("s1: %d %s\n", s1.id, s1.name);
    printf("s2: %d %s\n", s2.id, s2.name);

    free(s1.name);
    free(s2.name);
    return 0;
}
```

### ✅ Output
```
s1: 1 Alice
s2: 1 Bob
```
Now `s1` and `s2` have separate copies of the string.

---

## 💡 When Shallow Copy is Fine
✅ When all fields are **value types** (e.g., `int`, `float`, fixed arrays).  
❌ Avoid when structs contain **pointers or dynamically allocated data**.

---
## 🧩 Example 4 — Nested Structures
```c
typedef struct {
    char *street;
    int number;
} Address;

typedef struct {
    char *name;
    Address *addr;
} Employee;
```

Copying Employee e2 = e1; → shallow copy of addr and name.

Requires deep copy of both pointers to fully clone the structure.

Exercise: Write a function to do a deep copy of Employee structure.

---

## 🧩 Summary Slide

| Type | How it Works | Example |
|------|---------------|----------|
| **Shallow Copy** | Bitwise copy of fields | `struct2 = struct1;` |
| **Deep Copy** | Field-by-field duplication | Use `malloc()` and `strcpy()` |


---

## Advanced Problems


---

### 🔴 Level 6 — Triple Pointer
```c
#include <stdio.h>

int main() {
    int a = 50;
    int *p = &a;
    int **q = &p;
    int ***r = &q;

    ***r = ***r + 10;
    printf("%d\n", a);
    return 0;
}
```

---

### 🔴 Level 7 — Triple Pointer with Reassignment
```c
#include <stdio.h>

int main() {
    int x = 1, y = 2;
    int *p = &x;
    int **q = &p;
    int ***r = &q;

    **q = y;
    y = 10;
    printf("%d %d\n", x, y);
    return 0;
}
```

---

### 🔴 Level 8 — Complex Pointer Indirection
```c
#include <stdio.h>

int main() {
    int a = 3, b = 4;
    int *p = &a;
    int *q = &b;
    int **r = &p;
    *r = q;
    **r = 10;

    printf("%d %d\n", a, b);
    return 0;
}
```

---

### 🔴 Level 9 — Triple Pointer with Arrays
```c
#include <stdio.h>

int main() {
    int a[] = {10, 20, 30};
    int *p = a;
    int **q = &p;
    int ***r = &q;

    **q = *p + 1;
    ***r = **q + 1;

    printf("%d %d %d\n", a[0], a[1], a[2]);
    return 0;
}
```

---

### 🔴 Level 10 — Memory Graph Puzzle
```c
#include <stdio.h>

int main() {
    int a = 5, b = 6, c = 7;
    int *p1 = &a, *p2 = &b;
    int **q1 = &p1, **q2 = &p2;
    int ***r = &q1;

    **q2 = **q1 + 2;
    *r = q2;
    ***r = ***r + 3;

    printf("%d %d %d\n", a, b, c);
    return 0;
}
```

---

### Efficient storage for Lower Triangular Matrices

The bellow code store lower triangular matrices with only n(n-1)/2 memory.  Fill in the code for multiplying and deleting lower triangular matrices.

```c
#include <stdio.h>
#include <stdlib.h>

// structure for storing a lower triangular
// matrix with only n(n-1)/2 memory
typedef struct LTMatrix {
    int** mat;
    int num_rows;
    int num_cols;    
} LTMatrix;

// Explain why this function only allocates n(n-1)/2 memory
// for storing lower triangular matrices
LTMatrix* create_LTMatrix(int n, int m, int* init) {
    LTMatrix* M = malloc(sizeof(LTMatrix));
    M->num_rows = n;
    M->num_cols = m;
    M->mat = malloc(n*sizeof(int*));
    int k = 0;
    for (int i =0; i < n; i++) {
        if (i < m) {
            M->mat[i] = malloc(i*sizeof(int));
            if (init != NULL)
                for (int j = 0; j <= i; j++) {
                    M->mat[i][j] = init[k++];
                }
        } else { 
            M->mat[i] = malloc(m*sizeof(int));
            if (init != NULL)
                for (int j = 0; j < m; j++) {
                    M->mat[i][j] = init[k++];
                }
        }
    }
    return M;
}

void print_LTMatrix(LTMatrix* M) {
    printf("-- matrix --\n");
    for (int i = 0; i < M->num_rows; i++) {
        for (int j = 0; j < M->num_cols; j++) {
            printf("%d ", M->mat[i][j]);
        }
        printf("\n");
    }
    printf("-- end --\n");
}

// This function should multiply the
// lower triangular matrices A, B (if the dimensions are approriate)
// and return a newly created LTMatrix which has the result
LTMatrix* multiply_LTMatrix(LTMatrix* A, LTMatrix* B) {
	// TODO
}

// This function should free up all memory corresponding to 
// a LTMatrix
void delete_LTMatrix(LTMatrix* A) {
	// TODO
}

int main() {
    int matrix[6] = {1,
                     2,3,
                     4,5,6};
    LTMatrix* M = create_LTMatrix(3, 3, matrix);
    print_LTMatrix(M);

    return 0;
}
```

---

# C Memory & Pointer Puzzle Set 

Predict the output of the programs

---

## Level 1: Single Pointer Basics (Easy)

### Problem 1: Basic pointer

```c
#include <stdio.h>
int main() {
    int x = 10;
    int *p = &x;
    printf("%d %d\n", x, *p);
    return 0;
}
```

---

### Problem 2: Pointer modification

```c
#include <stdio.h>
int main() {
    int x = 5;
    int *p = &x;
    *p = 20;
    printf("%d\n", x);
    return 0;
}
```

---

### Problem 3: Pointer arithmetic

```c
#include <stdio.h>
int main() {
    int arr[3] = {1,2,3};
    int *p = arr;
    *(p+1) = 10;
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);
    return 0;
}
```

---

## Level 2: Pointer to Pointer (Medium)

### Problem 4: Double pointer assignment

```c
#include <stdio.h>
int main() {
    int x = 7;
    int *p = &x;
    int **q = &p;
    **q = 15;
    printf("%d %d\n", x, *p);
    return 0;
}
```

---

### Problem 5: Pointer redirection

```c
#include <stdio.h>
int main() {
    int a=1, b=2;
    int *p=&a;
    int **q=&p;
    *q = &b;
    **q = 5;
    printf("%d %d\n", a, b);
    return 0;
}
```

---

### Problem 6: Pointer swap

```c
#include <stdio.h>
void swap(int **x, int **y){
    int *temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int a=1, b=2;
    int *p1=&a, *p2=&b;
    swap(&p1,&p2);
    *p1 = 10;
    *p2 = 20;
    printf("%d %d\n", a, b);
    return 0;
}
```

---

## Level 3: Triple Pointer (Challenging)

### Problem 7: Triple pointer basics

```c
#include <stdio.h>
int main(){
    int x=3;
    int *p=&x;
    int **q=&p;
    int ***r=&q;
    ***r=10;
    printf("%d %d %d\n", x, *p, **q);
    return 0;
}
```

---

### Problem 8: Modifying pointers with triple pointer

```c
#include <stdio.h>
int main(){
    int a=1, b=2;
    int *p=&a, *q=&b;
    int **pp=&p;
    int ***r=&pp;
    
    **r=&b;
    ***r=5;
    printf("%d %d\n", a, b);
    return 0;
}
```

---

### Problem 9: Triple pointer swap

```c
#include <stdio.h>
void swap(int ***x,int ***y){
    int **temp = *x;
    *x = *y;
    *y = temp;
}
int main(){
    int a=1,b=2;
    int *p1=&a,*p2=&b;
    int **pp1=&p1, **pp2=&p2;
    swap(&pp1,&pp2);
    **pp1=10;
    **pp2=20;
    printf("%d %d\n", a,b);
    return 0;
}
```

---

## Level 4: Pointer Arrays (Advanced)

### Problem 10: Array of pointers

```c
#include <stdio.h>
int main(){
    int x=1,y=2,z=3;
    int *arr[3]={&x,&y,&z};
    int **p=arr;
    **p=10;
    p++;
    **p=20;
    printf("%d %d %d\n", x,y,z);
    return 0;
}
```

---

### Problem 11: Array of pointer-to-pointer

```c
#include <stdio.h>
int main(){
    int a=1,b=2;
    int *p=&a,*q=&b;
    int **arr[2]={&p,&q};
    **arr[0]=10;
    **arr[1]=20;
    printf("%d %d\n", a,b);
    return 0;
}
```

---

### Problem 12: Pointer array with triple pointer

```c
#include <stdio.h>
int main(){
    int a=1,b=2,c=3;
    int *p1=&a,*p2=&b,*p3=&c;
    int **arr[3]={&p1,&p2,&p3};
    int ***r=arr;
    ***r=10;
    r++;
    ***r=20;
    printf("%d %d %d\n", a,b,c);
    return 0;
}
```

---

### Problem 13: Pointer array arithmetic

```c
#include <stdio.h>
int main(){
    int x=5,y=6,z=7;
    int *arr[]={&x,&y,&z};
    int **p=arr+1;
    **p=10;
    printf("%d %d %d\n", x,y,z);
    return 0;
}
```

---

## Level 5: Dynamic Memory & Tricky Pointers (Hard)

### Problem 14: Pointer to malloc

```c
#include <stdio.h>
#include <stdlib.h>
int main(){
    int *p = (int*)malloc(sizeof(int));
    *p=10;
    int **q=&p;
    **q=20;
    printf("%d\n", *p);
    free(p);
    return 0;
}
```

---

### Problem 15: Double pointer malloc swap

```c
#include <stdio.h>
#include <stdlib.h>
void swap(int **x,int **y){
    int *temp=*x;
    *x=*y;
    *y=temp;
}
int main(){
    int *a=(int*)malloc(sizeof(int));
    int *b=(int*)malloc(sizeof(int));
    *a=1;*b=2;
    swap(&a,&b);
    printf("%d %d\n", *a,*b);
    free(a); free(b);
    return 0;
}
```

---

### Problem 16: Pointer to pointer array with malloc

```c
#include <stdio.h>
#include <stdlib.h>
int main(){
    int **arr = (int**)malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        arr[i]=(int*)malloc(sizeof(int));
        *arr[i]=i+1;
    }
    **arr=10;
    printf("%d %d %d\n", **arr, *arr[1], *arr[2]);
    for(int i=0;i<3;i++) free(arr[i]);
    free(arr);
    return 0;
}
```

---

### Problem 17: Pointer to pointer to malloc pointer

```c
#include <stdio.h>
#include <stdlib.h>
int main(){
    int *p = (int*)malloc(sizeof(int));
    *p=5;
    int **q=&p;
    int ***r=&q;
    ***r= (int*)malloc(sizeof(int));
    ****r=10;
    printf("%d\n", *p);
    free(*q);
    return 0;
}
```

---

### Problem 18: Function modification via triple pointer

```c
#include <stdio.h>
void f(int ***p){
    ***p = 100;
}
int main(){
    int x=10;
    int *p=&x;
    int **q=&p;
    f(&q);
    printf("%d\n", x);
    return 0;
}
```

---

### Problem 19: Pointer swapping in array

```c
#include <stdio.h>
int main(){
    int a=1,b=2,c=3;
    int *arr[3]={&a,&b,&c};
    int **p=arr;
    int *temp=*p;
    *p=*(p+2);
    *(p+2)=temp;
    printf("%d %d %d\n", a,b,c);
    return 0;
}
```

---

### Problem 20: Complex triple pointer + array

```c
#include <stdio.h>
int main(){
    int x=1,y=2,z=3;
    int *p1=&x,*p2=&y,*p3=&z;
    int **arr[3]={&p1,&p2,&p3};
    int ***r=arr+1;
    ***r= &x;
    **arr[0]= 10;
    **r = 20;
    printf("%d %d %d\n", x,y,z);
    return 0;
}
```
