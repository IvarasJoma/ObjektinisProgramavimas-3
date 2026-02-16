#include "struktura.h"

int main(){
    std::string ivestis;
    char ivestiesPasirinkimas;
    char skaiciavimoMetodoPasirinkimas;
    StudentasMasyvas** studentuSarasas = nullptr;
    int studentuSkaicius = 0;
    int pazymiuSkaicius = 0;
    int talpa = 0;
    std::string* vyrVardai = nullptr;
    int vyrVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_vyru_vardai.txt", vyrVardai);
    std::string* vyrPavardes = nullptr;
    int vyrPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt", vyrPavardes);
    std::string* motVardai = nullptr;
    int motVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_moteru_vardai.txt", motVardai);
    std::string* motPavardes = nullptr;
    int motPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt", motPavardes);
    while (true){
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!std::getline(std::cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1) {
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
    if (meniu == 4) {
        delete[] vyrVardai;
        delete[] vyrPavardes;
        delete[] motVardai;
        delete[] motPavardes;
        return 0;
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
        StudentasMasyvas* s = studentuSarasas[studentuSkaicius - 1];
        if (meniu == 3) {
            generuotiVardaPavarde(s->Vardas, s->Pavarde, vyrVardai, vyrVarduKiekis, vyrPavardes, vyrPavardziuKiekis, motVardai, motVarduKiekis, motPavardes, motPavardziuKiekis);
        } else {
            while (true) {
                std::cout << "Įveskite studento vardą: ";
                if (!std::getline(std::cin, s->Vardas)) return 0;
                if (tikrintiIvesti(s->Vardas)) break;
                std::cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true) {
                std::cout << "Įveskite studento pavardę: ";
                if (!std::getline(std::cin, s->Pavarde)) return 0;
                if (tikrintiIvesti(s->Pavarde)) break;
                std::cout << "Studento pavardė negali likti tuščia.\n";
            }
        }
        if (meniu == 2 || meniu == 3) {
            generuotiRezultatus(s);
        } else {
            while (true) {
                std::cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus pažymį, paspauskite klavišą ENTER. Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (ivestis.empty()) break;
                int val = 0;
                auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    uztikrintiNamuDarbuMasyvoTalpa(s->namuDarbuTarpiniaiRezultatai, s->namuDarbuTalpa, s->namuDarbuKiekis, s->namuDarbuKiekis + 1);
                    s->namuDarbuTarpiniaiRezultatai[s->namuDarbuKiekis] = val;
                    s->namuDarbuKiekis++;
                    continue;
                }
                std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            while (true) {
                std::cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
                if (!std::getline(std::cin, ivestis)) return 0;
                if (!tikrintiIvesti(ivestis)) {
                    std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                    continue;
                }
                int val = 0;
                auto res = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == std::errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    s->egzaminoRezultatas = val;
                    break;
                }
                std::cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
        }
    }
    for (int i = 0; i < studentuSkaicius; i++) {
        delete[] studentuSarasas[i]->namuDarbuTarpiniaiRezultatai;
        delete studentuSarasas[i];
    }
    delete[] studentuSarasas;
    delete[] vyrVardai;
    delete[] vyrPavardes;
    delete[] motVardai;
    delete[] motPavardes;
    return 0;
}