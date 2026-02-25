#ifndef STRUKTURASTUDENTAS_H
#define STRUKTURASTUDENTAS_H

#include <vector>

struct StudentasVektorius{
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatasPagalVidurki = 0;
    double galutinisRezultatasPagalMediana = 0;
};

#endif