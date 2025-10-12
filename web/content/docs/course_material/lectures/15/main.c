#include <stdio.h>



int main() {

    int n = 3;
    int m[2*n-1][2*n-1];

    int start = 0;
    int end = 2*n-2;
    for (int k=n; k>0; k--) {
        // 1. fill outer border by n
        for (int i = 0; i < 2*k-1; i++) {
            m[start][start+i] = k;// first row
            m[end][start+i] = k; // last row
            m[start+i][start] = k; // first column
            m[start + i][end] = k; // last column
        }
        //recurse
        start++;
        end--;
    }

    for (int i = 0; i< 2*n-1; i++) {
        for (int j = 0; j < 2*n-1; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    return 0;

}