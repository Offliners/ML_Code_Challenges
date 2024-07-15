#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double **matrixmul(double**, int, int, double**, int, int);
void free_matrix(double**, int);

int main(void)
{
    int row_A, col_A;
    scanf("%d %d", &row_A, &col_A);
    double **mat_A = create_matrix(row_A, col_A);
    for(int i = 0; i < row_A; ++i)
        for(int j = 0; j < col_A; ++j)
            scanf("%lf", &mat_A[i][j]);
    
    int row_B, col_B;
    scanf("%d %d", &row_B, &col_B);
    double **mat_B = create_matrix(row_B, col_B);
    for(int i = 0; i < row_B; ++i)
        for(int j = 0; j < col_B; ++j)
            scanf("%lf", &mat_B[i][j]);
    
    double **ans = matrixmul(mat_A, row_A, col_A, mat_B, row_B, col_B);
    if(!ans)
        printf("-1\n");
    else
    {
        for(int i = 0; i < row_A; ++i)
        {
            for(int j = 0; j < col_B; ++j)
                printf("%lf ", ans[i][j]);
            printf("\n");
        }
    }

    free_matrix(mat_A, row_A);
    free_matrix(mat_B, row_B);
    free_matrix(ans, row_A);

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

double **matrixmul(double **A, int A_row, int A_col, double **B, int B_row, int B_col)
{
    if(A_col != B_row)
        return NULL;
    
    double **C = create_matrix(A_row, B_col);

    for(int i = 0; i < A_row; ++i)
        for(int j = 0; j < B_col; ++j)
            for(int k = 0; k < B_row; ++k)
                C[i][j] += A[i][k] * B[k][j];
    
    return C;
}

void free_matrix(double **mat, int row)
{
    if(!mat)
        return;

    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}