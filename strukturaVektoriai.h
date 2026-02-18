#ifndef STRUKTURAVEKTORIAI_H
#define STRUKTURAVEKTORIAI_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <charconv>
#include <random>
#include <chrono>
#include <fstream>
#include <format>

struct StudentasVektorius {
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
};

bool tikrintiIvesti(const std::string& ivestis);
void tvarkytiVarda(const string& ivestis);
void tvarkytiPavarde(const string& ivestis);
double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius);
void parodytiRezultatuLentele(const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis);
int generuotiSveikaSkaiciu(int nuo, int iki);
std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes);

#endif