#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double *create_vector(int);
double *matrix_dot_vector(double **, int, int, double *, int);
void free_matrix(double **, int);
void free_vector(double *);

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
    double *vec_B = create_vector(row_B);
    for(int i = 0; i < row_B; ++i)
        scanf("%lf", &vec_B[i]);
    
    double *ans = matrix_dot_vector(mat_A, row_A, col_A, vec_B, row_B);
    if(!ans)
        printf("-1\n");
    else
    {
        for(int i = 0; i < row_A; ++i)
            printf("%.8lf ", ans[i]);
        printf("\n");
    }

    free_matrix(mat_A, row_A);
    free_vector(vec_B);
    free_vector(ans);

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

double *create_vector(int row)
{
    double *vec = (double*)malloc(row * sizeof(double));
    for(int i = 0; i < row; ++i)
        vec[i] = 0;
    
    return vec;
}

double *matrix_dot_vector(double **mat, int mat_row, int mat_col, double *vec, int vec_row)
{
    if(mat_col != vec_row)
        return NULL;
    
    double *ans = create_vector(mat_row);

    for(int i = 0; i < mat_row; ++i)
        for(int j = 0; j < vec_row; ++j)
            ans[i] += mat[i][j] * vec[j];
    
    return ans;
}

void free_matrix(double **mat, int row)
{
    if(!mat)
        return;

    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}

void free_vector(double *vec)
{
    if(!vec)
        return;

    free(vec);
}