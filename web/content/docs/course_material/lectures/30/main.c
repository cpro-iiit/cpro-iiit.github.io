#include <stdio.h>
int sum(int n) {
    int s = 0;
    for (int i = 0; i <= n; i++) s += i;
    return s;
}
int main() {
    int n = 5;
    printf("Sum = %d\n", sum(n));
}