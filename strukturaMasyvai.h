#ifndef STRUKTURAMASYVAI_H
#define STRUKTURAMASYVAI_H

#include <iostream>

struct StudentasMasyvas{
    std::string Vardas, Pavarde;
    int* namuDarbuTarpiniaiRezultatai = nullptr;
    int namuDarbuKiekis = 0;
    int namuDarbuTalpa = 0;
    int egzaminoRezultatas = 0;
};

double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius);
double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
void parodytiRezultatuLentele(StudentasMasyvas** studentuSarasas, int studentuSkaicius, char skaiciavimoMetodoPasirinkimas);
void uztikrintiNamuDarbuMasyvoTalpa(int*& namuDarbuTarpiniaiRezultatai, int& talpa, int pazymiuKiekis, int dydis);
void uztikrintiStudentuMasyvoTalpa(StudentasMasyvas**& studentuSarasas, int& talpa, int studentuSkaicius, int dydis);
void generuotiRezultatus(StudentasMasyvas* studentas, int maksimalusNDKiekis);
int nuskaitytiEilutesIsFailo(const std::string& failas, std::string*& nuskaitytasMasyvas);
void generuotiVardaPavarde(std::string& vardas, std::string& pavarde, const std::string* vyrVardai, int vyrVarduKiekis, const std::string* vyrPavardes, int vyrPavardziuKiekis, const std::string* motVardai, int motVarduKiekis, const std::string* motPavardes, int motPavardziuKiekis);
void atlaisvintiAtminti(StudentasMasyvas**& studentuSarasas, int& studentuSkaicius, int& talpa);

#endif