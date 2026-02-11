#include "struktura.h"

int main() {
    std::vector<Studentas> studentuSarasas;
    std::string ivestis;
    char pasirinkimas;
    while (true) {
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        std::getline(std::cin, ivestis);
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1) {
            pasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (pasirinkimas == 'V' || pasirinkimas == 'M') break;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
    while (true) {
        std::cout << "Įveskite studentų skaičių: ";
        std::getline(std::cin, ivestis);
        if (tikrintiIvesti(ivestis) && arIvestisSveikasisSkaicius(ivestis, false))
            break;
        std::cout << "Studentų skaičius turi būti sveikasis teigiamas skaičius.\n";
    }
    int studentuSkaicius = std::stoi(ivestis);
    studentuSarasas.reserve(studentuSkaicius);
    for (int i = 0; i < studentuSkaicius; i++){
        Studentas studentas;
        while (true) {
            std::cout << "Įveskite studento vardą: ";
            std::getline(std::cin, studentas.Vardas);
            if (tikrintiIvesti(studentas.Vardas)) break;
            std::cout << "Studento vardas negali likti tuščias.\n";
        }
        while (true) {
            std::cout << "Įveskite studento pavardę: ";
            std::getline(std::cin, studentas.Pavarde);
            if (tikrintiIvesti(studentas.Pavarde)) break;
            std::cout << "Studento pavardė negali likti tuščia.\n";
        }
        while (true) {
            std::cout << "Įveskite studento namų darbų pažymių skaičių: ";
            std::getline(std::cin, ivestis);
            if (tikrintiIvesti(ivestis) && arIvestisSveikasisSkaicius(ivestis, true)) break;
            std::cout << "Studento namų darbų pažymių skaičius turi būti neneigiamas (daugiau arba lygus 0).\n";
        }
        int pazymiuSkaicius = std::stoi(ivestis);
        studentas.namuDarbuTarpiniaiRezultatai.clear();
        studentas.namuDarbuTarpiniaiRezultatai.reserve(pazymiuSkaicius);
        for (int j = 0; j < pazymiuSkaicius; j++) {
            while (true) {
                std::cout << "Įveskite " << pazymiuSkaicius - j << " likusius studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus vieną pažymį, paspauskite klavišą ENTER: ";
                std::getline(std::cin, ivestis);
                if (tikrintiIvesti(ivestis) && arIvestisSveikasisSkaicius(ivestis, true)){
                    int val = std::stoi(ivestis);
                    if (val >= 1 && val <= 10) break;
                }
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            studentas.namuDarbuTarpiniaiRezultatai.push_back(std::stoi(ivestis));
        }
        while (true) {
            std::cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
            std::getline(std::cin, ivestis);
            if (tikrintiIvesti(ivestis) && arIvestisSveikasisSkaicius(ivestis, true)){
                int val = std::stoi(ivestis);
                if (val >= 1 && val <= 10) break;
            }
            std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
        }
        studentas.egzaminoRezultatas = std::stoi(ivestis);
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