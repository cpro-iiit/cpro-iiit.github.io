
#include <stdio.h>
#include "math_utils.h"

int main() {
    int x = 10, y = 5;

    printf("Add: %d\n", add(x, y));
    printf("Subtract: %d\n", subtract(x, y));
    printf("Multiply: %d\n", multiply(x, y));
    printf("Divide: %d\n", divide(x, y));

    printf("Main changed\n");

    return 0;
}