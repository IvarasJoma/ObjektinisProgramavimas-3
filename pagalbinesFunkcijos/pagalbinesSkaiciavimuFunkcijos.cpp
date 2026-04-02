#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include <algorithm>

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const Studentas& studentas){
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiNDMediana(std::vector<int> ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    std::size_t n = ndPazymiai.size();
    if (n % 2 == 1) return ndPazymiai[n / 2];
    else return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
}

double skaiciuotiGalutineMediana(const Studentas& studentas){
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void apskaiciuotiGalutiniPazymi(Studentas& studentas, char skaiciavimoMetodoPasirinkimas){
    if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v'){
        double galutinisRezultatasPagalVidurki = skaiciuotiGalutiniVidurki(studentas);
        studentas.galutinisRezultatas = galutinisRezultatasPagalVidurki;
    } else{
        double galutinisRezultatasPagalMediana = skaiciuotiGalutineMediana(studentas);
        studentas.galutinisRezultatas = galutinisRezultatasPagalMediana;
    }
}

void apskaiciuotiGalutiniusPazymius(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    for (auto& studentas : studentuSarasas) apskaiciuotiGalutiniPazymi(studentas, skaiciavimoMetodoPasirinkimas);
}

void suskirstytiStudentus(const std::vector<Studentas>& studentuSarasas, std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas){
    pazangiuSarasas.clear();
    silpnuSarasas.clear();
    pazangiuSarasas.reserve(studentuSarasas.size() / 2);
    silpnuSarasas.reserve(studentuSarasas.size() / 2);
    for (auto& studentas : studentuSarasas) {
        if (studentas.galutinisRezultatas < 5) silpnuSarasas.push_back(std::move(studentas));
        else pazangiuSarasas.push_back(std::move(studentas));
    }
}