---
title: "L29: File I/O III"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# L29 File I/O III


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