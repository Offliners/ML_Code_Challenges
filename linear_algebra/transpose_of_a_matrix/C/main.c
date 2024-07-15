#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double **transpose_matrix(double**, int, int, int*, int*);
void free_matrix(double**, int);

int main(void)
{
    int mat_row, mat_col;
    scanf("%d %d", &mat_row, &mat_col);

    double **mat = create_matrix(mat_row, mat_col);
    for(int i = 0; i < mat_row; ++i)
        for(int j = 0; j < mat_col; ++j)
            scanf("%lf", &mat[i][j]);

    int mat_T_row = 0;
    int mat_T_col = 0;
    double **mat_T = transpose_matrix(mat, mat_row, mat_col, &mat_T_row, &mat_T_col);

    for(int i = 0; i < mat_T_row; ++i)
    {
        for(int j = 0; j < mat_T_col; ++j)
            printf("%lf ", mat_T[i][j]);
        printf("\n");
    }

    free_matrix(mat, mat_row);
    free_matrix(mat_T, mat_T_row);

    return 0;
}

double **create_matrix(int row, int col)
{
    double **mat = (double**)malloc(row * sizeof(double*));
    for(int i = 0; i < row; ++i)
        mat[i] = (double*)malloc(col * sizeof(double));
    
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            mat[i][j] = 0;
    
    return mat;
}

double **transpose_matrix(double **mat, int mat_row, int mat_col, int *return_mat_T_row, int *return_mat_T_col)
{
    *return_mat_T_row = mat_col;
    *return_mat_T_col = mat_row;
    double **mat_T = create_matrix(*return_mat_T_row, *return_mat_T_col);

    for(int i = 0; i < *return_mat_T_row; ++i)
        for(int j = 0; j < *return_mat_T_col; ++j)
            mat_T[i][j] = mat[j][i];

    return mat_T;
}

void free_matrix(double **mat, int row)
{
    if(!mat)
        return;

    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}