#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

void knapsackExhaustive(const vector<int>& weights, const vector<int>& values, int N, int W, int& max_value, long long& best_mask) {
    max_value = 0;
    best_mask = 0;

    long long total_combinations = 1LL << N;

    for (long long mask = 0; mask < total_combinations; ++mask) {
        int current_weight = 0;
        int current_value = 0;

        for (int i = 0; i < N; ++i) {
            if ((mask >> i) & 1) {
                current_weight += weights[i];
                current_value += values[i];
            }
        }

        if (current_weight <= W && current_value > max_value) {
            max_value = current_value;
            best_mask = mask;
        }
    }
}

int main() {
    unsigned int seed = 21;
    vector<int> N_values = {10, 15, 20, 22, 25, 28, 30};

    cout << "======================================================================================\n";
    cout << "  N  | Max Value |   Total Subsets (2^N)   | Time (s) |      Note / Status      \n";
    cout << "======================================================================================\n";

    for (int N : N_values) {
        int W = N * 3;

        vector<int> weights(N);
        vector<int> values(N);

        mt19937 rng(seed);

        uniform_int_distribution<int> dist_weight(1, 20);
        uniform_int_distribution<int> dist_value(10, 99);

        for (int i = 0; i < N; ++i) {
            weights[i] = dist_weight(rng);
            values[i] = dist_value(rng);
        }

        int max_value = 0;
        long long best_mask = 0;
        long long total_combinations = 1LL << N;

        auto start = chrono::high_resolution_clock::now();
        knapsackExhaustive(weights, values, N, W, max_value, best_mask);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end - start;
        double current_time = elapsed.count();

        string status = "Fast";
        if (current_time > 1.0) status = "Noticeable delay";
        if (current_time > 10.0) status = "Severe delay";

        cout << setw(3) << N << "  | "
             << setw(9) << max_value << " | "
             << setw(23) << total_combinations << " | "
             << fixed << setprecision(4) << setw(8) << current_time << " | "
             << status << "\n";
    }
    
    cout << "======================================================================================\n";

}