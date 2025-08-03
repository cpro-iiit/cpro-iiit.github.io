---
title: "Quiz-1"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:150px](IIIT_Hyderabad_Logo.jpg)'
---

# Welcome to CS0.101 Computer Programming

 
# Quiz-1
Questions and Solutions: [C_pro_quiz1_2024.pdf](https://github.com/cpro-iiit/cpro-iiit.github.io/blob/main/web/content/docs/course_material/quiz/C_pro_quiz1_2024.pdf)



---

# Cpro24m Quiz-1

## Code for each question below with attached solution   
---  
# Short answer questions
### Q-1 Assuming 8 bits, express 33 in 2′s complement notation. (5 marks)

    Ans: Convert 33 to Binary The binary representation of 33 is 00100001.

    Determine if the Number is Positive or Negative:

    Since 33 is positive, the 2's complement representation for positive
    numbers is the same as their binary representation, with the most
    significant bit (MSB) being 0 (which indicates a positive number).

    So, the 8-bit 2's complement representation of 33 is:0100001
---
    
### Q-2 What is the space taken by each of the following data types: char, double, int, float, short? (5 marks)

```c
int q_2() {
        printf("Size of char: %lu byte(s)\n", sizeof(char));
        printf("Size of int: %lu byte(s)\n", sizeof(int));
        printf("Size of float: %lu byte(s)\n", sizeof(float));
        printf("Size of double: %lu byte(s)\n", sizeof(double));
        printf("Size of short: %lu byte(s)\n", sizeof(short));

        return 0;
}   // Ans: char: 1 byte
    // int: 4 bytes
    // float: 4 bytes
    // double: 8 bytes
    // short: 2 bytes
```
--- 
### Q-3: What is the output of the following program? Answer with justification. (5 marks)
```c
int q_3() {
    int i = 2, j = 2, k = 2;
    i += j += k;
    printf("%d %d %d", i, j, k);
    return 0;
}// Ans-3: 6 4 2

```

---

### Q-4: What is the output of the following program? Answer with justification. (5 marks)
```c
int q_4(){
    int n=0;
    if (n >= 1 <= 10){
        printf("n is between 1 and 10\n");}
    return 0;
}// Ans 4; n is between 1 and 10
```
---

# Multiple choise questions.

--- 


### Q-1: What is the output of the following program?
```c 
int q1() {
    int num = 2;
    printf("Ans 1.1: %d\n", (num << 1) + (num >> 1));
    return 0;
    // Ans 1: 5
} 
```
--- 

### Q-2: What is the output of the following program?
```c
int q2() {
    int i = 0, j = 0;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 1;) {
            break;
        }
        printf("Ans 1.2: CProgramming\n");
    }
    return 0;
} // Ans 1.2: CProgramming. 
    // ... x100 (Total 100 CProgramming)
```
--- 

### Q-3: What is the output of the following program?
```c 
int q3() {
    int a=2, b=3;
    printf("%d %d", a/b, b/a);
    return 0;
} // Ans 1.3; 0 1 
```
--- 

### Q-4: What is the output of the following program?
```c
int q4() {
    int i, j, count;
    count=0;
    for(i=0; i<5; i++);
    { 
        count++;
    }
    printf("%d",count);
    return 0;
} // Ans 1.4: 1
```
--- 

### Q-5: What is the output of the following program?
```c
int q5() {
        int i = 0, j = 0; 
        while (i<5 & j<10)  { 
            i++; 
            j++; 
        } 
        printf("%d %d", i, j);
    return 0;
} // Ans 1.5: 5 5
```
--- 

### Q-6: What is the output of the following program?
```c
int q6() {
        int i = 3; 
        printf("%d\n", i++); 
        printf("%d\n", i++);
} // Ans 1.6: 3 4
```
---  

### Q-7: What is the output of the following program?
```c
int q7() {
    int a = 2;
    switch(a) {
        case 1: printf("1 ");
        case 2: printf("2 ");
        case 3: printf("3 ");
        default: printf("None");
    }
    return 0;
} // Ans 1.7: 2 3 None
```
--- 

### Q-8: What is the output of the following program?
```c
int q8() {
    int x = printf("Hello!");
    printf("%d", x);
    return 0;
} // Ans 1.8: Hello!6
```
--- 

### Q-9: What is the output of the following program?
```c
int q9() {
    int x =0, y = 0, z = 1;
    if (x){
        if (y) {
                if  (z){
                        z = 3;
                }
                else {
                        z = 2;
                }
        }
    }
    printf("Ans 1.9: %d, %d, %d\n", x, y, z);
    return 0;
} // Ans 1.9: 0, 0, 1
```
--- 
### Q-10: What is the output of the following program?
```c
int q10() {
    double x = 0;
    for (x=0; x<5; x++);
    printf("Ans 1.10: %lf\n", x);
    return 0;
} // Ans 1.10: 5.000000
```
--- 
##  Run c programm for all questions, q_1.c
```c
int main () {
    q1();
    q2();
    q3();
    q4();
    q5();
    q6();
    q7();
    q8();
    q9();
    q10();
    q_2();
    q_3();
    q2_4();

    return 0;
}
```

--- 
## Solutions 

Compile and run the q_1.c

```c
gcc q_1.c -o main; ./q_1 
```


More detailed Solution: [C_pro_quiz1_2024.pdf](https://github.com/cpro-iiit/cpro-iiit.github.io/blob/main/web/content/docs/course_material/quiz/C_pro_quiz1_2024.pdf)