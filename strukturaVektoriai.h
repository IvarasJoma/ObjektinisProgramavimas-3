#ifndef STRUKTURAVEKTORIAI_H
#define STRUKTURAVEKTORIAI_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

struct StudentasVektorius{
    std::string Vardas, Pavarde;
    std::vector<int> namuDarbuTarpiniaiRezultatai;
    int egzaminoRezultatas;
    double galutinisRezultatasPagalVidurki = 0;
    double galutinisRezultatasPagalMediana = 0;
    int vardasNr = -1;
    int pavardeNr = -1;
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
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, int kiekis);
template<typename T, typename Member> auto lygintiElementusPagalDidejanciaReiksme(Member T::*member) { return [member](const T& a, const T& b) { return a.*member < b.*member; }; }
template<typename T, typename Member> auto lygintiElementusPagalMazejanciaReiksme(Member T::*member) { return [member](const T& a, const T& b) { return a.*member > b.*member; }; }
template<typename T> auto lygintiVardaSuSkaiciaisDidejanciaTvarka(int T::*numMember, std::string T::*strMember) { return [numMember, strMember](const T& a, const T& b) { const int na = a.*numMember; const int nb = b.*numMember; const bool aTuriSkaiciu = na >= 0; const bool bTuriSkaiciu = nb >= 0; if (aTuriSkaiciu && bTuriSkaiciu) { if (na != nb) return na < nb; return (a.*strMember) < (b.*strMember);} return (a.*strMember) < (b.*strMember);};}
template<typename T> auto lygintiVardaSuSkaiciaisMazejanciaTvarka(int T::*numMember, std::string T::*strMember) { return [numMember, strMember](const T& a, const T& b) { const int na = a.*numMember; const int nb = b.*numMember; const bool aTuriSkaiciu = na >= 0; const bool bTuriSkaiciu = nb >= 0; if (aTuriSkaiciu && bTuriSkaiciu) { if (na != nb) return na > nb; return (a.*strMember) > (b.*strMember);} return (a.*strMember) > (b.*strMember);};}
void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas);
double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga);

#endif