#include <iostream>
#include <string>
#include <vector>
#include "Studentas.h"
#include "../strukturosFailai/strukturaVisi.h"


Studentas::Studentas(const char* eilute, std::size_t namuDarbuKiekis) : examGrade_(0) {
    const char* pointer = eilute;
    std::string name;
    std::string surname;
    if (!nuskaitytiZodiIsFailo(pointer, name)) throw std::runtime_error("Nepavyko nuskaityti studento vardo");
    if (!nuskaitytiZodiIsFailo(pointer, surname)) throw std::runtime_error("Nepavyko nuskaityti studento pavardes");
    name_ = std::move(name);
    surname_ = std::move(surname);
    homeworkGrades_.reserve(namuDarbuKiekis);
    for (std::size_t i = 0; i < namuDarbuKiekis; i++) {
        int tempGrade;
        if (!nuskaitytiSveikaSkaiciuIsFailo(pointer, tempGrade)) tempGrade = 0;
        homeworkGrades_.push_back(tempGrade);
    }
    int examGrade = 0;
    if (!nuskaitytiSveikaSkaiciuIsFailo(pointer, examGrade)) examGrade = 0;
    examGrade_ = examGrade;
}

Studentas::Studentas(bool generuotiPazymius, int ndKiekis) : examGrade_(0) {
    name_ = nuskaitytiVardaArPavarde("Įveskite studento vardą: ", tvarkytiVarda, "Studento vardas negali būti tuščia eilutė.");
    surname_ = nuskaitytiVardaArPavarde("Įveskite studento pavardę: ", tvarkytiPavarde, "Studento pavardė negali būti tuščia eilutė.");
    if (generuotiPazymius) for (int i = 0; i < ndKiekis; ++i) homeworkGrades_.push_back(generuotiSveikaSkaiciu(1, 10));
    else for (int i = 0; i < ndKiekis; ++i) homeworkGrades_.push_back(nuskaitytiPazymiNuo1iki10("Įveskite namų darbo pažymį (1-10): "));
    examGrade_ = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ");
}

double Studentas::calculateFinalGrade(char method) const {
    if (homeworkGrades_.empty()) return 0.6 * examGrade_;
    double finalHomeworkGrade = 0.0;
    if (method == 'V' || method == 'v') {
        double sum = std::accumulate(homeworkGrades_.begin(), homeworkGrades_.end(), 0.0);
        finalHomeworkGrade = sum / homeworkGrades_.size();
    } else {
        std::vector<int> temp = homeworkGrades_;
        std::sort(temp.begin(), temp.end());
        std::size_t n = temp.size();
        if (n % 2 == 0) {
            finalHomeworkGrade = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
        } else {
            finalHomeworkGrade = temp[n / 2];
        }
    }
    return 0.4 * finalHomeworkGrade + 0.6 * examGrade_;
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << s.name_ << ' ' << s.surname_ << ' ' << s.homeworkGrades_.size();
    for (const int homeworkGrade : s.homeworkGrades_) os << ' ' << homeworkGrade;
    os << ' ' << s.examGrade_;
    return os;
}
