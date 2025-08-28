---
title: "L8: Float representation and Evaluation order for logical expressions"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:125px](IIIT_Hyderabad_Logo.jpg)'
revealjs_config:
  slideNumber: true
---




## L8 Float Representation, Evaluation order for logical expressions


---

# C Programming: Tilde Operator (`~`)

---

## What is `~` in C?

- `~` is the **bitwise NOT operator**.
- Flips every bit:
  - `0 → 1`
  - `1 → 0`

Example:

x = 5; // 0000 0101 (in 8 bits)
~x = ? // 1111 1010

---


## Example with Unsigned Integer

```c
#include <stdio.h>
int main() {
    unsigned int x = 5;    // 0000...0101
    printf("x = %u\n", x);
    printf("~x = %u\n", ~x);
}
```
---

## Example with Signed Integer
```c
#include <stdio.h>
int main() {
    int x = 5;   // 0000...0101
    printf("x = %d\n", x);
    printf("~x = %d\n", ~x);
}
```


---

## Floating Point Representation (IEEE 754)

C uses IEEE 754 Standard for float (32-bit) and double (64-bit).
 
| Sign (1 bit) | Exponent (8 bits) | Mantissa (23 bits) |
| ------------ | ----------------- | ------------------ |


$$ (-1)^{\text{sign}}\times (1.\text{mantissa})\times 2^{(\text{exponent} - 127)}$$


---
## Example

Number: 5.75

- Convert to binary:
5.75 = 101.11₂
= 1.0111 × 2²

Sign = 0 (positive)
Exponent = 127 + 2 = 129 = 10000001₂
Mantissa = 0111000...

Final 32-bit pattern:

```
0 10000001 01110000000000000000000
```


---
## Float Representation Example – 0.15625

Convert decimal to binary fraction:
```
0.15625 × 2 = 0.3125 → 0
0.3125 × 2 = 0.625   → 0
0.625 × 2 = 1.25     → 1
0.25 × 2 = 0.5       → 0
0.5 × 2 = 1.0        → 1
```

Binary = 0.00101₂ Normalize: 1.01 × 2⁻³. Sign = 0
Exponent = 127 − 3 = 124 = 01111100₂
Mantissa = 0100000...

Final bit pattern: `0 01111100 01000000000000000000000`

---
## Another Float Example – Negative Number

Number: -7.5

Binary: 111.1₂ = 1.111 × 2²

Sign = 1
Exponent = 127 + 2 = 129 = 10000001₂
Mantissa = 1110000...

Final representation:

1 10000001 11100000000000000000000


---

## The Problem: Exact Representation

- Not all decimal real numbers can be represented **exactly** in binary.
- Example: `0.1` in base 10 looks simple.
- In **binary (base 2)**, `0.1` = `0.000110011001100110011...` (repeating infinitely).
- A `float` has **limited bits**, so it stores only an approximation.

---

## The Problem

- Floating point numbers (`float`, `double`) are stored in **binary (IEEE 754)**.
- Many decimal values **cannot be represented exactly**.
- Equality checks (`==`) often fail due to **rounding errors**.

---

## Example: Equality Failure : Adding .1, 10 times

```c
#include <stdio.h>
#include <math.h>
int main() {
    float x = 0.1f;
    float sum = 0.0f;
    // Add 0.1 ten times
    for (int i = 0; i < 10; i++) 
        sum += x;
    printf("Sum of 0.1 added 10 times = %.25f\n", sum);
    printf("Expected value            = 1.0000000000000000000000000\n");
    // Direct equality check
    if (sum == 1.0f) 
        printf("Equal (sum == 1.0)\n");
    else 
        printf("Not Equal (sum != 1.0)\n");
    // Safer way: use tolerance (epsilon)
    float epsilon = 1e-6;
    if (fabs(sum - 1.0f) < epsilon) {
        printf("Approximately Equal (using epsilon)\n");
    }
    return 0;
}
```

---

## Why?

Internally (IEEE 754, 32-bit float):

0.1 → 0.10000000149011612

Tiny differences cause == to fail.

---

## The Fix: Use an Epsilon

Instead of ==, check if the difference is within tolerance:

```c
#include <stdio.h>
#include <math.h>

int main() {
    float x = 0.1f, y = 0.2f, z = 0.3f;
    float epsilon = 1e-6;

    if (fabs((x + y) - z) < epsilon) {
        printf("Approximately Equal\n");
    } else {
        printf("Not Equal\n");
    }
}
```
---

## Float Representation of Zero


- Exponent = `00000000`
- Mantissa = `000...000`
- Two forms exist:
  - **+0.0** → Sign bit = `0`
  - **-0.0** → Sign bit = `1`

---

## Why Two Zeros?

- Both `+0.0` and `-0.0` are valid.
- They compare equal in C:
```c
#include <stdio.h>
int main() {
    float a = 0.0f;
    float b = -0.0f;

    if (a == b)
        printf("Equal\n");
    else
        printf("Not Equal\n");

    printf("1/a = %f\n", 1/a);
    printf("1/b = %f\n", 1/b);
}
```
---
##  Output
Equal
1/a = inf
1/b = -inf

Equality holds (0.0 == -0.0).

But division reveals the sign of zero!

---



## Logical Operators in C

- **AND (&&)**  
  True if *both* operands are true.

- **OR (||)**  
  True if *at least one* operand is true.

- **NOT (!)**  
  Negates a condition.

---

## Evaluation Order – Short-Circuit

In C, evaluation is **left-to-right** with **short-circuiting**:

- `A && B` → If `A` is false, **B is not evaluated**.  
- `A || B` → If `A` is true, **B is not evaluated**.  

This is called **short-circuit evaluation**.

---

## Example: Short-Circuit AND

```c
#include <stdio.h>
int main() {
    int x = 0;
    if (x != 0 && (10 / x > 1)) {
        printf("Condition true\n");
    } else {
        printf("Condition false\n");
    }
}
```

---

## Example: Short-Circuit OR

```c
#include <stdio.h>
int main() {
    int x = 5;
    if (x == 5 || (10 / x == 2)) {
        printf("True branch\n");
    }
}
```

---

## Example with Side Effects

```c
#include <stdio.h>
int main() {
    int a = 0, b = 1;
    if (a++ > 0 && b++) {
        printf("Inside if\n");
    }
    printf("a = %d, b = %d\n", a, b);
}
```

---