#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> calculate_covariance_matrix(vector<vector<double>>&);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int vec_row, vec_col;
    cin >> vec_row >> vec_col;

    int num_vec;
    cin >> num_vec;
    vector<vector<double>> vecs(num_vec, vector<double>(vec_row, 0));
    for(int i = 0; i < num_vec; ++i)
        for(int j = 0; j < vec_row; ++j)
            cin >> vecs[i][j];

    vector<vector<double>> ans = calculate_covariance_matrix(vecs);
    for(int i = 0; i < num_vec; ++i)
    {
        for(int j = 0; j < num_vec; ++j)
            cout << fixed << setprecision(8) << ans[i][j] << " ";
        cout << endl;
    }

    return 0;
}

vector<vector<double>> calculate_covariance_matrix(vector<vector<double>> &vecs)
{
    int n_features = vecs.size();
    int n_observations = vecs[0].size();
    vector<vector<double>> cov_mat(n_features, vector<double>(n_features, 0));
    vector<double> means(n_features, 0);

    for(int i = 0; i < n_features; ++i)
    {
        double sum = 0;
        for(int j = 0; j < n_observations; ++j)
            sum += vecs[i][j];
        
        means[i] = sum / n_observations;
    }

    for(int i = 0; i < n_features; ++i)
    {
        for(int j = i; j < n_features; ++j)
        {
            double mul_result = 0;
            for(int k = 0; k < n_observations; ++k)
                mul_result += (vecs[i][k] - means[i]) * (vecs[j][k] - means[j]);
            
            mul_result /= (n_observations - 1);
            cov_mat[i][j] = mul_result;
            cov_mat[j][i] = mul_result;
        }
    }

    return cov_mat;
}