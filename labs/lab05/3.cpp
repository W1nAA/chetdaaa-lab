#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

struct TSPResult {
    vector<int> best_path;
    double min_cost;
};

TSPResult TSP_Exhaustive(const vector<vector<double>> &dist_matrix, int N) {
    vector<int> cities(N - 1);

    for (int i = 0; i < N - 1; i++) {
        cities[i] = i + 1;
    }

    double min_cost = numeric_limits<double>::infinity();
    vector<int> best_path;

    do {
        vector<int> current_path;
        current_path.reserve(N + 1);
        current_path.push_back(0);
        current_path.insert(current_path.end(), cities.begin(), cities.end());
        current_path.push_back(0);
        double current_cost = 0.0;

        for (int i = 0; i < N; ++i) {
            int u = current_path[i];
            int v = current_path[i + 1];
            current_cost += dist_matrix[u][v];
        }

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_path = current_path;
        }

    } while (next_permutation(cities.begin(), cities.end()));

    return {best_path, min_cost};
}

vector<vector<double>> generate_distance_matrix(int N) {
    unsigned int seed = 21;
    mt19937 rng(seed);
    uniform_real_distribution<double> dist(10.0, 100.0);

    vector<vector<double>> matrix(N, vector<double>(N, 0.0));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double d = dist(rng);
            matrix[i][j] = d;
            matrix[j][i] = d;
        }
    }
    return matrix;
}

int main() {
    vector<int> test_sizes = {8, 9, 10, 11, 12, 13};
    double prev_time = 0.0;

    cout << fixed << setprecision(6);
    cout << "================================================================\n";
    cout << " N  | (N-1)! Paths | Execution Time (s) | Min Cost | t(N)/t(N-1)\n";
    cout << "================================================================\n";

    for (int N : test_sizes) {
        vector<vector<double>> dist_matrix = generate_distance_matrix(N);

        auto start_time = chrono::high_resolution_clock::now();

        TSPResult result = TSP_Exhaustive(dist_matrix, N);

        auto end_time = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end_time - start_time;
        double current_time = duration.count();

        long long factorial = 1;
        for (int i = 1; i <= N - 1; ++i) {
            factorial *= i;
        }

        cout << setw(3) << N << " | "
             << setw(12) << factorial << " | "
             << setw(18) << current_time << " | "
             << setw(8) << setprecision(2) << result.min_cost << " | ";

        if (N == 8) {
            cout << "    -    " << endl;
        } else {
            double ratio = current_time / prev_time;
            cout << setw(8) << ratio << endl;
        }

        prev_time = current_time;
    }
    cout << "================================================================\n";

    return 0;
}