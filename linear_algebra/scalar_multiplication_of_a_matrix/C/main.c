#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double **scalar_multiply(double**, int, int, double);
void free_matrix(double **, int);

int main(void)
{
    int row, col;
    scanf("%d %d", &row, &col);

    double k;
    scanf("%lf", &k);

    double **mat = create_matrix(row, col);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            scanf("%lf", &mat[i][j]);
    
    double **k_mat = scalar_multiply(mat, row, col, k);
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
            printf("%.8lf ", k_mat[i][j]);
        printf("\n");
    }

    free_matrix(mat, row);
    free_matrix(k_mat, row);

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

double **scalar_multiply(double **mat, int row, int col, double k)
{
    double **k_mat = create_matrix(row, col);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            k_mat[i][j] = k * mat[i][j];
    
    return k_mat;
}

void free_matrix(double **mat, int row)
{
    if(!mat)
        return;

    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}