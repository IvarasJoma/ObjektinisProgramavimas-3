#include <chrono>
#include <print>
#include <format>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "Vector.h"

using Clock = std::chrono::high_resolution_clock;
static constexpr int RUNS = 100;

template<typename Fn>
double measure_ms(Fn&& fn) {
    double times[RUNS];
    for (int r = 0; r < RUNS; ++r) {
        auto t0 = Clock::now();
        fn();
        auto t1 = Clock::now();
        times[r] = std::chrono::duration<double, std::milli>(t1 - t0).count();
    }
    return std::accumulate(times, times + RUNS, 0.0) / RUNS;
}

int main() {
    const unsigned int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    std::println("{:<15} {:>14} {:>14} {:>10}", "Elementų skaičius", "std::vector", "Vector klasė", "Skirtumas");
    std::println("{}", std::string(57, '-'));
    for (unsigned int sz : sizes) {
        double t_std = measure_ms([&] {
            std::vector<int> v1;
            for (unsigned int i = 1; i <= sz; ++i) v1.push_back(i);
        });
        double t_vec = measure_ms([&] {
            Vector<int> v2;
            for (unsigned int i = 1; i <= sz; ++i) v2.push_back(i);
        });
        double ratio = t_vec / t_std;
        std::println("{:<15} {:>13.6f} ms {:>13.6f} ms {:>9.3f}x", sz, t_std, t_vec, ratio);
    }
}