#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double **inverse_2x2(double**, int, int);
void free_matrix(double**, int);

int main(void)
{
    int row, col;
    scanf("%d %d", &row, &col);

    double **mat = create_matrix(row, col);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            scanf("%lf", &mat[i][j]);

    double **mat_inv = inverse_2x2(mat, row, col);
    if(!mat_inv)
        printf("-1\n");
    else
    {
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
                printf("%.8lf ", mat_inv[i][j]);
            printf("\n");
        }
    }

    free_matrix(mat, row);
    free_matrix(mat_inv, row);

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

double **inverse_2x2(double **mat, int row, int col)
{
    double det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    if(det == 0)
        return NULL;
    
    double **mat_inv = create_matrix(row, col);
    mat_inv[0][0] = mat[1][1] / det;
    mat_inv[1][1] = mat[0][0] / det;
    mat_inv[0][1] = -mat[0][1] / det;
    mat_inv[1][0] = -mat[1][0] / det;

    return mat_inv;
}

void free_matrix(double **mat, int row)
{
    if(!mat)
        return;

    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}