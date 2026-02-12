#ifndef STRUKTURA_H
#define STRUKTURA_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> 

struct StudentasVektorius {
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
};

struct StudentasMasyvas {
    std::string Vardas, Pavarde;
    int* namuDarbuTarpiniaiRezultatai = nullptr;
    int namuDarbuKiekis = 0;
    int egzaminoRezultatas = 0;
};

bool tikrintiIvesti(const std::string& ivestis);
bool arIvestisSveikasisSkaicius(const std::string& ivestis, bool leistiNuli);
double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const StudentasVektorius& studentas);
double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);

#endif