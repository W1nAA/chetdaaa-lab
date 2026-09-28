#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double closestPairBruteForce(const vector<Point>& P, Point& p1, Point& p2) {
    double min_dist = numeric_limits<double>::infinity();
    int n = P.size();

    for (int i = 0; i <= n - 2; ++i) {
        for (int j = i + 1; j <= n - 1; ++j) {
            double dx = P[i].x - P[j].x;
            double dy = P[i].y - P[j].y;
            double dist = sqrt(dx * dx + dy * dy);

            if (dist < min_dist) {
                min_dist = dist;
                p1 = P[i];
                p2 = P[j];
            }
        }
    }

    return min_dist;
}

int main() {
    cout << "Brute Force & Exhaustive Search Task 1\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << setw(10) << "N"
         << setw(20) << "C(N,2)"
         << setw(20) << "Time (ms)"
         << setw(25) << "Ratio t(N)/t(N/2)" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    vector<int> N_list = {100, 1000, 5000, 10000, 20000};

    mt19937 rng(1337);
    uniform_real_distribution<double> dist(0.0, 10000.0);

    double prev_time = -1.0;
    int prev_N = -1;

    for (int N : N_list) {
        vector<Point> P(N);

        for (int i = 0; i < N; ++i) {
            P[i] = {dist(rng), dist(rng)};
        }

        Point best_p1, best_p2;

        auto start = chrono::high_resolution_clock::now();

        double min_d = closestPairBruteForce(P, best_p1, best_p2);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        double current_time = elapsed.count();

        long long num_pairs = (long long)N * (N - 1) / 2;

        cout << setw(10) << N
             << setw(20) << num_pairs
             << setw(20) << fixed << setprecision(2) << current_time;

        if (prev_N > 0 && N == prev_N * 2 && prev_time > 0) {
            double ratio = current_time / prev_time;

            cout << setw(25)
                 << fixed << setprecision(2)
                 << ratio << "\n";
        } else {
            cout << setw(25) << "-" << "\n";
        }

        prev_time = current_time;
        prev_N = N;
    }

    cout << "---------------------------------------------------------------------------------\n";

    return 0;
}