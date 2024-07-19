#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<vector<double>> train_neuron(vector<vector<double>>&, vector<double>&, vector<double>&, double, double, int);
vector<double> matrix_dot_vector(vector<vector<double>>&, vector<double>&);
vector<double> vector_addition(vector<double>&, vector<double>&);
vector<double> vector_subtraction(vector<double>&, vector<double>&);
vector<double> sigmoid(vector<double>&);
double mse(vector<double>&, vector<double>&);
vector<vector<double>> transpose_matrix(vector<vector<double>>&);
vector<double> vector_multiplication(vector<double>&, vector<double>&);
double vector_sum(vector<double>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int epochs, num_data, feature_size;
    cin >> epochs >> num_data >> feature_size;
    vector<vector<double>> features(num_data, vector<double>(feature_size, 0));
    for(int i = 0; i < num_data; ++i)
        for(int j = 0; j < feature_size; ++j)
            cin >> features[i][j];

    int label_size;
    cin >> label_size;
    vector<double> labels(label_size, 0);
    for(int i = 0; i < label_size; ++i)
        cin >> labels[i];

    int weight_size;
    cin >> weight_size;
    vector<double> initial_weights(weight_size, 0);
    for(int i = 0; i < weight_size; ++i)
        cin >> initial_weights[i];
    
    double initial_bias;
    cin >> initial_bias;

    double learning_rate;
    cin >> learning_rate;

    vector<vector<double>> ans = train_neuron(features, labels, initial_weights, initial_bias, learning_rate, epochs);
    // trained weights
    for(int i = 0; i < ans[0].size(); ++i)
        cout << fixed << setprecision(8) << ans[0][i] << " ";
    cout << endl;

    // trained bias
    cout << ans[1][0] << endl;

    // MSE loss of each epoch
    for(int i = 0; i < ans[2].size(); ++i)
        cout << ans[2][i] << " ";
    cout << endl;

    return 0;
}

vector<vector<double>> train_neuron(vector<vector<double>> &features, vector<double> &labels, vector<double> &initial_weights, double initial_bias, double learning_rate, int epochs)
{
    vector<vector<double>> ans;
    ans.push_back(vector<double>(initial_weights.size(), 0)); // trained weights
    ans.push_back(vector<double>(1, 0));                      // trained bias
    ans.push_back(vector<double>(epochs, 0));                 // MSE loss of each epoch

    int num_data = features.size();
    int num = labels.size();
    int weight_size = initial_weights.size();
    vector<double> nums(weight_size, 1.0 / num);

    vector<double> weights = initial_weights;
    double bias = initial_bias;

    vector<double> ones(num, 1);
    vector<double> lr_vec(weight_size, learning_rate);
    for(int i = 0; i < epochs; ++i)
    {
        vector<double> z = matrix_dot_vector(features, weights);
        vector<double> bias_vec(num_data, bias);
        z = vector_addition(z, bias_vec);
        z = sigmoid(z);
        ans[2][i] = mse(z, labels);

        vector<double> errors = vector_subtraction(z, labels);
        vector<vector<double>> features_T = transpose_matrix(features);
        vector<double> temp = vector_subtraction(ones, z);
        temp = vector_multiplication(z, temp);
        vector<double> grad = vector_multiplication(errors, temp);

        bias -= learning_rate * vector_sum(grad) / num;

        temp = matrix_dot_vector(features_T, grad);
        temp = vector_multiplication(lr_vec, temp);
        temp = vector_multiplication(nums, temp);
        weights = vector_subtraction(weights, temp);
    }
    for(int i = 0; i < weight_size; ++i)
        ans[0][i] = weights[i];

    ans[1][0] = bias;

    return ans;
}

vector<double> matrix_dot_vector(vector<vector<double>> &mat, vector<double> &vec)
{
    if(mat[0].size() != vec.size())
        return {-1};

    int result_row = mat.size();
    int result_col = vec.size();
    vector<double> result(result_row);

    for(int i = 0; i < result_row; ++i)
        for(int j = 0; j < result_col; ++j)
            result[i] += mat[i][j] * vec[j];

    return result;
}

vector<double> vector_addition(vector<double> &A, vector<double> &B)
{
    if(A.size() != B.size())
        return {-1};
    
    vector<double> C(A.size(), 0);
    for(int i = 0; i < A.size(); ++i)
        C[i] = A[i] + B[i];

    return C; 
}

vector<double> vector_subtraction(vector<double> &A, vector<double> &B)
{
    if(A.size() != B.size())
        return {-1};
    
    vector<double> C(A.size(), 0);
    for(int i = 0; i < A.size(); ++i)
        C[i] = A[i] - B[i];

    return C; 
}

vector<double> sigmoid(vector<double> &z)
{
    vector<double> z_sigmoid(z.size(), 0);
    for(int i = 0; i < z.size(); ++i)
        z_sigmoid[i] = 1 / (1 + exp(-z[i]));

    return z_sigmoid;
}

double mse(vector<double> &pred, vector<double> &labels)
{
    if(pred.size() != labels.size())
    {
        cout << "Size mismatch between predictions (" << pred.size() << ") and labels (" << labels.size() << ")!" << endl;
        return 0;
    }

    int n = pred.size();
    double result = 0;
    for(int i = 0; i < n; ++i)
        result += pow(pred[i] - labels[i], 2);

    return result / n;
}

vector<vector<double>> transpose_matrix(vector<vector<double>> &mat)
{
    int mat_T_row = mat[0].size();
    int mat_T_col = mat.size();
    vector<vector<double>> mat_T(mat_T_row, vector<double>(mat_T_col, 0));
    for(int i = 0; i < mat_T_row; ++i)
        for(int j = 0; j < mat_T_col; ++j)
            mat_T[i][j] = mat[j][i];
    
    return mat_T;
}

vector<double> vector_multiplication(vector<double> &A, vector<double> &B)
{
    if(A.size() != B.size())
        return {0};

    int size = A.size();
    vector<double> C(size, 0);
    for(int i = 0; i < size; ++i)
        C[i] = A[i] * B[i];
    
    return C;
}

double vector_sum(vector<double> &vec)
{
    double total = 0;
    for(int i = 0; i < vec.size(); ++i)
        total += vec[i];
    
    return total;
}