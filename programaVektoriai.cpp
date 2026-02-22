#include "strukturaVektoriai.h"
#include "bendraStruktura.h"

int main(){
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    std::string studentai10000 = "tekstiniaiFailai/studentai10000.txt";
    std::string studentai100000 = "tekstiniaiFailai/studentai100000.txt";
    std::string studentai1000000 = "tekstiniaiFailai/studentai1000000.txt";
    std::string kursiokai = "tekstiniaiFailai/kursiokai.txt";
    while (true) {
        std::vector<std::string> meniu = {"Galimi programos veikimo būdai:", "1 - Įvesti duomenis ranka", "2 - Generuoti tik pažymius", "3 - Generuoti vardus, pavardes ir pažymius", "4 - Nuskaityti duomenis iš failo", "5 - Baigti darbą"};
        int pasirinkimas = nuskaitytiMeniuPasirinkima();
        if (pasirinkimas == 5) break;
        char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
        std::vector<StudentasVektorius> studentuSarasas;
        studentuSarasas.clear();
        if (pasirinkimas == 4){
            std::vector<std::string> meniu = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            int pasirinkimas = nuskaitytiMeniuPasirinkima();
            if (pasirinkimas == 1) nuskaitytiStudentuDuomenisIsFailo(kursiokai);
            if (pasirinkimas == 2) nuskaitytiStudentuDuomenisIsFailo(studentai10000);
            if (pasirinkimas == 3) nuskaitytiStudentuDuomenisIsFailo(studentai100000);
            if (pasirinkimas == 4) nuskaitytiStudentuDuomenisIsFailo(studentai1000000);
            std::vector<std::string> meniu = {"Pasirinkite, pagal ką norite rūšiuoti studentus:", "1 - vardą", "2 - pavardę", "3 - namų darbų galutinį pažymį", "4 - egzamino pažymį"};
            int pasirinkimas = nuskaitytiMeniuPasirinkima();
        }
        if (pasirinkimas == 3) {
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
        if (pasirinkimas == 1 || pasirinkimas == 2) maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
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
            if (pasirinkimas == 2) generuotiRezultatus(studentas, maksimalusNDKiekis);
            else {
                nuskaitytiNamuDarbuPazymius(studentas.namuDarbuTarpiniaiRezultatai, maksimalusNDKiekis);
                studentas.egzaminoRezultatas = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ");
            }
            studentuSarasas.push_back(std::move(studentas));
        }
        parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
    }
    return 0;
}