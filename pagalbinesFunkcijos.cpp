#include "struktura.h"

bool tikrintiIvesti(const std::string& ivestis) {
    for (char simbolis : ivestis) {
        if (!std::isspace(static_cast<unsigned char>(simbolis))) return true;
    } return false;
}

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    double suma = 0.0;
    for (int i = 0; i < pazymiuSkaicius; i++) suma += namuDarbuTarpiniaiRezultatai[i];
    return suma / pazymiuSkaicius;
}

double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
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

double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    std::sort(namuDarbuTarpiniaiRezultatai, namuDarbuTarpiniaiRezultatai + pazymiuSkaicius);
    if (pazymiuSkaicius % 2 == 1) return namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2];
    return (namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2 - 1] + namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2]) / 2.0;
}

double skaiciuotiGalutineMediana(const StudentasVektorius& studentas) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void parodytiRezultatuLentele(std::vector<StudentasVektorius> studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(14) << "Pavardė" << std::setw(18) << (skaiciavimoMetodoPasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        std::cout << std::left << std::setw(15) << studentas.Vardas << std::setw(14) << studentas.Pavarde << std::fixed << std::setprecision(2) << galutinisRezultatas << "\n";
    }
}