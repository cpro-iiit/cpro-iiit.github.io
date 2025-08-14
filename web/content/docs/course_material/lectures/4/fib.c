#include <stdio.h>
int main() {
    int n = 10;
    int i = 1;
    long long c = 0, f = 0 , t = 1;
    while (i < n) {
        c = f + t;
        f = t;
        t = c;
        i = i + 1;
            printf("%d\n", c);
    }


    return 0;
}