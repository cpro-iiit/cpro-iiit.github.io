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