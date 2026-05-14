#include <print>
#include <vector>
#include "Vector.h"

int main() {
    const unsigned int N = 100000000;
    int std_reallocations = 0;
    {
        std::vector<int> v;
        for (unsigned int i = 1; i <= N; ++i) {
            if (v.size() == v.capacity())
                ++std_reallocations;
            v.push_back(i);
        }
    }
    int my_reallocations = 0;
    {
        Vector<int> v;
        for (unsigned int i = 1; i <= N; ++i) {
            if (v.size() == v.capacity())
                ++my_reallocations;
            v.push_back(i);
        }
    }
    std::println("Elementų skaičius:       {:>12}", N);
    std::println("std::vector perskirstymai: {:>10}", std_reallocations);
    std::println("Vector      perskirstymai: {:>10}", my_reallocations);
}