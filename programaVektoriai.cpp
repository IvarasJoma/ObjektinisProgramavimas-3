#include "strukturaVektoriai.h"

int main(){
    std::vector<StudentasVektorius> studentuSarasas;
    std::string ivestis;
    char skaiciavimoMetodoPasirinkimas;
    char ivestiesPasirinkimas;
    char pazymiuIvedimoBudas;
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    while (true){
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            skaiciavimoMetodoPasirinkimas = (char)std::toupper(static_cast<unsigned char>(ivestis[0]));
            if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'M') break;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
    int meniu = 0;
    while (true) {
        std::cout << "Galimi programos veikimo būdai:\n";
        std::cout << "1 - Įvesti duomenis ranka\n";
        std::cout << "2 - Generuoti tik pažymius\n";
        std::cout << "3 - Generuoti vardus, pavardes ir pažymius\n";
        std::cout << "4 - Baigti darbą\n";
        std::cout << "Pasirinkite programos eigą: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        int val = 0;
        auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
        if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 4) {
            meniu = val;
            break;
        }
        std::cout << "Įveskite TIK 1, 2, 3 arba 4.\n";
    }
    if (meniu == 4) return 0;
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
        if (meniu == 3) {
            generuotiVardaPavarde(studentas, vyrVardai, vyrPavardes, motVardai, motPavardes);
        } else {
            while (true) {
                std::cout << "Įveskite studento vardą: ";
                if (!std::getline(std::cin, studentas.Vardas)) return 0;
                if (tikrintiIvesti(studentas.Vardas)) break;
                std::cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true) {
                std::cout << "Įveskite studento pavardę: ";
                if (!std::getline(std::cin, studentas.Pavarde)) return 0;
                if (tikrintiIvesti(studentas.Pavarde)) break;
                std::cout << "Studento pavardė negali likti tuščia.\n";
            }
        }
        if (meniu == 2 || meniu == 3) {
            generuotiRezultatus(studentas);
        } else {
            studentas.namuDarbuTarpiniaiRezultatai.clear();
            while (true) {
                std::cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus pažymį, paspauskite klavišą ENTER. Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (ivestis.empty()) break;
                int val = 0;
                auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    studentas.namuDarbuTarpiniaiRezultatai.push_back(val);
                    continue;
                }
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            while (true) {
                std::cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10).Įvedus pažymį, paspauskite klavišą ENTER: ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (!tikrintiIvesti(ivestis)) {
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