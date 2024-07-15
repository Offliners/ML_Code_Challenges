#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> linear_regression_normal_equation(vector<vector<double>>&, vector<double>&);
vector<vector<double>> transpose_matrix(vector<vector<double>>&);
vector<vector<double>> matrix_multiplication(vector<vector<double>>&, vector<vector<double>>&);
vector<vector<double>> matrix_inverse(vector<vector<double>>&);
vector<double> matrix_dot_vector(vector<vector<double>>&, vector<double>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int mat_row, mat_col;
    cin >> mat_row >> mat_col;

    vector<vector<double>> X(mat_row, vector<double>(mat_col - 1, 0));
    vector<double> y(mat_row, 0);

    for(int i = 0; i < mat_row; ++i)
    {
        for(int j = 0; j < mat_col - 1; ++j)
            cin >> X[i][j];
        
        cin >> y[i];
    }

    vector<double> theta = linear_regression_normal_equation(X, y);
    for(int i = 0; i < theta.size(); ++i)
        cout << theta[i] << " ";
    cout << endl;

    return 0;
}

vector<double> linear_regression_normal_equation(vector<vector<double>> &X, vector<double> &y)
{
    vector<vector<double>> X_T = transpose_matrix(X);
    vector<vector<double>> X_T_X = matrix_multiplication(X_T, X);

    vector<double> theta = matrix_dot_vector(X_T_X, y);

    return theta;
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

vector<vector<double>> matrix_multiplication(vector<vector<double>> &A, vector<vector<double>> &B)
{
    int A_row = A.size();
    int A_col = A[0].size();
    int B_row = B.size();
    int B_col = B[0].size();

    if(A_col != B_row)
        return {{}};
    
    vector<vector<double>> C(A_row, vector<double>(B_col, 0));
    for(int i = 0; i < A_row; ++i)
        for(int j = 0; j < A_col; ++j)
            for(int k = 0; k < B_row; ++k)
                C[i][j] += A[i][k] * B[k][j];
    
    return C;
}

vector<vector<double>> matrix_inverse(vector<vector<double>> &A)
{

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