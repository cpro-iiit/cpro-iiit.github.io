---
title: "L27: File I/O"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# File I/O and Command Line Arguments
---
## Commandline Argument

An easier way to take input from the user in shell.



---
## Commandline Argument

```c
#include <stdio.h>
int main(int argc, char* argv[]) {
    printf("The number of arguments is %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("%d Argument: %s\n", i, argv[i]);    
    }
    return 0;
}
```
---
## Problem
Write a program that takes the First Name Last Name Age 
as commandline arguments and prints it as follows
  First Name: <first arg>   
  Last name : <sec arg>  
  Age       : <third arg>  

---
## Solution
```c
#include "stdio.h"

int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        printf("Incorrect number of arguments provided.\n");
        return 0;
    }

    printf("First Name:\t%s\n", argv[1]);
    printf("Last Name :\t%s\n", argv[2]);
    printf("Age       :\t%s\n", argv[3]);
    return 0;
 }
```
---
## Why store data in files?

- Much larger data storage than RAM.
- Persist accross different executions of the program.
- Work with other programs.

---
## Opening/Closing a file

```c
#include <stdlib.h>
#include <stdio.h>
/* File pointer to hold reference to our file */
FILE * fPtr;
// Open file in w (write) mode. "data/file1.txt"  is complete path to create file
fPtr = fopen("data/file1.txt", "w");
/* fopen() return NULL if last operation  was unsuccessful */
if(fPtr == NULL)
{
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(0);
}
/* Done with this file, close file to release resource */
fclose(fPtr);
```
---
## Reading from file

- `fgetc()` – Used to read single character from file.
- `fgets()` – Used to read string from file.
- `fscanf()` – Use this to read formatted input from file.
- `fread()` – Read block of raw bytes from file. Used to read binary files.

---
## Reading

- Open a file using `fopen()` function and store its reference in a `FILE` pointer say `fPtr`.
- You must open file in `r`(read) mode or atleast mode that support read access.

- Read content from file using any of these functions `fgetc()`, `fgets()`, `fscanf()` or `fread()`.
Finally, close the file using `fclose(fPtr)`.

---


## Reading from file, char by char

```c
do {
    /* Read single character from file */
    ch = fgetc(fPtr);
    /* Print character read on console */
    putchar(ch);
} while(ch != EOF); /* Repeat this 
if last read character is not EOF */
```
