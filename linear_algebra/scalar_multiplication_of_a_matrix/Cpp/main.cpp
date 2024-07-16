#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> scalar_multiply(vector<vector<double>>&, double);

int main(void)
{
    int row, col;
    cin >> row >> col;

    double k;
    cin >> k;

    vector<vector<double>> mat(row, vector<double>(col, 0));
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            cin >> mat[i][j];

    vector<vector<double>> k_mat = scalar_multiply(mat, k);
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
            cout << fixed << setprecision(8) << k_mat[i][j] << " ";
        cout << endl;
    }

    return 0;
}

vector<vector<double>> scalar_multiply(vector<vector<double>> &mat, double k)
{
    int row = mat.size();
    int col = mat[0].size();
    vector<vector<double>> k_mat(row, vector<double>(col, 0));

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            k_mat[i][j] = k * mat[i][j];

    return k_mat;
}