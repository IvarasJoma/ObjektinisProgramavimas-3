#include "strukturaVektoriai.h"
#include "bendraStruktura.h"

int main() {
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    while (true) {
        int meniu = nuskaitytiMeniuPasirinkima();
        if (meniu == 4) break;
        char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
        std::vector<StudentasVektorius> studentuSarasas;
        studentuSarasas.clear();
        if (meniu == 3) {
            int generuojamuStudentuKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite norima generuoti studentų kiekį ir paspauskite ENTER: ");
            int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų pažymių kiekį ir paspauskite ENTER: ");
            studentuSarasas.reserve(generuojamuStudentuKiekis);
            for (int i = 0; i < generuojamuStudentuKiekis; i++) {
                StudentasVektorius studentas;
                generuotiVardaPavarde(studentas, vyrVardai, vyrPavardes, motVardai, motPavardes);
                generuotiRezultatus(studentas, maksimalusNDKiekis);
                studentuSarasas.push_back(std::move(studentas));
            }
            parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
            continue;
        }
        int maksimalusNDKiekis = 0;
        if (meniu == 2) {
            maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
        }
        while (true) {
            std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
            std::string ivestis;
            if (!getline(std::cin, ivestis)) return 0;
            if (!(tikrintiIvesti(ivestis) && ivestis.size() == 1)) {
                std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
            char pasirinkimas = ivestis[0];
            if (pasirinkimas == 'N' || pasirinkimas == 'n') break;
            if (!(pasirinkimas == 'T' || pasirinkimas == 't')) {
                std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
            StudentasVektorius studentas;
            while (true) {
                std::cout << "Įveskite studento vardą: ";
                if (!getline(std::cin, studentas.Vardas)) return 0;
                if (tikrintiIvesti(studentas.Vardas)) {
                    tvarkytiVarda(studentas.Vardas);
                    break;
                }
                std::cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true) {
                std::cout << "Įveskite studento pavardę: ";
                if (!getline(std::cin, studentas.Pavarde)) return 0;
                if (tikrintiIvesti(studentas.Pavarde)) {
                    tvarkytiPavarde(studentas.Pavarde);
                    break;
                }
                std::cout << "Studento pavardė negali likti tuščia.\n";
            }
            if (meniu == 2) {
                generuotiRezultatus(studentas, maksimalusNDKiekis);
            } else {
                nuskaitytiNamuDarbuPazymius(studentas.namuDarbuTarpiniaiRezultatai);
                studentas.egzaminoRezultatas = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ");
            }
            studentuSarasas.push_back(std::move(studentas));
        }
        parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
    }
    return 0;
}