#include "struktura.h"

bool tikrintiIvesti(const std::string& ivestis) {
    for (char simbolis : ivestis) {
        if (!std::isspace(static_cast<unsigned char>(simbolis))) return true;
    } return false;
}

bool arIvestisSveikasisSkaicius(const std::string& ivestis, bool leistiNuli) {
    if (ivestis.empty()) return false;
    for (char simbolis : ivestis) {
        if (!std::isdigit(static_cast<unsigned char>(simbolis))) return false;
    }
    if (!leistiNuli && ivestis[0] == '0') return false;
    if (ivestis.size() > 1 && ivestis[0] == '0')return false;
    return true;
}

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const Studentas& studentas) {
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

double skaiciuotiGalutineMediana(const Studentas& studentas) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}