#include "strukturaMasyvai.h"
#include "bendraStruktura.h"

#include <iostream>
#include <algorithm>
#include <charconv>
#include <format>
#include <sstream>
#include <fstream>

double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    double suma = 0.0;
    for (int i = 0; i < pazymiuSkaicius; i++) suma += namuDarbuTarpiniaiRezultatai[i];
    return suma / pazymiuSkaicius;
}

double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    std::sort(namuDarbuTarpiniaiRezultatai, namuDarbuTarpiniaiRezultatai + pazymiuSkaicius);
    if (pazymiuSkaicius % 2 == 1) return namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2];
    return (namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2 - 1] + namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2]) / 2.0;
}

double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void parodytiRezultatuLentele(StudentasMasyvas** studentuSarasas, int studentuSkaicius, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::string(56, '-') << "\n";
    std::cout << std::format("{:<18} {:<18} {:<20}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    std::cout << std::string(56, '-') << "\n";
    for (int i = 0; i < studentuSkaicius; i++) {
        int studentoNamuDarbuKiekis = studentuSarasas[i]->namuDarbuKiekis;
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ) ? skaiciuotiGalutiniVidurki(*studentuSarasas[i], studentoNamuDarbuKiekis) : skaiciuotiGalutineMediana(*studentuSarasas[i], studentoNamuDarbuKiekis);
        std::cout << format("{:<18} {:<18} {:<20.2f}\n", studentuSarasas[i]->Vardas, studentuSarasas[i]->Pavarde, galutinisRezultatas);
    }
}

void uztikrintiStudentuMasyvoTalpa(StudentasMasyvas**& studentuSarasas, int& talpa, int studentuSkaicius, int dydis){
    if (dydis <= talpa) return;
    int naujaTalpa = (talpa == 0) ? 2 : talpa * 2;
    while (naujaTalpa < dydis) naujaTalpa *= 2;
    StudentasMasyvas** naujasMasyvas = new StudentasMasyvas*[naujaTalpa];
    for (int i = 0; i < studentuSkaicius; i++) naujasMasyvas[i] = studentuSarasas[i];
    for (int i = studentuSkaicius; i < naujaTalpa; i++) naujasMasyvas[i] = nullptr;
    delete[] studentuSarasas;
    studentuSarasas = naujasMasyvas;
    talpa = naujaTalpa;
}

void uztikrintiNamuDarbuMasyvoTalpa(int*& namuDarbuTarpiniaiRezultatai, int& talpa, int pazymiuKiekis, int dydis){
    if (dydis <= talpa) return;
    int naujaTalpa = (talpa == 0) ? 2 : talpa * 2;
    while (naujaTalpa < dydis) naujaTalpa *= 2;
    int* naujasMasyvas = new int[naujaTalpa];
    for (int i = 0; i < pazymiuKiekis; i++) naujasMasyvas[i] = namuDarbuTarpiniaiRezultatai[i];
    delete[] namuDarbuTarpiniaiRezultatai;
    namuDarbuTarpiniaiRezultatai = naujasMasyvas;
    talpa = naujaTalpa;
}

void generuotiRezultatus(StudentasMasyvas* studentas, int maksimalusNDKiekis) {
    delete[] studentas->namuDarbuTarpiniaiRezultatai;
    studentas->namuDarbuTarpiniaiRezultatai = nullptr;
    studentas->namuDarbuKiekis = 0;
    studentas->namuDarbuTalpa = 0;
    uztikrintiNamuDarbuMasyvoTalpa(studentas->namuDarbuTarpiniaiRezultatai, studentas->namuDarbuTalpa, studentas->namuDarbuKiekis, maksimalusNDKiekis);
    for (int i = 0; i < maksimalusNDKiekis; ++i) {
        studentas->namuDarbuTarpiniaiRezultatai[studentas->namuDarbuKiekis] = generuotiSveikaSkaiciu(1, 10);
        studentas->namuDarbuKiekis++;
    }
    for (int i = maksimalusNDKiekis; i < maksimalusNDKiekis; ++i){
        studentas->namuDarbuTarpiniaiRezultatai[studentas->namuDarbuKiekis] = 0;
        studentas->namuDarbuKiekis++;
    }
    studentas->egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

int nuskaitytiEilutesIsFailo(const std::string& failas, std::string*& nuskaitytasMasyvas) {
    nuskaitytasMasyvas = nullptr;
    std::ifstream fin(failas);
    if (!fin) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return 0;
    }
    int kiekis = 0;
    std::string eilute;
    while (getline(fin, eilute)) {
        if (!eilute.empty()) kiekis++;
    }
    if (kiekis == 0) return 0;
    nuskaitytasMasyvas = new std::string[kiekis];
    fin.clear();
    fin.seekg(0);
    int i = 0;
    while (getline(fin, eilute)) {
        if (eilute.empty()) continue;
        if (i < kiekis) nuskaitytasMasyvas[i++] = eilute;
    }
    return i;
}

void generuotiVardaPavarde(std::string& vardas, std::string& pavarde, const std::string* vyrVardai, int vyrVarduKiekis, const std::string* vyrPavardes, int vyrPavardziuKiekis, const std::string* motVardai, int motVarduKiekis, const std::string* motPavardes, int motPavardziuKiekis){
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0) {
        if (vyrVarduKiekis <= 0 || vyrPavardziuKiekis <= 0) {
            vardas = "Vardenis";
            pavarde = "Pavardenis";
            return;
        }
        int vardoIndeksas = generuotiSveikaSkaiciu(0, vyrVarduKiekis - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, vyrPavardziuKiekis - 1);
        vardas = vyrVardai[vardoIndeksas];
        pavarde = vyrPavardes[pavardesIndeksas];
    } else {
        if (motVarduKiekis <= 0 || motPavardziuKiekis <= 0) {
            vardas = "Vardenė";
            pavarde = "Pavardenė";
            return;
        }
        int vardoIndeksas = generuotiSveikaSkaiciu(0, motVarduKiekis - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, motPavardziuKiekis - 1);
        vardas = motVardai[vardoIndeksas];
        pavarde = motPavardes[pavardesIndeksas];
    }
}

void atlaisvintiAtminti(StudentasMasyvas**& studentuSarasas, int& studentuSkaicius, int& talpa){
    if (!studentuSarasas){
        studentuSkaicius = 0;
        talpa = 0;
        return;
    }
    for (int i = 0; i < studentuSkaicius; i++) {
        delete[] studentuSarasas[i]->namuDarbuTarpiniaiRezultatai;
        delete studentuSarasas[i];
    }
    delete[] studentuSarasas;
    studentuSarasas = nullptr;
    studentuSkaicius = 0;
    talpa = 0;
}