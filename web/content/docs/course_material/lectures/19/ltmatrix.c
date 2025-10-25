#include <stdio.h>
#include <stdlib.h>

// structure for storing a lower triangular
// matrix with only n(n-1)/2 memory
typedef struct LTMatrix {
    int** mat;
    int num_rows;
    int num_cols;    
} LTMatrix;

LTMatrix* create_LTMatrix(int n, int m, int* init) {
    LTMatrix* M = malloc(sizeof(LTMatrix));
    M->num_rows = n;
    M->num_cols = m;
    M->mat = malloc(n*sizeof(int*));
    int k = 0;
    for (int i =0; i < n; i++) {
        if (i < m) {
            M->mat[i] = malloc(i*sizeof(int));
            if (init != NULL)
                for (int j = 0; j <= i; j++) {
                    M->mat[i][j] = init[k++];
                }
        } else { 
            M->mat[i] = malloc(m*sizeof(int));
            if (init != NULL)
                for (int j = 0; j < m; j++) {
                    M->mat[i][j] = init[k++];
                }
        }
    }
    return M;
}

void print_LTMatrix(LTMatrix* M) {
    printf("-- matrix --\n");
    for (int i = 0; i < M->num_rows; i++) {
        for (int j = 0; j < M->num_cols; j++) {
            printf("%d ", M->mat[i][j]);
        }
        printf("\n");
    }
    printf("-- end --\n");
}

// This function should multiply the
// lower triangular matrices A, B (if the dimensions are approriate)
// and return a newly created LTMatrix which has the result
LTMatrix* multiply(LTMatrix* A, LTMatrix* B) {

}

// This function should free up all memory corresponding to 
// a LTMatrix
void delete(LTMatrix* A) {

}

int main() {
    int matrix[6] = {1,
                     2,3,
                     4,5,6};
    LTMatrix* M = create_LTMatrix(3, 3, matrix);
    print_LTMatrix(M);

    return 0;
}