/* Copyright (C) 2019  Lince99
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see http://www.gnu.org/licenses .
 */

#ifndef ASCII_MATRIX_H
#define ASCII_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

//signatures
int isAlphaNum(int);
int is_void_matrix(int**, int, int);
int** init_matrix(int, int);
int** resize_matrix(int**, int*, int*, int, int);
void print_matrix(WINDOW*, int**, int, int);
void print_matrix_stdout(int**, int, int);
void free_matrix(int**, int);
int matrix_to_file(int**, int, int, char*);
int** file_to_matrix(char*, int*, int*);



/*
 * return 1 if it's a printable character, else return 0
 */
int isAlphaNum(int ch) {

    //Ascii table 0-127
    if(ch >= 32 || ch <= 126)
        return 1;
    //extended AScii table 128-255
    if((ch == 128) || (ch >= 130 || ch <= 140) || (ch == 142) ||
       (ch >= 130 || ch <= 140) || (ch >= 130 || ch <= 140) ||
       (ch == 142) || (ch >= 145 || ch <= 156) || (ch == 158) ||
       (ch == 159) || (ch >= 161 || ch <= 172) ||
       (ch >= 174 || ch <= 183) || (ch >= 185 || ch <= 255))
        return 1;

    //non-printable character
    return 0;
}

/*
 * check if the matrix is completely void
 */
int is_void_matrix(int** matrix, int mat_y, int mat_x) {

    if(matrix == NULL)
        return 1;

    for(; mat_y > 0; mat_y--) {
        for (; mat_x > 0; mat_x--) {
            if(matrix[mat_y][mat_x] != 0 || matrix[mat_y][mat_x] != ' ')
                return 0;
        }
    }

    return 1;
}

/*
 * allocate a new matrix
 */
int** init_matrix(int y, int x) {
    int** mat = NULL;
    int i, j;

    if(y <= 0 || x <= 0)
        return NULL;
    //init rows
    mat = (int**) malloc(sizeof(int*)*y);
    if(mat == NULL)
        return NULL;
    //init every cell in every row
    for(i = 0; i < y; i++) {
        mat[i] = (int*) malloc(sizeof(int)*x);
        if(mat[i] == NULL)
            return NULL;
        for(j = 0; j < x; j++)
            mat[i][j] = 0;
    }

    return mat;
}

/*
 * resize matrix only if new size is bigger than original,
 * then return the new matrix and the new size within 2nd (y) and 3rd (x) param
 */
int** resize_matrix(int** mat, int* mat_y, int* mat_x, int new_y, int new_x) {
    int y, x;

    if(mat == NULL) {
        *mat_y = new_y;
        *mat_x = new_x;
        return init_matrix(new_y, new_x);
    }
    //check rows resize
    if(new_y > *mat_y) {
        mat = (int**) realloc(mat, sizeof(int*)*new_y);
        for(y = (*mat_y)-1; y < new_y; y++) {
            mat[y] = (int*) malloc(sizeof(int)*(*mat_x));
            for(x = 0; x < *mat_x; x++)
                mat[y][x] = 0;
        }
        *mat_y = new_y;
    }
    //check column resize
    if(new_x > *mat_x) {
        for(y = 0; y < *mat_y; y++) {
            mat[y] = (int*) realloc(mat[y], sizeof(int)*new_x);
            for(x = new_x-(*mat_x)-1; x < new_x; x++)
                mat[y][x] = 0;
        }
        *mat_x = new_x;
    }

    return mat;
}

/*
 * print matrix content inside the "win" ncurses window
 * "border" is how many char has to skip to print content
 */
void print_matrix(WINDOW* win, int** matrix, int mat_y, int mat_x) {
    int y, x;
    int nlines, ncols;

    if(win == NULL || matrix == NULL)
        return;
    getmaxyx(win, nlines, ncols);
    for(y = 1; y < nlines-1 && y < mat_y; y++) {
        for(x = 1; x < ncols-1 && x < mat_x; x++) {
            if(matrix[y-1][x-1] != 0)
                mvwprintw(win, y, x, "%c", matrix[y-1][x-1]);
            else
                mvwprintw(win, y, x, " ");
        }
    }

}

/*
 * print matrix content to stdout
 */
void print_matrix_stdout(int** matrix, int mat_y, int mat_x) {
    int y, x;

    if(matrix == NULL)
        return;
    printf("+");
    for(x = 1; x < mat_x-1; x++)
        printf("-");
    printf("+");
    for(y = 0; y < mat_y; y++) {
        printf("|");
        for(x = 0; x < mat_x; x++) {
            if(matrix[y][x] != 0)
                printf("%c", matrix[y][x]);
            else
                printf(" ");
        }
        printf("|\n");
    }
    printf("\n+");
    for(x = 1; x < mat_x-1; x++)
        printf("-");
    printf("+\n");

}

/*
 * free matrix memory, and return 1 on success, 0 on error
 */
void free_matrix(int** matrix, int mat_y) {

    if(matrix == NULL || mat_y <= 0)
        return;
    for(; mat_y > 0; mat_y--)
        free(matrix[mat_y-1]);
    free(matrix);

}

//-----------------------------------TODO-------------------------------------//
/*
 * save matrix to filename, return 0 on success, 1 on NULL found, 2 I/O error
 */
int matrix_to_file(int** matrix, int mat_y, int mat_x, char* filename) {
    FILE* fp = NULL;
    int y, x;

    if(matrix == NULL || filename == NULL)
        return 1;
    fp = fopen(filename, "w+");
    if(fp == NULL)
        return 2;
    //print to file matrix content
    for(y = 0; y < mat_y; y++) {
        for(x = 0; x < mat_x; x++) {
            if(matrix[y][x] == 0)
                fprintf(fp, " ");
            else
                fprintf(fp, "%c", matrix[y][x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}

/*
 * return a pointer to the matrix, and mat_y, mat_x via reference
 */
int** file_to_matrix(char* filename, int* mat_y, int* mat_x) {
    FILE* fp = NULL;
    int** matrix = NULL;
    int ch = 0;
    //int y, x;

    if(filename == NULL) {
        *mat_y = -1;
        *mat_x = -1;
        return NULL;
    }
    fp = fopen(filename, "r");
    if(fp == NULL) {
        *mat_y = -1;
        *mat_x = -1;
        return NULL;
    }
    //read file content
    while((ch = fgetc(fp)) != EOF) {
        if(ch == '\n')
            (*mat_y)++;
        else
            (*mat_x)++;
    }

    fclose(fp);

    return matrix;
}

#endif //ASCII_MATRIX_H
