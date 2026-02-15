#include "struktura.h"

int main(){
    std::vector<StudentasVektorius> studentuSarasas;
    std::string ivestis;
    char skaiciavimoMetodoPasirinkimas;
    char ivestiesPasirinkimas;
    char pazymiuIvedimoBudas;
    while (true){
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            skaiciavimoMetodoPasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'M') break;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
    while (true) {
        std::cout << "Pažymių įvedimas: I - įvesti ranka, A - atsitiktinai generuoti: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1) {
            pazymiuIvedimoBudas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (pazymiuIvedimoBudas == 'I' || pazymiuIvedimoBudas == 'A') break;
        }
        std::cout << "Įveskite TIK vieną raidę: I arba A.\n";
    }
    while(true){
        StudentasVektorius studentas;
        while (true){
            std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
            if (!std::getline(std::cin, ivestis)) return 0;
            if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
                ivestiesPasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
                if (ivestiesPasirinkimas == 'T') break;
                if (ivestiesPasirinkimas == 'N'){
                    parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
                    return 0;
                }
            }
            std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
        }
        while (true){
            std::cout << "Įveskite studento vardą: ";
            if (!std::getline(std::cin, studentas.Vardas)) return 0;
            if (tikrintiIvesti(studentas.Vardas)) break;
            std::cout << "Studento vardas negali likti tuščias.\n";
        }
        while (true){
            std::cout << "Įveskite studento pavardę: ";
            if (!std::getline(std::cin, studentas.Pavarde)) return 0;
            if (tikrintiIvesti(studentas.Pavarde)) break;
            std::cout << "Studento pavardė negali likti tuščia.\n";
        }
        if (pazymiuIvedimoBudas == 'A') {
            generuotiRezultatus(studentas);
            std::cout << "Sugeneruoti ND pažymiai: ";
            for (int x : studentas.namuDarbuTarpiniaiRezultatai) std::cout << x << ' ';
            std::cout << "\nSugeneruotas egzamino pažymys: " << studentas.egzaminoRezultatas << "\n";
        } else {
            studentas.namuDarbuTarpiniaiRezultatai.clear();
            while (true) {
                std::cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (ivestis.empty()) break;
                int val = 0;
                auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10){
                    studentas.namuDarbuTarpiniaiRezultatai.push_back(val);
                    continue;
                }
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            while (true) {
                std::cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (!tikrintiIvesti(ivestis)){
                    std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                    continue;
                }
                int val = 0;
                auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    studentas.egzaminoRezultatas = val;
                    break;
                }
                std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
        }
        studentuSarasas.push_back(std::move(studentas));
    }
}