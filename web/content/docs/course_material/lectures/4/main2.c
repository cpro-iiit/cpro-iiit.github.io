#include <stdio.h>
int main() {
    int result = 10 + 20 * 3 % 4;
    printf("%d\n", result); // 70 (not 90)
    return 0;
}