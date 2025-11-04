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
    fwrite( (void*)c, sizeof(Customer), 3, cus_file);
    fclose(cus_file);
    
    Customer d[3] ;
    cus_file = fopen("customer.bin","r");
    fread((void*)d, sizeof(Customer), 3, cus_file);
    for (int i = 0; i < 3; i++) {
        printf("Customer Read Details: %s, %d\n", d[i].name, d[i].phone_no);
    }
    fclose(cus_file);
    return 0;
}