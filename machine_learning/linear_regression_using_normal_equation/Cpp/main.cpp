#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> linear_regression_normal_equation(vector<vector<double>>&, vector<double>&);
vector<vector<double>> transpose_matrix(vector<vector<double>>&);
vector<vector<double>> matrixmul(vector<vector<double>>&, vector<vector<double>>&);
vector<vector<double>> matrix_inverse(vector<vector<double>>&);
double matrix_determinant(vector<vector<double>>&);
void scalar_multiply(vector<vector<double>>&, double);
vector<vector<double>> get_cofactor_matrix(vector<vector<double>>&);
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
        cout << fixed << setprecision(8) << theta[i] << " ";
    cout << endl;

    return 0;
}

vector<double> linear_regression_normal_equation(vector<vector<double>> &X, vector<double> &y)
{
    vector<vector<double>> X_T = transpose_matrix(X);
    vector<vector<double>> X_T_X = matrixmul(X_T, X);
    vector<vector<double>> X_T_X_inv = matrix_inverse(X_T_X);
    vector<vector<double>> X_T_X_inv_X_T = matrixmul(X_T_X_inv, X_T);
    vector<double> theta = matrix_dot_vector(X_T_X_inv_X_T, y);

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

vector<vector<double>> matrixmul(vector<vector<double>> &A, vector<vector<double>> &B)
{
    int A_row = A.size();
    int A_col = A[0].size();
    int B_row = B.size();
    int B_col = B[0].size();
    if(A_col != B_row)
        return {{-1}};

    vector<vector<double>> C(A_row, vector<double>(B_col, 0));
    for(int i = 0; i < A_row; ++i)
        for(int j = 0; j < B_col; ++j)
            for(int k = 0; k < B_row; ++k)
                C[i][j] += A[i][k] * B[k][j];
    
    return C;
}

vector<vector<double>> matrix_inverse(vector<vector<double>> &A)
{
    double det = matrix_determinant(A);
    if(det == 0)
    {
        cout << "The determinant of the matrix is zero!" << endl;
        return {{}};
    }

    double det_inv = 1 / det;
    int dim = A.size();
    vector<vector<double>> inv_mat = A;
    inv_mat = get_cofactor_matrix(inv_mat);
    inv_mat = transpose_matrix(inv_mat);
    scalar_multiply(inv_mat, det_inv);

    return inv_mat;
}

double matrix_determinant(vector<vector<double>> &A)
{
    if(A.size() != A[0].size())
    {
        cout << "Invalid size!" << endl;
        return -1;
    }

    int dim = A.size();
    if(dim == 0)
        return 1;
    
    if(dim == 1)
        return A[0][0];
    
    if(dim == 2)
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];

    if(dim == 3)
        return A[0][0] * A[1][1] * A[2][2] +\
               A[0][1] * A[1][2] * A[2][0] +\
               A[0][2] * A[1][0] * A[2][1] -\
               A[0][0] * A[1][2] * A[2][1] -\
               A[0][1] * A[1][0] * A[2][2] -\
               A[0][2] * A[1][1] * A[2][0];
    
    double det_result = 0;
    int sign = 1;
    for(int i = 0; i < dim; ++i)
    {
        vector<vector<double>> sub_mat(dim - 1, vector<double>(dim - 1, 0));
        for(int j = 1; j < dim; ++j)
        {
            int temp = 0;
            for(int k = 0; k < dim; ++k)
            {
                if(k != i)
                {
                    sub_mat[j-1][temp] = A[j][k];
                    ++temp;
                }
            }
        }

        det_result += sign * A[0][i] * matrix_determinant(sub_mat);
        sign = -sign;
    }

    return det_result;
}

void scalar_multiply(vector<vector<double>> &mat, double k)
{
    int row = mat.size();
    int col = mat[0].size();

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            mat[i][j] *= k;
}

vector<vector<double>> get_cofactor_matrix(vector<vector<double>> &A)
{
    if(A.size() != A[0].size())
    {
        cout << "Invalid size!" << endl;
        return {{}};
    }

    int dim = A.size();
    vector<vector<double>> co_mat(dim, vector<double>(dim, 0));
    vector<vector<double>> sub_mat(dim - 1, vector<double>(dim - 1, 0));

    int sign = -1;
    for(int i = 0; i < dim; ++i)
    {
        for(int j = 0; j < dim; ++j)
        {
            int p = 0;
            for(int x = 0; x < dim; ++x)
            {
                if(x == i)
                    continue;

                int q = 0;
                for(int y = 0; y < dim; ++y)
                {
                    if(y == j)
                        continue;

                    sub_mat[p][q] = A[x][y];
                    ++q;
                }
                ++p;
            }

            sign = (i + j) % 2 == 0 ? 1 : -1;
            co_mat[i][j] = sign * matrix_determinant(sub_mat);
        }
    }

    return co_mat;
}

vector<double> matrix_dot_vector(vector<vector<double>> &mat, vector<double> &vec)
{
    if(mat[0].size() != vec.size())
    {
        cout << "Invalid size!" << endl;
        return {-1};
    }

    int result_row = mat.size();
    int result_col = vec.size();
    vector<double> result(result_row);

    for(int i = 0; i < result_row; ++i)
        for(int j = 0; j < result_col; ++j)
            result[i] += mat[i][j] * vec[j];

    return result;
}