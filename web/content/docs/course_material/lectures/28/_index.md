---
title: "L28: File I/O II"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# File I/O II

C I/O Library

---

## Copying a file with source/destination as commandline arguments

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid arguments\n");
        return 0;
    }

    char ch;

    FILE* s = fopen(argv[1], "r");
    FILE* d = fopen(argv[2], "w");

    /* fopen() return NULL if last operation was unsuccessful */
    if(s == NULL || d == NULL)
    {
        /* Unable to open file hence exit */
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        return 0;
    }

    /* File open success message */
    printf("File opened successfully. Reading file contents character by character. \n\n");

    do 
    {
        /* Read single character from file */
        ch = fgetc(s);

        /* Print character read on console */
        putchar(ch);

        fputc(ch, d);

    } while(ch != EOF); /* Repeat this if last read character is not EOF */

    /* Done with this file, close file to release resource */
    fclose(s);
    fclose(d);

    return 0;
}
```


## Home Work

Write a program which takes a file name as command line argument and prints the number of chars, words, lines and paragraphs in the file.


---
## Reading line by line using `fgets()`

```c
char * fgets(char * str, int num, FILE * stream);
```
---

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main() {
    /* File pointer to hold reference to our file */
    FILE * fPtr;

    char buffer[BUFFER_SIZE];
    int totalRead = 0;
    int total_chars = 0;

    /* 
     * Open file in r (read) mode. 
     * "data/file2.txt" is complete file path to read
     */
    fPtr = fopen("1.c", "r");

    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        return 0;
    }

    /* File open success message */
    printf("File opened successfully. Reading file contents line by line. \n\n");

    /* Repeat this until read line is not NULL */
    while(fgets(buffer, BUFFER_SIZE, fPtr) != NULL) 
    {
        /* Total character read count */
        totalRead = strlen(buffer);
        total_chars += strlen(buffer);

        /* Print line read on cosole*/
        printf("%s", buffer);

    } 

    printf("Total number of chars: %d", total_chars);

    /* Done with this file, close file to release resource */
    fclose(fPtr);

    return 0;
}
``` 

---


# C Standard Library

[https://en.wikibooks.org/wiki/C_Programming/Standard_library_reference]

[https://en.cppreference.com/w/c/io]




## Random Number Generation

[Random Number Generation Reference](https://en.cppreference.com/w/c/numeric/random)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    srand(time(NULL)); // use current time as seed for random generator
    int random_variable = rand();
    printf("Random value on [0,%d]: %d\n", RAND_MAX, random_variable);

    int x;
    int count[] = { 0,0,0,0,0,0};
    for (int i=0; i < 6000; i++) {
       x = 1+ rand()%6;
    //    printf("%d ", x); 
       count[x-1]++;
    }
    printf("%d %d %d %d %d %d\n", count[0], count[1], count[2], count[3], count[4], count[5]);
}
```

### Home Work 1

Write a program to generate and  print:

- a uniformly random subset of {1, 2, .., n}. Take n as input.
- a uniformly random subset of {1, 2, .., n} of size k. Take n, k as input.
- a uniformly random permutation of {1, 2, .., n}. Take n as input.

## Date Time Clock

[Date Time Clock Reference](https://en.cppreference.com/w/c/chrono)


### Home Work 2

- Write a program to print the number of days in the current month.

- Write a program, which takes an input a date and prints the month calendar where that date belongs. 

For eg: For today date it should print below:

<pre>
November 3rd, 2023
Sun Mon Tue Wed Thu Fri Sat  
29  30  31  1   2   3*  4  
5   6   7   8   9   10  11  
12  13  14  15  16  17  18  
19  20  21  22  23  24  25  
26  27  28  29  30  
</pre>

