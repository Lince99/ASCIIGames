#include <stdio.h>
#include <stdlib.h>
#include "ascii_matrix.h"

int main() {
    int** matrix = NULL;
    int mat_y, mat_x;
    int val = 0;

    printf("Inserisci la dimensione della matrice:\n");
    printf("Rows:\t");
    scanf("%d", &mat_y);
    printf("Cols:\t");
    scanf("%d", &mat_x);
    //init matrix
    matrix = init_matrix(mat_y, mat_x);
    //print void matrix
    printf("Newly created matrix[%d][%d]:\n", mat_y, mat_x);
    print_matrix_stdout(matrix, mat_y, mat_x);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
    //resize matrix rows
    matrix = resize_matrix(matrix, &mat_y, &mat_x, mat_y+1, mat_x);
    printf("\nAdd 1 row to matrix[%d][%d]:\n", mat_y, mat_x);
    print_matrix_stdout(matrix, mat_y, mat_x);
    printf("_________________________________________________\n\n");
    //resize matrix cols
    matrix = resize_matrix(matrix, &mat_y, &mat_x, mat_y, mat_x+1);
    printf("\nAdd 1 cols to matrix[%d][%d]:\n", mat_y, mat_x);
    print_matrix_stdout(matrix, mat_y, mat_x);
    printf("_________________________________________________\n\n");
    //free matrix
    //free(matrix);
    if(matrix == NULL)
        printf("\nMatrix deallocated\n");
    //re-create it
    printf("Re-created matrix:\n");
    print_matrix_stdout(matrix, mat_y, mat_x);

    return 0;
}
