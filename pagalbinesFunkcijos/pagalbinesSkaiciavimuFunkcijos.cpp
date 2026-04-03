#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include <algorithm>

void suskirstytiStudentus(const std::vector<Studentas>& studentuSarasas, std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas) {
    pazangiuSarasas.clear();
    silpnuSarasas.clear();
    pazangiuSarasas.reserve(studentuSarasas.size() / 2);
    silpnuSarasas.reserve(studentuSarasas.size() / 2);
    for (const auto& studentas : studentuSarasas){
        if (studentas.getFinalGrade() < 5) silpnuSarasas.push_back(studentas);
        else pazangiuSarasas.push_back(studentas);
    }
}

void apskaiciuotiGalutiniusPazymius(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    for (auto& studentas : studentuSarasas) studentas.setFinalGrade(studentas.calculateFinalGrade(skaiciavimoMetodoPasirinkimas));
}