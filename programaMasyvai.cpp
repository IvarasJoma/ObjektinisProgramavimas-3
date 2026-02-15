#include "struktura.h"

int main() {
    std::string ivestis;
    char ivestiesPasirinkimas;
    char skaiciavimoMetodoPasirinkimas;
    StudentasMasyvas** studentuSarasas = nullptr;
    int studentuSkaicius = 0;
    int pazymiuSkaicius = 0;
    int talpa = 0;
    while (true){
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1) {
            skaiciavimoMetodoPasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'M') break;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
    while (true){
        std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            ivestiesPasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (ivestiesPasirinkimas == 'T'){
                uztikrintiStudentuMasyvoTalpa(studentuSarasas, talpa, studentuSkaicius, studentuSkaicius + 1);
                studentuSarasas[studentuSkaicius] = new StudentasMasyvas();
                studentuSkaicius++;
            }
            else if (ivestiesPasirinkimas == 'N'){
                parodytiRezultatuLentele(studentuSarasas, studentuSkaicius, skaiciavimoMetodoPasirinkimas);
                break;
            }
            else {
                std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
        } else {
            std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
            continue;
        }    
        while (true) {
            std::cout << "Įveskite studento vardą: ";
            std::getline(std::cin, studentuSarasas[studentuSkaicius - 1]->Vardas);
            if (tikrintiIvesti(studentuSarasas[studentuSkaicius - 1]->Vardas)) break;
            std::cout << "Studento vardas negali likti tuščias.\n";
        }
        while (true) {
            std::cout << "Įveskite studento pavardę: ";
            std::getline(std::cin, studentuSarasas[studentuSkaicius - 1]->Pavarde);
            if (tikrintiIvesti(studentuSarasas[studentuSkaicius - 1]->Pavarde)) break;
            std::cout << "Studento pavardė negali likti tuščia.\n";
        }
        while (true) {
            std::cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus pažymį, paspauskite klavišą ENTER. Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
            std::getline(std::cin, ivestis);
            if (ivestis.empty()){
                break;
            }
            int val = 0;
            auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
            if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10){
                uztikrintiNamuDarbuMasyvoTalpa(studentuSarasas[studentuSkaicius - 1]->namuDarbuTarpiniaiRezultatai, studentuSarasas[studentuSkaicius - 1]->namuDarbuTalpa, studentuSarasas[studentuSkaicius - 1]->namuDarbuKiekis, studentuSarasas[studentuSkaicius - 1]->namuDarbuKiekis + 1);
                studentuSarasas[studentuSkaicius - 1]->namuDarbuTarpiniaiRezultatai[studentuSarasas[studentuSkaicius - 1]->namuDarbuKiekis] = val;
                studentuSarasas[studentuSkaicius - 1]->namuDarbuKiekis++;
                continue;
            } else {
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
        }
        while (true) {
            std::cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
            std::getline(std::cin, ivestis);
            if (!tikrintiIvesti(ivestis)){
                std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                continue;
            }
            int val = 0;
            auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
            if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10){
                studentuSarasas[studentuSkaicius - 1]->egzaminoRezultatas = val;
                break;
            }
            std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
        }    
    }
    for (int i = 0; i < studentuSkaicius; i++) {
        delete[] studentuSarasas[i]->namuDarbuTarpiniaiRezultatai;
        delete studentuSarasas[i];
    }
    delete[] studentuSarasas;
    return 0;
}