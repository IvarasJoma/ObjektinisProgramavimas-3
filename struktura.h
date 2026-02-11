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

bool tikrintiIvesti(const std::string& ivestis);
bool arIvestisSveikasisSkaicius(const std::string& ivestis, bool leistiNuli);
double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const Studentas& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const Studentas& studentas);

#endif