#ifndef STRUKTURASTUDENTAS_H
#define STRUKTURASTUDENTAS_H

#include <string>

struct StudentasOld {
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatas = 0;
};

#endif