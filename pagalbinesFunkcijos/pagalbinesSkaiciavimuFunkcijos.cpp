#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include <algorithm>

double gautiVidurki(const std::vector<int>& ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double gautiMediana(std::vector<int> ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    std::size_t n = ndPazymiai.size();
    if (n % 2 == 1) return ndPazymiai[n / 2];
    else return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
}

void apskaiciuotiGalutiniusPazymius(std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    for (auto& studentas : studentuSarasas) apskaiciuotiGalutiniPazymi(studentas, skaiciavimoMetodoPasirinkimas);
}

void suskirstytiStudentus(const std::vector<StudentasVektorius>& studentuSarasas, std::vector<StudentasVektorius>& pazangiuSarasas, std::vector<StudentasVektorius>& silpnuSarasas){
    pazangiuSarasas.clear();
    silpnuSarasas.clear();
    pazangiuSarasas.reserve(studentuSarasas.size() / 2);
    silpnuSarasas.reserve(studentuSarasas.size() / 2);
    for (auto& studentas : studentuSarasas) {
        if (studentas.galutinisRezultatas < 5) silpnuSarasas.push_back(std::move(studentas));
        else pazangiuSarasas.push_back(std::move(studentas));
    }
}