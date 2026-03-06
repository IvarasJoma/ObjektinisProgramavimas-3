#ifndef STRUKTURATESTAVIMAS_H
#define STRUKTURATESTAVIMAS_H

#include "../strukturosFailai/Failai.h"
#include <chrono>

struct TestoLaikai {
    double nuskaitymas = 0.0;
    double skaiciavimas = 0.0;
    double rikiavimas = 0.0;
    double isvedimas = 0.0;
    double bendras() const {
        return nuskaitymas + skaiciavimas + rikiavimas + isvedimas;
    }
    void padalintiIs(int kiekis) {
        nuskaitymas /= kiekis;
        skaiciavimas /= kiekis;
        rikiavimas /= kiekis;
        isvedimas /= kiekis;
    }
};

double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga);

template <typename Func> double ismatuotiLaika(Func veiksmas) {
    auto pradzia = std::chrono::steady_clock::now();
    veiksmas();
    auto pabaiga = std::chrono::steady_clock::now();
    return apskaiciuotiLaika(pradzia, pabaiga);
}

void vykdytiTestavima(Failai& failai);

#endif