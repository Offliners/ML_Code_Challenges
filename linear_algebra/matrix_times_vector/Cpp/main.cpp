#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> matrix_dot_vector(vector<vector<double>>&, vector<double>&);

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

    int row_B;
    int col_B;
    cin >> row_B >> col_B;
    vector<double> vec_B(row_B, 0);
    for(int i = 0; i < row_B; ++i)
        cin >> vec_B[i];

    vector<double> ans = matrix_dot_vector(mat_A, vec_B);
    if(ans[0] == -1)
        cout << -1 << endl;
    else
    {
        for(int i = 0; i < row_A; ++i)
            cout << fixed << setprecision(8) << ans[i] << " ";
        cout<< endl;
    }

    return 0;
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