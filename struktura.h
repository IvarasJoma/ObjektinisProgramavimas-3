#ifndef STRUKTURA_H
#define STRUKTURA_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> 

struct Studentas {
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
};

#endif