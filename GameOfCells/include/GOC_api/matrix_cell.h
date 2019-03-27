/*
 * This source is under MIT license
 * Copyright (c) 2019 Lince99
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MATRIX_CELL_H
#define MATRIX_CELL_H

#include <stdio.h>
#include <unistd.h>



//global variables
int MATRIX_Y = 0;
int MATRIX_X = 0;

//signatures
int print_matrix_xterm(int**, int, int);
int** edit_matrix_size(int**, int, int);
int print_matrix_xterm(int**, int, int);
int count_alive_near(int**, int, int, int, int);



/*
 * create a new matrix for one xy plane (2D)
 */
int** init_matrix(int mat_y, int mat_x) {
    int** mat = NULL;
    int i = 0;

    if(mat_y <= 0 || mat_x <= 0) {
        perror("Invalid params (size <= 0)!");
        return NULL;
    }

    mat = (int**) malloc(sizeof(int*)*mat_y);
    if(mat == NULL) {
        perror("Error on alloc matrix column (y)!");
        return NULL;
    }
    for(i = 0; i < mat_y; i++) {
        mat[i] = (int*) malloc(sizeof(int)*(mat_x-1));
        if(mat[i] == NULL) {
            printf("Error on alloc matrix row (x)!");
            return NULL;
        }
    }

    //setting up global dimensions
    MATRIX_Y = mat_y;
    MATRIX_X = mat_x;

    return mat;
}

/*
 * add or remove rows or columns for a dynamic matrix
 */
int** edit_matrix_size(int** matrix, int mat_y, int mat_x) {
    int** tmp = matrix;
    int i = 0;

    if(mat_y <= 0 || mat_x <= 0) {
        perror("Invalid params (size <= 0)!");
        return NULL;
    }
    if(matrix == NULL)
        return init_matrix(mat_y, mat_x);

    if(mat_y != MATRIX_Y) {
        tmp = (int**) realloc(matrix, sizeof(int)*mat_y);
        if(tmp == NULL) {
            perror("Error on resize matrix row!");
            return matrix;
        }
    }
    if(mat_x != MATRIX_X) {
        for(i = 0; i < mat_y; i++) {
            tmp[i] = (int*) realloc(matrix, sizeof(int)*(mat_x-1));
            if(tmp[i] == NULL) {
                perror("Error on resize matrix column!");
                return matrix;
            }
        }
    }

    //update global y
    MATRIX_Y = mat_y;
    MATRIX_X = mat_x;

    return tmp;
}

/*
 * print with colors and refresh the content of the matrix to any terminal
 */
int print_matrix_xterm(int** matrix, int mat_y, int mat_x) {
    int y = 0;
    int x = 0;

    for(x = 0; x < mat_x; x++)
        printf("-");
    printf("\n");
    for(y = 0; y < mat_y; y++) {
        for(x = 0; x < mat_x; x++) {
            if(matrix[y][x])
                printf("\033[37m\033[47m#\033[0m");
            else
                printf("\033[30\033[40mm \033[0m");
        }
        printf("\n");
    }
    printf("\n");
    for(x = 0; x < mat_x; x++)
        printf("-");
    printf("\033[0;1H\n");

    return 0;
}

/*
 * count how many cells around y,x cell are alive
 * return -1 on error, >= 0 on success
 */
int count_alive_near(int** matrix, int mat_y, int mat_x, int y, int x) {
    int count = 0;

    if(y < 0 || y >= mat_y || x < 0 || x >= mat_x)
        return -1;

    //check top
    if(y-1 >= 0) {
        //check top left
        if(x-1 >= 0) {
            if(matrix[y-1][x-1])
                count++;
        }
        //check top mid
        if(matrix[y-1][x])
            count++;
        //check top right
        if(x+1 < mat_x) {
            if(matrix[y-1][x+1])
                count++;
        }
    }
    //check mid left
    if(x-1 >= 0) {
        if(matrix[y][x-1])
            count++;
    }
    //check mid right
    if(x+1 < mat_x) {
        if(matrix[y][x+1])
            count++;
    }
    //check bottom
    if(y+1 < mat_y) {
        //check bottom left
        if(x-1 >= 0) {
            if(matrix[y+1][x-1])
                count++;
        }
        //check bottom mid
        if(matrix[y+1][x])
            count++;
        //check bottom right
        if(x+1 < mat_x) {
            if(matrix[y+1][x+1])
                count++;
        }
    }

    return count;
}

#endif //MATRIX_CELL_H
