---
title: "Tutorial 1"
bookHidden: false
marp: false
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:150px](IIIT_Hyderabad_Logo.jpg)'
---

# Welcome to CS0.101 Tutorial 1


Slides:  https://github.com/cpro-iiit/cpro-iiit.github.io/blob/main/web/content/docs/course_material/tutorials/1/Computer%20Programming%20Tut-1.pdf
    

--- 

## Computer Programming Tutorial-1

---

## Question 1:Marks Analysis

    N students took a course on economics. The final marks (out of 100) of all the students are provided.
    If the input marks do not fall in the range 0 to 100, you should print an error and exit the program by displaying a suitable
    error message.
    Solve the following problems:
    1. If the pass mark is 35, what is the pass percentage? (Percentage of students passed the exam)
    2. What is the mean, variance, and standard deviation of the class?
    3. Compute the number of students falling within one standard deviation, two standard deviations, and the rest.
    4. (No of students in range [mean - sd, mean + sd], [mean - 2*sd, mean + 2*sd] and rest) What are the maximum and minimum
    marks?

Round Off upto 2 decimal points for Pass Percentage, Mean, Variance and Standard Deviation.

---


## Solution:

1. Use a for loop to iterate over all the values, and store the number of students
with marks >=35. In the meantime, also calculate ‘mean’.

2. Use a 2nd for loop to iterate over the values again, and use the formula for
variance to calculate it. Take the square root for standard deviation.

3. Use a 3rd for loop to compute the outputs for part 3 & 4. 
Use ‘%.2f’ to round it upto 2 decimal places.


--- 


## Question 2: The Encrypted Message


Alice and Bob are 2 friends. Alice wants to send a message to Bob about a number X. To do so, she encrypts the number using a special operation involving key k
    X is encrypted as Y = ((X+100) (XOR) k) - 100
    Y+100 = (X+100) XOR k

    (Y+100 XOR k) = (X+100)

    X = (Y+100 XOR k) - 100

Bob has received this encrypted message and knows the key k, but is unfortunately unable to decrypt the message. Help Bob decrypt the message sent.

    Note: The XOR of 2 numbers A and B can be obtained by "A ^ B" in C. ( "^" is the operator for XOR in C ).


--- 

## Solution:

   1. Y = (X+100) (XOR) k - 100
   2. Y + 100 = (X+100) (XOR) k
   3. (Y + 100) (XOR) k = (X+100) (XOR) k (XOR) k
   4. [ (Y + 100) (XOR) k ] - 100 = X

Properties of XOR:
   1. A ( XOR ) 1 = A’
   2. A ( XOR ) 0 = A
   3. A ( XOR ) A = 0

---

## How do you think of test cases?

    1. Understand the problem - This means look at input constraints, and the output
    format.
    2. How to approach it - Divide the input space into partitions. Create decision
    tables.
    3. Think of Edge, Boundary and Special Cases.

--- 


## Compile code 

    gcc filename.c -o output_file_name
    ./a.out ( for linux )
    ./a.exe ( for windows )


--- 

## Question? 
    
    write to TAs , use office hours. 

--- 
Annousements: https://courses.iiit.ac.in/course/view.php?id=4492

Course materials: https://cpro-iiit.github.io/

Assessments/ Autograding: https://pingala.iiit.ac.in/courses/ 