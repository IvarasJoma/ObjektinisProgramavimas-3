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
void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes);
void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);
std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, int kiekis);
void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas);
double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga);

template<typename Tipas, typename LaukoTipas> auto lygintiElementusPagalDidejanciaReiksme(LaukoTipas Tipas::*laukoRodykle){ 
    return [LaukoTipas](const Tipas& a, const Tipas& b){ 
        return a.*laukoRodykle < b.*laukoRodykle; 
    }; 
}
template<typename Tipas, typename LaukoTipas> auto lygintiElementusPagalMazejanciaReiksme(LaukoTipas Tipas::*laukoRodykle){
    return [LaukoTipas](const Tipas& a, const Tipas& b){
        return a.*laukoRodykle > b.*laukoRodykle;
    };
}
template<typename Tipas> auto lygintiVardaSuSkaiciaisDidejanciaTvarka(int Tipas::*SkaiciausLaukas, std::string Tipas::*TekstoLaukas){
    return [SkaiciausLaukas, TekstoLaukas](const Tipas& a, const Tipas& b){
        const int pirmas = a.*SkaiciausLaukas;
        const int antras = b.*SkaiciausLaukas;
        const bool arPirmasTuriSkaiciu = pirmas >= 0;
        const bool arAntrasTuriSkaiciu = antras >= 0;
        if (arPirmasTuriSkaiciu && arAntrasTuriSkaiciu){
            if (pirmas != antras) return pirmas < antras;
            return (a.*TekstoLaukas) < (b.*TekstoLaukas);
        } 
        return (a.*TekstoLaukas) < (b.*TekstoLaukas);
    };
}

template<typename Tipas> auto lygintiVardaSuSkaiciaisMazejanciaTvarka(int Tipas::*SkaiciausLaukas, std::string Tipas::*TekstoLaukas){
    return [SkaiciausLaukas, TekstoLaukas](const Tipas& a, const Tipas& b){
        const int pirmas = a.*SkaiciausLaukas;
        const int antras = b.*SkaiciausLaukas;
        const bool arPirmasTuriSkaiciu = pirmas >= 0;
        const bool arAntrasTuriSkaiciu = antras >= 0;
        if (arPirmasTuriSkaiciu && arAntrasTuriSkaiciu){
            if (pirmas != antras) return pirmas > antras;
            return (a.*TekstoLaukas) > (b.*TekstoLaukas);
        }
        return (a.*TekstoLaukas) > (b.*TekstoLaukas);
    };
}

#endif