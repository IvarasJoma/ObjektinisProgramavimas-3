#ifndef STRUKTURA_H
#define STRUKTURA_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <charconv>
#include <random>
#include <chrono>

struct StudentasVektorius {
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
};

struct StudentasMasyvas {
    std::string Vardas, Pavarde;
    int* namuDarbuTarpiniaiRezultatai = nullptr;
    int namuDarbuKiekis = 0;
    int namuDarbuTalpa = 0;
    int egzaminoRezultatas = 0;
};

bool tikrintiIvesti(const std::string& ivestis);
double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const StudentasVektorius& studentas);
double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
void parodytiRezultatuLentele(std::vector<StudentasVektorius> studentuSarasas, char pasirinkimas);
void parodytiRezultatuLentele(StudentasMasyvas**& studentuSarasas, int studentuSkaicius, char skaiciavimoMetodoPasirinkimas);
void uztikrintiNamuDarbuMasyvoTalpa(int*& namuDarbuTarpiniaiRezultatai, int& talpa, int pazymiuKiekis, int dydis);
void uztikrintiStudentuMasyvoTalpa(StudentasMasyvas**& studentuSarasas, int& talpa, int studentuSkaicius, int dydis);
void generuotiRezultatus(StudentasVektorius& studentas);
int generuotiSveikusSkaicius(int nuo, int iki);
void generuotiRezultatus(StudentasMasyvas* studentas);

#endif