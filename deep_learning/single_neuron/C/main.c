#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **create_matrix(int, int);
double *create_vector(int);
double *single_neuron_model(double**, int, int, double*, int, double*, int, double);
void free_matrix(double**, int);
void free_vector(double*);

int main(void)
{
    int num_data, feature_size;
    scanf("%d %d", &num_data, &feature_size);

    double **features = create_matrix(num_data, feature_size);
    for(int i = 0; i < num_data; ++i)
        for(int j = 0; j < feature_size; ++j)
            scanf("%lf", &features[i][j]);
    
    int num_label;
    scanf("%d", &num_label);
    double *labels = create_vector(num_label);
    for(int i = 0; i < num_label; ++i)
        scanf("%lf", &labels[i]);

    int num_weight;
    scanf("%d", &num_weight);
    double *weights = create_vector(num_weight);
    for(int i = 0; i < num_weight; ++i)
        scanf("%lf", &weights[i]);

    double bias;
    scanf("%lf", &bias);

    double *ans = single_neuron_model(features, num_data, feature_size, labels, num_label, weights, num_weight, bias);
    for(int i = 0; i < num_data; ++i)
        printf("%lf ", ans[i]);
    printf("\n");
    printf("%lf\n", ans[num_data]);

    free_matrix(features, num_data);
    free_vector(labels);
    free_vector(weights);
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

double *single_neuron_model(double **features, int num_data, int num_feature, double *labels, int num_label, double *weights, int num_weight, double bias)
{
    int mse_size = 1;
    double *ans = create_vector(num_data + mse_size);

    double mse = 0;
    for(int i = 0; i < num_data; ++i)
    {
        double z = 0;
        for(int j = 0; j < num_feature; ++j)
            z += features[i][j] * weights[j];
        
        ans[i] = 1 / (1 + exp(-(z + bias)));
        mse += pow(ans[i] - labels[i], 2);
    }
    ans[num_data] = mse / num_data;

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