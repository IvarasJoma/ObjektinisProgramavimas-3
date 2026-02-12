#include "struktura.h"

int main() {
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
    StudentasMasyvas** studentuSarasas = new StudentasMasyvas*[studentuSkaicius];
    for (int i = 0; i < studentuSkaicius; i++){
        studentuSarasas[i] = new StudentasMasyvas();
        while (true) {
            std::cout << "Įveskite studento vardą: ";
            std::getline(std::cin, studentuSarasas[i]->Vardas);
            if (tikrintiIvesti(studentuSarasas[i]->Vardas)) break;
            std::cout << "Studento vardas negali likti tuščias.\n";
        }
        while (true) {
            std::cout << "Įveskite studento pavardę: ";
            std::getline(std::cin, studentuSarasas[i]->Pavarde);
            if (tikrintiIvesti(studentuSarasas[i]->Pavarde)) break;
            std::cout << "Studento pavardė negali likti tuščia.\n";
        }
        while (true) {
            std::cout << "Įveskite studento namų darbų pažymių skaičių: ";
            std::getline(std::cin, ivestis);
            if (tikrintiIvesti(ivestis) && arIvestisSveikasisSkaicius(ivestis, true)) break;
            std::cout << "Studento namų darbų pažymių skaičius turi būti neneigiamas (daugiau arba lygus 0).\n";
        }
        studentuSarasas[i]->namuDarbuKiekis = std::stoi(ivestis);
        int pazymiuSkaicius = studentuSarasas[i]->namuDarbuKiekis;
        studentuSarasas[i]->namuDarbuTarpiniaiRezultatai = new int[pazymiuSkaicius];
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
            studentuSarasas[i]->namuDarbuTarpiniaiRezultatai[j] = std::stoi(ivestis);
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
        studentuSarasas[i]->egzaminoRezultatas = std::stoi(ivestis);
    }
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavardė" << std::setw(18) << (pasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (int i = 0; i < studentuSkaicius; i++) {
        int studentoNamuDarbuKiekis = studentuSarasas[i]->namuDarbuKiekis;
        double galutinisRezultatas = (pasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(*studentuSarasas[i], studentoNamuDarbuKiekis) : skaiciuotiGalutineMediana(*studentuSarasas[i], studentoNamuDarbuKiekis);
        std::cout << std::left << std::setw(15) << studentuSarasas[i]->Vardas << std::setw(15) << studentuSarasas[i]->Pavarde << std::fixed << std::setprecision(2) << galutinisRezultatas << "\n";
    }
    for (int i = 0; i < studentuSkaicius; i++) {
        delete[] studentuSarasas[i]->namuDarbuTarpiniaiRezultatai;
        delete studentuSarasas[i];
    }
    delete[] studentuSarasas;
    return 0;
}