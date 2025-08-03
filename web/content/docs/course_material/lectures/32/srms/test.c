#include <stdio.h>

int main() {



    FILE* f = fopen("test","w");

    fclose(f);
    return 0;
}