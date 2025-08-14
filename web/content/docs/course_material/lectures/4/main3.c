#include <stdio.h>
int main() {
    char day = 'a';
    switch (day) {
        case 'a': printf("Monday\n"); break;
        case 'b': printf("Tuesday\n"); break;
        case 'c': printf("Wednesday\n"); break;
        default: printf("Invalid day\n");
    }
    return 0;
}