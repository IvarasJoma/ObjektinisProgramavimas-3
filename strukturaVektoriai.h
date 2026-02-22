#ifndef STRUKTURAVEKTORIAI_H
#define STRUKTURAVEKTORIAI_H

#include <iostream>
#include <vector>

struct StudentasVektorius{
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatasPagalVidurki = 0;
    double galutinisRezultatasPagalMediana = 0;
};

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
void parodytiRezultatuLentele(const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis);
std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes);
void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);
std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);
template<typename T, typename Member> auto lygintiElementusPagalReiksme(Member T::*member) { return [member](const T& a, const T& b) { return a.*member < b.*member; }; }
void parodytiRezultatuLentele(const std::vector<StudentasVektorius>& studentuSarasas);

#endif