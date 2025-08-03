#include "srms.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Improper arguments\n");
        return 0;
    }

    char items_list[3][100] = {
        "Potato",
        "Tomato",
        "Eggs"
    };

    int price_list[3] = {
        100,
        200,
        35
    };

    Database db;
    db.customer_count = db.reciept_count = 0;

    // Read from the files here.
    FILE* f_cust = fopen(argv[1], "r");
    FILE* f_rec = fopen(argv[2], "r");

    fread(&(db.customer_count), sizeof(int), 1, f_cust);
    fread(db.customers, sizeof(Customer), db.customer_count, f_cust);

    fread(&(db.reciept_count), sizeof(int), 1, f_rec);
    fread(db.reciepts, sizeof(Reciept), db.reciept_count, f_rec);
    fclose(f_cust);
    fclose(f_rec);


    while(true) {

        // system("@cls||clear"); // clears the screen

        printf("-------------------------------------------------------------------\n"
               "Store Reciept Management System\n"
               "-------------------------------------------------------------------\n"
               "\tOptions: 0 New Receipt | 1 New Customer | 2 Reciepts by Customer | 3 Save & Exit | 4 Items List\n"
               "\tStats: %d Customers | %d Reciepts\n"
               "-------------------------------------------------------------------\n"
               "Enter Option: ", db.customer_count, db.reciept_count);
        
        int option;
        scanf("%d", &option);

        int p, v, m;
        int c = 0;
        char name[100];
        switch (option)
        {
            case 0:
                printf("Enter Customer Phone: ");
                scanf("%d", &p);
                c = find_customer_by_phone_no(p, &db); 
                if (c == -1) {
                    printf("(New Customer) Name: ");
                    scanf("%s", name);
                    c = add_customer(name, p, &db);
                }
                printf("Payment Mode (0 for Cash, 1 for Card, 2 for UPI): ");
                scanf("%d", &m);
                printf("Reciept Amount: ");
                scanf("%d", &v);
                add_reciept(v, c, m, &db);
                break;

            case 1:
                printf("Enter Customer Phone: ");
                scanf("%d", &p);
                c = find_customer_by_phone_no(p, &db); 
                if (c == -1) {
                    printf("(New Customer) Name: ");
                    scanf("%s", name);
                    c = add_customer(name, p, &db);
                }
                break;

            case 2:
                // input a phone nom
                printf("Enter Customer Phone: ");
                scanf("%d", &p);
                c = find_customer_by_phone_no(p, &db); 

                // print out all reicepts curresponding to that customer.
                    printf("No.\tValue\n"
                            "--------------------------\n");
                for(int i =0; i< db.reciept_count; i++) {

                    if (db.reciepts[i].customer_index == c) {
                        printf("%d\t%f\n", i, db.reciepts[i].value);
                    }
                }

                printf("----------------------\n");
                break;

            case 3: {
                FILE* f_cust = fopen(argv[1], "w");
                FILE* f_rec = fopen(argv[2], "w");

                if (f_cust == NULL || f_rec == NULL ) {
                    printf("Invalid files\n");
                } else {
                    fwrite(&(db.customer_count), sizeof(int), 1, f_cust);
                    fwrite(db.customers, sizeof(Customer), db.customer_count, f_cust);

                    fwrite(&(db.reciept_count), sizeof(int), 1, f_rec);
                    fwrite(db.reciepts, sizeof(Reciept), db.reciept_count, f_rec);
                    fclose(f_cust);
                    fclose(f_rec);
                }

                return 0;
                break;
            }

            case 4: {
                
            }
            
            default:
                break;
        }

    }

    return 0;
}