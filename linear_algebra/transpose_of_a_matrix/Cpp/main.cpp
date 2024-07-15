#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> transpose_matrix(vector<vector<double>>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int mat_row, mat_col;
    cin >> mat_row >> mat_col;

    vector<vector<double>> mat(mat_row, vector<double>(mat_col, 0));
    for(int i = 0; i < mat_row; ++i)
        for(int j = 0; j < mat_col; ++j)
            cin >> mat[i][j];

    vector<vector<double>> mat_T = transpose_matrix(mat);
    for(int i = 0; i < mat_T.size(); ++i)
    {
        for(int j = 0; j < mat_T[0].size(); ++j)
            cout << fixed << setprecision(8) << mat_T[i][j] << " ";
        cout << endl;
    }

    return 0;
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