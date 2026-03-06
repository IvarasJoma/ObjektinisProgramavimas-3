#include "strukturaSkaiciavimai.h"
#include <algorithm>

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas){
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

double skaiciuotiGalutineMediana(const StudentasVektorius& studentas){
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void apskaiciuotiGalutiniPazymi(StudentasVektorius& studentas, char skaiciavimoMetodoPasirinkimas){
    if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v'){
        double galutinisRezultatasPagalVidurki = skaiciuotiGalutiniVidurki(studentas);
        studentas.galutinisRezultatas = galutinisRezultatasPagalVidurki;
    } else {
        double galutinisRezultatasPagalMediana = skaiciuotiGalutineMediana(studentas);
        studentas.galutinisRezultatas = galutinisRezultatasPagalMediana;
    }
}