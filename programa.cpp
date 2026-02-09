#include "struktura.h"

bool tikrintiIvesti(const std::string& s) {
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) return true;
    } return false;
}

bool arIvestisSveikasisSkaicius(const std::string& s, bool leistiNuli) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    if (!leistiNuli && s[0] == '0') return false;
    if (s.size() > 1 && s[0] == '0')return false;
    return true;
}

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const Studentas& s) {
    double ndVidurkis = skaiciuotiNDVidurki(s.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * s.egzaminoRezultatas;
}

int main() {
    std::vector<Studentas> studentuSarasas;
    std::string input;
    while (true) {
        std::cout << "Iveskite studentų skaičių: ";
        std::getline(std::cin, input);
        if (tikrintiIvesti(input) && arIvestisSveikasisSkaicius(input, false))
            break;
        std::cout << "Studentų skaičius turi būti sveikasis teigiamas skaičius.\n";
    }
    int studentuSkaicius = std::stoi(input);
    studentuSarasas.reserve(studentuSkaicius);
    for (int i = 0; i < studentuSkaicius; i++){
        Studentas studentas;
        while (true) {
            std::cout << "Iveskite studento vardą: ";
            std::getline(std::cin, studentas.Vardas);
            if (tikrintiIvesti(studentas.Vardas)) break;
            std::cout << "Studento vardas negali likti tuščias.\n";
        }
        while (true) {
            std::cout << "Iveskite studento pavardę: ";
            std::getline(std::cin, studentas.Pavarde);
            if (tikrintiIvesti(studentas.Pavarde)) break;
            std::cout << "Studento pavardė negali likti tuščia.\n";
        }
        while (true) {
            std::cout << "Iveskite studento namų darbų pažymių skaičių: ";
            std::getline(std::cin, input);
            if (tikrintiIvesti(input) && arIvestisSveikasisSkaicius(input, true)) break;
            std::cout << "Studento namų darbų pažymių skaičius turi būti neneigiamas (daugiau arba lygus 0).\n";
        }
        int pazymiuSkaicius = std::stoi(input);
        studentas.namuDarbuTarpiniaiRezultatai.clear();
        studentas.namuDarbuTarpiniaiRezultatai.reserve(pazymiuSkaicius);
        for (int j = 0; j < pazymiuSkaicius; j++) {
            while (true) {
                std::cout << "Iveskite " << pazymiuSkaicius - j << " likusius studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus vieną pažymį, paspauskite klavišą ENTER: ";
                std::getline(std::cin, input);
                if (tikrintiIvesti(input) && arIvestisSveikasisSkaicius(input, true)){
                    int val = std::stoi(input);
                    if (val >= 1 && val <= 10) break;
                }
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            studentas.namuDarbuTarpiniaiRezultatai.push_back(std::stoi(input));
        }
        while (true) {
            std::cout << "Iveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
            std::getline(std::cin, input);
            if (tikrintiIvesti(input) && arIvestisSveikasisSkaicius(input, true)){
                int val = std::stoi(input);
                if (val >= 1 && val <= 10) break;
            }
            std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
        }
        studentas.egzaminoRezultatas = std::stoi(input);
        studentuSarasas.push_back(std::move(studentas));
    }
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavardė" << std::setw(18) << "Galutinis (Vid.)" << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
        std::cout << std::left << std::setw(15) << studentas.Vardas << std::setw(15) << studentas.Pavarde << std::fixed << std::setprecision(2) << galutinisVidurkis << "\n";
    }
    return 0;
}