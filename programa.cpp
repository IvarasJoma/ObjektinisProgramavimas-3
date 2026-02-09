#include "struktura.h"

bool tikrintiIvesti(const std::string& string) {
    for (char c : string) {
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

double skaiciuotiGalutineMediana(const Studentas& s) {
    double ndMediana = skaiciuotiNDMediana(s.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * s.egzaminoRezultatas;
}

int main() {
    std::vector<Studentas> studentuSarasas;
    std::string input;
    char pasirinkimas;
    while (true) {
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        std::getline(std::cin, input);
        if (tikrintiIvesti(input) && input.size() == 1) {
            pasirinkimas = (char)std::toupper(static_cast<unsigned char>(input[0]));
            if (pasirinkimas == 'V' || pasirinkimas == 'M') break;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
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
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavardė" << std::setw(18) << (pasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisRezultatas = (pasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        std::cout << std::left << std::setw(15) << studentas.Vardas << std::setw(15) << studentas.Pavarde << std::fixed << std::setprecision(2) << galutinisRezultatas << "\n";
    }
    return 0;
}