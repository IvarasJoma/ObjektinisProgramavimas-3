#include <chrono>
#include <cstdio>
#include <vector>
#include <algorithm>
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
    std::sort(times, times + RUNS);
    return times[RUNS / 2];
}

int main() {
    const unsigned int sizes[] = {
        10000, 100000, 1000000, 10000000, 100000000
    };

    printf("%-15s %14s %14s %10s\n", "Elementų skaičius", "std::vector", "Vector klasė", "Skirtumas");
    printf("%s\n", std::string(57, '-').c_str());

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

        char sz_buf[16];
        if      (sz >= 100'000'000) snprintf(sz_buf, sizeof(sz_buf), "100 000 000");
        else if (sz >=  10'000'000) snprintf(sz_buf, sizeof(sz_buf), " 10 000 000");
        else if (sz >=   1'000'000) snprintf(sz_buf, sizeof(sz_buf), "  1 000 000");
        else if (sz >=     100'000) snprintf(sz_buf, sizeof(sz_buf), "    100 000");
        else                        snprintf(sz_buf, sizeof(sz_buf), "     10 000");

        printf("%-15s %13.6f ms %13.6f ms %9.3fx\n",
               sz_buf, t_std, t_vec, ratio);
    }
    return 0;
}