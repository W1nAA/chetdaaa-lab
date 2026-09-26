#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <chrono>

struct Point {
    double x, y;
};

// ฟังก์ชันคำนวณ Closest Pair แบบ Brute Force ตาม Pseudocode
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
    std::vector<int> N_list = {100, 1000, 5000, 10000, 20000};

    // ตัวสร้างพิกัดสุ่ม
    std::mt19937 rng(1337); // กำหนด Seed เพื่อให้ผลสุ่มคงที่
    std::uniform_real_distribution<double> dist(0.0, 10000.0);

    for (int N : N_list) {
        std::vector<Point> P(N);
        for (int i = 0; i < N; ++i) {
            P[i] = {dist(rng), dist(rng)};
        }

        Point best_p1, best_p2;

        // เริ่มจับเวลา
        auto start = std::chrono::high_resolution_clock::now();

        double min_d = closestPairBruteForce(P, best_p1, best_p2);

        // สิ้นสุดจับเวลา
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        long long num_pairs = (long long)N * (N - 1) / 2;
        std::cout << "N = " << N 
                  << " | Pairs = " << num_pairs 
                  << " | Time = " << elapsed.count() << " ms\n";
    }

    return 0;
}