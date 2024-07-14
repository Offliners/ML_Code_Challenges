#include <stdio.h>
#include <stdlib.h>

double **create_matrix(int, int);
double *create_vector(int);
double **calculate_covariance_matrix(double**, int, int, int*, int*);
void free_matrix(double**, int);
void free_vector(double*);

int main(void)
{
    int vec_row, vec_col;
    scanf("%d %d", &vec_row, &vec_col);

    int num_vec;
    scanf("%d", &num_vec);

    double **vecs = create_matrix(num_vec, vec_row);
    for(int i = 0; i < num_vec; ++i)
        for(int j = 0; j < vec_row; ++j)
            scanf("%lf", &vecs[i][j]);

    int ans_row = 0;
    int ans_col = 0;
    double **ans = calculate_covariance_matrix(vecs, num_vec, vec_row, &ans_row, &ans_col);
    for(int i = 0; i < ans_row; ++i)
    {
        for(int j = 0; j < ans_col; ++j)
            printf("%lf ", ans[i][j]);
        printf("\n");
    }

    free_matrix(vecs, num_vec);
    free_matrix(ans, num_vec);

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

double **calculate_covariance_matrix(double **vecs, int vecs_row, int vecs_col, int *return_row_size, int *return_col_size)
{
    int n_featrues = vecs_row;
    int n_observations = vecs_col;

    double *means = create_vector(n_featrues);
    double **cov_mat = create_matrix(n_featrues, n_featrues);
    *return_row_size = n_featrues;
    *return_col_size = n_featrues;

    for(int i = 0; i < n_featrues; ++i)
    {
        double sum = 0;
        for(int j = 0; j < n_observations; ++j)
            sum += vecs[i][j];
        
        means[i] = sum / n_observations;
    }

    for(int i = 0; i < n_featrues; ++i)
    {
        for(int j = i; j < n_featrues; ++j)
        {
            double mul_result = 0;
            for(int k = 0; k < n_observations; ++k)
                mul_result += (vecs[i][k] - means[i]) * (vecs[j][k] - means[j]);

            mul_result /= (n_observations - 1);
            cov_mat[i][j] = mul_result;
            cov_mat[j][i] = mul_result;
        }
    }
    
    free_vector(means);
    return cov_mat;
}

void free_matrix(double **mat, int row)
{
    for(int i = 0; i < row; ++i)
        free(mat[i]);
    
    free(mat);
}

void free_vector(double *vec)
{
    free(vec);
}