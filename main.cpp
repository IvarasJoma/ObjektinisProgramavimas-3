#include <iostream>

int main() {
    try {
        StatiniaiDuomenys statiniaiDuomenys;
        IvestiesServisas ivestis;
        IsvestiesServisas isvestis;
        FailuServisas failai;
        StudentuGeneratorius generatorius(statiniaiDuomenys);
        BenchmarkService benchmarkai;

        ProgramosValdiklis programa(
            ivestis,
            isvestis,
            failai,
            generatorius,
            benchmarkai,
            statiniaiDuomenys
        );

        programa.paleisti();
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << '\n';
        return 1;
    }
}