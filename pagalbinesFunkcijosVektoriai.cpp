#include "strukturaVektoriai.h"
#include "bendraStruktura.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <charconv>
#include <format>
#include <sstream>
#include <fstream>

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiNDMediana(std::vector<int> ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    int n = (int)ndPazymiai.size();
    if (n % 2 == 1) {
        return ndPazymiai[n / 2];
    } else {
        return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
    }
}

double skaiciuotiGalutineMediana(const StudentasVektorius& studentas) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void parodytiRezultatuLentele(const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::string(56, '-') << "\n";
    std::cout << std::format("{:<18} {:<18} {:<20}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    std::cout << std::string(56, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        std::cout << std::format("{:<18} {:<18} {:<20.2f}\n", studentas.Vardas, studentas.Pavarde, galutinisRezultatas);
    }
}

void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis) {
    studentas.namuDarbuTarpiniaiRezultatai.clear();
    studentas.namuDarbuTarpiniaiRezultatai.reserve(maksimalusNDKiekis);
    for (int i = 0; i < maksimalusNDKiekis; ++i) {
        studentas.namuDarbuTarpiniaiRezultatai.push_back(generuotiSveikaSkaiciu(1, 10));
    }
    for (int i = maksimalusNDKiekis; i < maksimalusNDKiekis; ++i){
        studentas.namuDarbuTarpiniaiRezultatai.push_back(0);
    }
    studentas.egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()) {
        studentas.Vardas = "Vardenis";
        studentas.Pavarde = "Pavardenis";
        return;
    }
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0) {
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)vyrVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)vyrPavardes.size() - 1);
        studentas.Vardas = vyrVardai[vardoIndeksas];
        studentas.Pavarde = vyrPavardes[pavardesIndeksas];
    }
    else {
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)motVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)motPavardes.size() - 1);
        studentas.Vardas = motVardai[vardoIndeksas];
        studentas.Pavarde = motPavardes[pavardesIndeksas];
    }
}

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas){
    std::vector<std::string> rezultatas;
    std::ifstream fin(failas);
    if (!fin) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return rezultatas;
    }
    std::string eilute;
    while (getline(fin, eilute)) {
        if (!eilute.empty()) {
            rezultatas.push_back(eilute);
        }
    }
    return rezultatas;
}

void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai) {
    namuDarbuPazymiai.clear();
    while (true) {
        std::cout << "Įveskite studento namų darbų pažymius (1-10). Po kiekvieno įvesto pažymio paspauskite klavišą ENTER. Baigus tuščioje eilutėje paspauskite klavišą ENTER: ";
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        if (ivestis.empty()) break;
        int reiksme = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= 1 && reiksme <= 10) {
            namuDarbuPazymiai.push_back(reiksme);
        } else {
            std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
        }
    }
}