#ifndef VEKTORIUSTUDENTOSTRUKTURA_H
#define VEKTORIUSTUDENTOSTRUKTURA_H

#include <vector>
#include <string>

struct StudentasVektorius{
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatas = 0;
};

#endif