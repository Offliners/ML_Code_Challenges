#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double *create_vector(int);
double *linear_regression_normal_equation(double**, int, int, double*, int);
double **transpose_matrix(double**, int, int);
double **matrixmul(double**, int, int, double**, int, int);
double **matrix_inverse(double**, int, int);
double matrix_determinant(double **, int, int);
double **matrix_copy(double**, int, int);
double **get_cofactor_matrix(double**, int, int);
double **scalar_multiply(double**, int, int, double);
double *matrix_dot_vector(double**, int, int, double*, int);
void free_matrix(double**, int);
void free_vector(double*);

int main(void)
{
    int row, col;
    scanf("%d %d", &row, &col);

    double **X = create_matrix(row, col - 1);
    double *y = create_vector(row);
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col -1; ++j)
            scanf("%lf", &X[i][j]);
        
        scanf("%lf", &y[i]);
    }

    double *theta = linear_regression_normal_equation(X, row, col - 1, y, row);
    for(int i = 0; i < row; ++i)
        printf("%.8lf ", theta[i]);
    printf("\n");

    free_matrix(X, row);
    free_vector(y);
    free_vector(theta);

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

double *linear_regression_normal_equation(double **X, int X_row, int X_col, double *y, int y_row)
{
    double **X_T = transpose_matrix(X, X_row, X_col);
    double **X_T_X = matrixmul(X_T, X_col, X_row, X, X_row, X_col);
    double **X_T_X_inv = matrix_inverse(X_T_X, X_col, X_col);
    double **X_T_X_inv_X_T = matrixmul(X_T_X_inv, X_col, X_col, X_T, X_col, X_row);
    double *theta = matrix_dot_vector(X_T_X_inv_X_T, X_col, X_col, y, y_row);

    free_matrix(X_T, X_row);
    free_matrix(X_T_X, X_col);
    free_matrix(X_T_X_inv, X_col);
    free_matrix(X_T_X_inv_X_T, X_col);

    return theta;
}

double **transpose_matrix(double **mat, int mat_row, int mat_col)
{
    double **mat_T = create_matrix(mat_row, mat_col);

    for(int i = 0; i < mat_row; ++i)
        for(int j = 0; j < mat_col; ++j)
            mat_T[i][j] = mat[j][i];

    return mat_T;
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

double **matrix_inverse(double **mat, int row, int col)
{
    double det = matrix_determinant(mat, row, col);
    if(det == 0)
    {
        printf("The determinant of the matrix is zero!\n");
        return NULL;
    }

    double det_inv = 1 / det;
    double **mat_inv = matrix_copy(mat, row, col);
    mat_inv = get_cofactor_matrix(mat_inv, row, col);
    mat_inv = transpose_matrix(mat_inv, row, col);
    mat_inv = scalar_multiply(mat_inv, row, col, det_inv);

    return mat_inv;
}

double matrix_determinant(double **mat, int row, int col)
{
    if(row != col)
    {
        printf("Invalid size!\n");
        return -1;
    }

    if(row == 0)
        return 1;
    
    if(row == 1)
        return mat[0][0];
    
    if(row == 2)
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    if(row == 3)
        return mat[0][0] * mat[1][1] * mat[2][2] +\
               mat[0][1] * mat[1][2] * mat[2][0] +\
               mat[0][2] * mat[1][0] * mat[2][1] -\
               mat[0][0] * mat[1][2] * mat[2][1] -\
               mat[0][1] * mat[1][0] * mat[2][2] -\
               mat[0][2] * mat[1][1] * mat[2][0];

    double det_result = 0;
    int sign = 1;
    for(int i = 0; i < row; ++i)
    {
        double **sub_mat = create_matrix(row - 1, col - 1);
        for(int j = 1; j < col; ++j)
        {
            int temp = 0;
            for(int k = 0; k < row; ++k)
            {
                if(k != i)
                {
                    sub_mat[j - 1][temp] = mat[j][k];
                    ++temp;
                }
            }
        }

        det_result += sign * mat[0][i] * matrix_determinant(sub_mat, row - 1, col - 1);
        sign = -sign;
        free_matrix(sub_mat, row - 1);
    }

    return det_result;
}

double **matrix_copy(double **mat, int row, int col)
{
    double **mat_copy = create_matrix(row, col);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            mat_copy[i][j] = mat[i][j];
    
    return mat_copy;
}

double **get_cofactor_matrix(double **mat, int row, int col)
{
    if(row != col)
    {
        printf("Invalid size!\n");
        return NULL;
    }

    double **co_mat = create_matrix(row, col);
    double **sub_mat = create_matrix(row - 1, col - 1);

    int sign = -1;
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            int p = 0;
            for(int x = 0; x < row; ++x)
            {
                if(x == i)
                    continue;

                int q = 0;
                for(int y = 0; y < col; ++y)
                {
                    if(y == j)
                        continue;

                    sub_mat[p][q] = mat[x][y];
                    ++q;
                }
                ++p;
            }

            sign = (i + j) % 2 == 0 ? 1 : -1;
            co_mat[i][j] = sign * matrix_determinant(sub_mat, row - 1, col - 1);
        }
    }

    free_matrix(sub_mat, row - 1);
    return co_mat;
}

double **scalar_multiply(double **mat, int row, int col, double k)
{
    double **k_mat = create_matrix(row, col);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            k_mat[i][j] = k * mat[i][j];
    
    return k_mat;
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
    free(vec);
}