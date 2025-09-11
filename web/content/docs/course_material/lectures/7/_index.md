---
title: "L07: Data Representations"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 25)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---

## L7: Integer Representations
2's completement
Bitwise Operators 

 ---


## Two's Complement Representation

Used to represent signed integers in C.

Positive numbers → same as binary.

Negative numbers → take 2’s complement (invert + add 1).

---

## Two's Complement Example
8-bit system

+5:

00000101


-5:

Start with +5: 00000101

Invert: 11111010

Add 1: 11111011

So, -5 = 11111011₂

---
## Two’s Complement Arithmetic

```c
#include <stdio.h>

int main() {
    char a = 5;   // 00000101
    char b = -5;  // 11111011

    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("a + b = %d\n", a + b); // should be 0
    return 0;
}
```
---

## Two’s Complement – More Examples
Example: Represent -18 in 8 bits

+18 = 00010010

Invert → 11101101

Add 1 → 11101110

So, -18 = 11101110₂

---

## Wrap-Around Example in Two’s Complement

```c
#include <stdio.h>
int main() {
    char c = 127;   // 01111111
    printf("c = %d\n", c);
    c = c + 1;      // Overflow!
    printf("c after +1 = %d\n", c);
}
```
---

## Bitwise Operators in C

- Operate **directly on the bits** of integers.
- Very useful in systems programming, embedded systems, optimization.

**Operators:**
- `&` (AND)  
- `|` (OR)  
- `^` (XOR)  
- `~` (NOT / Complement)  
- `<<` (Left Shift)  
- `>>` (Right Shift)

---

## Bitwise Example

```c
#include <stdio.h>

int main() {
    int a = 6, b = 3;  // a=0110, b=0011

    printf("a & b = %d\n", a & b); // 2
    printf("a | b = %d\n", a | b); // 7
    printf("a ^ b = %d\n", a ^ b); // 5
    printf("~a = %d\n", ~a);       // -7 (2's complement)
    printf("a << 1 = %d\n", a << 1); // 12
    printf("a >> 1 = %d\n", a >> 1); // 3
    return 0;
}
```

---

## Practical Bitwise Example: Check Even/Odd

```c
#include <stdio.h>
int main() {
    int n = 37;
    if(n & 1)
        printf("%d is Odd\n", n);
    else
        printf("%d is Even\n", n);
}
```

---

## Bitwise Example: Swapping Two Numbers

```c
#include <stdio.h>
int main() {
    int x = 7, y = 12;
    printf("Before: x=%d, y=%d\n", x, y);

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("After: x=%d, y=%d\n", x, y);
}
```

---



