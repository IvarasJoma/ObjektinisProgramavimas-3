#ifndef STRUKTURASTUDENTAS_H
#define STRUKTURASTUDENTAS_H

#include <string>

template <typename StudentuKonteineris>
struct Studentas {
    std::string Vardas, Pavarde;
    Container namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatas = 0;
};

#endif