#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <chrono>
#include <iomanip>

struct Point {
    double x, y;
};


double closestPairBruteForce(const std::vector<Point>& P, Point& p1, Point& p2) {
    double min_dist = std::numeric_limits<double>::infinity();
    int n = P.size();

    for (int i = 0; i <= n - 2; ++i) {
        for (int j = i + 1; j <= n - 1; ++j) {
            double dx = P[i].x - P[j].x;
            double dy = P[i].y - P[j].y;
            double dist = std::sqrt(dx * dx + dy * dy);

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
    std::cout << "Bruce Force & Exhaustive Search Task 1\n";
    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << std::setw(10) << "N" 
              << std::setw(20) << "C(N,2)" 
              << std::setw(20) << "Time (ms)" 
              << std::setw(25) << "Ratio t(N)/t(N/2)" << "\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    std::vector<int> N_list = {100, 1000, 5000, 10000, 20000};
    std::mt19937 rng(1337);
    std::uniform_real_distribution<double> dist(0.0, 10000.0);

    double prev_time = -1.0;
    int prev_N = -1;

    for (int N : N_list) {
        std::vector<Point> P(N);
        for (int i = 0; i < N; ++i) {
            P[i] = {dist(rng), dist(rng)};
        }

        Point best_p1, best_p2;

        auto start = std::chrono::high_resolution_clock::now();
        double min_d = closestPairBruteForce(P, best_p1, best_p2);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;
        double current_time = elapsed.count();
        long long num_pairs = (long long)N * (N - 1) / 2;

        std::cout << std::setw(10) << N 
                  << std::setw(20) << num_pairs 
                  << std::setw(20) << std::fixed << std::setprecision(2) << current_time;

        
        if (prev_N > 0 && N == prev_N * 2 && prev_time > 0) {
            double ratio = current_time / prev_time;
            std::cout << std::setw(25) << std::fixed << std::setprecision(2) << ratio << "\n";
        } else {
            std::cout << std::setw(25) << "-" << "\n";
        }

        prev_time = current_time;
        prev_N = N;
    }

    std::cout << "---------------------------------------------------------------------------------\n";

    return 0;
}

