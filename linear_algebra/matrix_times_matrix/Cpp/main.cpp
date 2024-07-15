#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> matrixmul(vector<vector<double>>&, vector<vector<double>>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int row_A, col_A;
    cin >> row_A >> col_A;
    vector<vector<double>> mat_A(row_A, vector<double>(col_A, 0));
    for(int i = 0; i < row_A; ++i)
        for(int j = 0; j < col_A; ++j)
            cin >> mat_A[i][j];

    int row_B, col_B;
    cin >> row_B >> col_B;
    vector<vector<double>> mat_B(row_B, vector<double>(col_B, 0));
    for(int i = 0; i < row_B; ++i)
        for(int j = 0; j < col_B; ++j)
            cin >> mat_B[i][j];

    vector<vector<double>> ans = matrixmul(mat_A, mat_B);
    if(ans[0][0] == -1)
        cout << "-1" << endl;
    else
    {
        for(int i = 0; i < row_A; ++i)
        {
            for(int j = 0; j < col_B; ++j)
                cout << fixed << setprecision(8) << ans[i][j] << " ";
            cout << endl;
        }
    }

    return 0;
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