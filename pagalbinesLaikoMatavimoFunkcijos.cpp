#include "strukturaGeneravimas.h"
#include <chrono>

double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga){
    return std::chrono::duration<double>(pabaiga - startas).count();
}