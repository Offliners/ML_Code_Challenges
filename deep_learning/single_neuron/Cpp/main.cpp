#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> single_neuron_model(vector<vector<double>>&, vector<double>&, vector<double>&, double);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int num_data, feature_size;
    cin >> num_data >> feature_size;
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
    vector<double> weights(weight_size, 0);
    for(int i = 0; i < weight_size; ++i)
        cin >> weights[i];

    double bias;
    cin >> bias;

    vector<double> ans = single_neuron_model(features, labels, weights, bias);
    for(int i = 0; i < ans.size() - 1; ++i)
        cout << fixed << setprecision(8) << ans[i] << " ";
    cout << endl;
    cout << ans.back() << endl;

    return 0;
}

vector<double> single_neuron_model(vector<vector<double>> &features, vector<double> &labels, vector<double> &weights, double bias)
{
    int num_data = features.size();
    int prob_ans_size = features.size();
    vector<double> ans(prob_ans_size, 0);

    double mse = 0;
    for(int i = 0; i < prob_ans_size; ++i)
    {
        double z = 0;
        for(int j = 0; j < features[i].size(); ++j)
            z += features[i][j] * weights[j];
        
        ans[i] = 1 / (1 + exp(-(z + bias)));
        mse += pow(ans[i] - labels[i], 2);
    }

    ans.push_back(mse / num_data);
    return ans;
}