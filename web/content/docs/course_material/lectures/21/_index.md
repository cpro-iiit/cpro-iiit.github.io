---
title: "L21: File I/O"
bookHidden: true
marp: true
header: 'CS0.101 Computer Programming (Monsoon 25)'
revealjs_config:
  slideNumber: true
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


---


## Reading/Writing Binary Data to/from a file

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    char name[100];
    int phone_no;
} Customer;

int main() {
    Customer c = { "Ramu", 90034699 };
    FILE* cus_file = fopen("customer.bin","w");
    fwrite(&c, sizeof(Customer), 1, cus_file);
    fclose(cus_file);

    Customer d ;
    cus_file = fopen("customer.bin","r");
    fread(d, sizeof(Customer), 1, cus_file);
    printf("Customer Read Details: %s, %d", d.name, d.phone_no);
    fclose(cus_file);
    return 0;
}
```
---


## Reading/Writing Array of structs

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    char name[100];
    int phone_no;
} Customer;

int main() {
    Customer c[3] = {
        { "Ramu", 90034699 },
        { "Ammu", 900146939 },
        { "Thomas", 769834234 }
    };

    FILE* cus_file = fopen("customer.bin","w");
    fwrite(c, sizeof(Customer), 3, cus_file);
    fclose(cus_file);
    
    Customer d[3] ;
    cus_file = fopen("customer.bin","r");
    fread(&d, sizeof(Customer), 3, cus_file);
    for (int i = 0; i < 3; i++) {
        printf("Customer Read Details: %s, %d", d[i].name, d[i].phone_no);
    }
    fclose(cus_file);
    return 0;
}
```
---

## Store Reciept Management System

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Customer {
    char name[100];
    int phone_no;
} Customer;

typedef enum PayMode {
    Cash,
    Card,
    UPI 
} PayMode;

typedef struct Reciept {
    time_t time;
    float value;
    // Customer *customer; We cannot store this as pointer.
    int customer_index;
    PayMode mode;
} Reciept;

typedef struct Database {
    Customer customers[100];
    Reciept reciepts[1000];
    int customer_count;
    int reciept_count;
} Database;

int add_customer(char *name, int phone_no, Database *db) {
    Customer *c = &(db->customers[db->customer_count++]);
    c->phone_no = phone_no;
    strcpy(c->name, name);
    return db->customer_count-1;
}

Reciept* add_reciept(int value, int c, PayMode mode, Database *db) {
    time_t now = time(NULL);
    Reciept* r = &(db->reciepts[db->reciept_count++]);
    r->customer_index= c;
    r->value = value;
    r->time = now;
    r->mode = mode;
    return r;
}

int find_customer_by_phone_no(int phone, Database *db) {
    Customer *cust = NULL;
    for(int i =0; i< db->customer_count; i++) {
        if(phone == db->customers[i].phone_no) {
            cust = &(db->customers[i]);
            return i;
            break;
        }
    }
    return -1;
}

void print_db(Database* db) {
    printf("Customers_______________\n");
    for (int i = 0; i < db->customer_count; i++) {
        printf("%s\t%d\n", db->customers[i].name, db->customers[i].phone_no);
    }
    printf("Reciepts_______________\n");
    for (int i = 0; i < db->reciept_count; i++) {
        printf("%d\t%f\n", db->reciepts[i].customer_index, db->reciepts[i].value);
    }
}
```

## Write Example
```c
int main() {
    Database db;
    db.customer_count = db.reciept_count = 0;

    int a = add_customer("Alice",12345,&db);

    add_reciept(1000, a, Cash, &db);
    add_reciept(500, a, UPI, &db);

    int b = add_customer("Bob",5678,&db);

    add_reciept(700, b, Card, &db);
    add_reciept(500, b, UPI, &db);

    print_db(&db);

    FILE* cus_file = fopen("customers.bin","w");

    fwrite(&(db.customer_count), sizeof(int), 1, cus_file);

    fwrite(db.customers, sizeof(Customer), db.customer_count, cus_file);

    fclose(cus_file);

    FILE* res_file = fopen("reciepts.bin","w");

    fwrite(&(db.reciept_count), sizeof(int), 1, res_file);

    fwrite(db.reciepts, sizeof(Reciept), db.reciept_count, res_file);

    fclose(res_file);

    return 0;

}
```

## Read Example 

```c
int main() {
    Database db;
    db.customer_count = db.reciept_count = 0;

    FILE* cus_file = fopen("customers.bin","r");

    fread(&(db.customer_count), sizeof(int), 1, cus_file);

    fread(db.customers, sizeof(Customer), db.customer_count, cus_file);

    fclose(cus_file);

    FILE* res_file = fopen("reciepts.bin","r");

    fread(&(db.reciept_count), sizeof(int), 1, res_file);

    fread(db.reciepts, sizeof(Reciept), db.reciept_count, res_file);

    fclose(cus_file);

    print_db(&db);

    return 0;
}
```