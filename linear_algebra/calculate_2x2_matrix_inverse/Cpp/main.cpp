#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> inverse_2x2(vector<vector<double>>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int row, col;
    cin >> row >> col;
    vector<vector<double>> mat(row, vector<double>(col, 0));
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            cin >> mat[i][j];
    
    vector<vector<double>> mat_inv = inverse_2x2(mat);
    if(mat_inv[0][0] == -1)
        cout << "-1" << endl;
    else
    {
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
                cout << fixed << setprecision(8) << mat_inv[i][j] << " ";
            cout << endl;
        }
    }

    return 0;
}

vector<vector<double>> inverse_2x2(vector<vector<double>> &mat)
{
    double det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    if(det == 0)
        return {{-1}};
    
    vector<vector<double>> mat_inv(2, vector<double>(2, 0));
    mat_inv[0][0] = mat[1][1] / det;
    mat_inv[1][1] = mat[0][0] / det;
    mat_inv[0][1] = -mat[0][1] / det;
    mat_inv[1][0] = -mat[1][0] / det;

    return mat_inv;
}