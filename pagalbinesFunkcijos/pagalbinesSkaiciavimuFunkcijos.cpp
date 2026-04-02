#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include <algorithm>

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0.0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiNDMediana(std::vector<int> ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    std::size_t n = ndPazymiai.size();
    return (n % 2 == 1) ? ndPazymiai[n / 2] : (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
}

double skaiciuotiGalutiniPazymi(const Studentas& studentas, char skaiciavimoMetodoPasirinkimas) {
    double ndRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v') ? skaiciuotiNDVidurki(studentas.getHomeworkGrades()) : skaiciuotiNDMediana(studentas.getHomeworkGrades());
    return 0.4 * ndRezultatas + 0.6 * studentas.egzaminoRezultatas;
}

void suskirstytiStudentus(const std::vector<Studentas>& studentuSarasas, std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas) {
    pazangiuSarasas.clear();
    silpnuSarasas.clear();
    pazangiuSarasas.reserve(studentuSarasas.size() / 2);
    silpnuSarasas.reserve(studentuSarasas.size() / 2);
    for (const auto& studentas : studentuSarasas) studentas.calculateFinalGrade() < 5) ? silpnuSarasas.push_back(studentas); : pazangiuSarasas.push_back(studentas);
}