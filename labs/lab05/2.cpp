#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>

void knapsackExhaustive(const std::vector<int>& weights, const std::vector<int>& values, int N, int W) {
    int max_value = 0;
    int best_mask = 0;

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
            best_mask = static_cast<int>(mask);
        }
    }

    std::cout << "N = " << std::setw(2) << N << " | Max Value = " << max_value << "\n";
}

int main() {
    std::vector<int> N_values = {10, 15, 20, 22, 25, 28, 30};

    for (int N : N_values) {
        int W = N * 5;

        std::vector<int> weights(N);
        std::vector<int> values(N);

        std::srand(42);
        for (int i = 0; i < N; ++i) {
            weights[i] = (std::rand() % 20) + 1;
            values[i] = (std::rand() % 90) + 10;
        }

        auto start = std::chrono::high_resolution_clock::now();
        knapsackExhaustive(weights, values, N, W);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time used: " << std::fixed << std::setprecision(4) 
                  << elapsed.count() << " seconds\n\n";
    }
}