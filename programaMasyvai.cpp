#include "strukturaMasyvai.h"
#include "bendraStruktura.h"

int main(){
    std::string* vyrVardai = nullptr;
    std::string* vyrPavardes = nullptr;
    std::string* motVardai = nullptr;
    std::string* motPavardes = nullptr;
    int vyrVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_vyru_vardai.txt", vyrVardai);
    int vyrPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt", vyrPavardes);
    int motVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_moteru_vardai.txt", motVardai);
    int motPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt", motPavardes);
    while (true){
        int meniu = nuskaitytiMeniuPasirinkima();
        if (meniu == 4) break;
        char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
        StudentasMasyvas** studentuSarasas = nullptr;
        int studentuSkaicius = 0;
        int talpa = 0;
        if (meniu == 3){
            int generuojamuStudentuKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite norima generuoti studentų kiekį ir paspauskite ENTER: ");
            int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų kiekį ir paspauskite ENTER: ");
            for (int i = 0; i < generuojamuStudentuKiekis; i++){
                uztikrintiStudentuMasyvoTalpa(studentuSarasas, talpa, studentuSkaicius, studentuSkaicius + 1);
                studentuSarasas[studentuSkaicius] = new StudentasMasyvas();
                StudentasMasyvas* studentas = studentuSarasas[studentuSkaicius];
                generuotiVardaPavarde(studentas->Vardas, studentas->Pavarde, vyrVardai, vyrVarduKiekis, vyrPavardes, vyrPavardziuKiekis, motVardai, motVarduKiekis, motPavardes, motPavardziuKiekis);
                generuotiRezultatus(studentas, maksimalusNDKiekis);
                studentuSkaicius++;
            }
            parodytiRezultatuLentele(studentuSarasas, studentuSkaicius, skaiciavimoMetodoPasirinkimas);
            atlaisvintiAtminti(studentuSarasas, studentuSkaicius, talpa);
            continue;
        }
        int maksimalusNDKiekis = 0;
        if (meniu == 1 || meniu == 2) maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
        while (true){
            std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
            std::string ivestis;
            if (!getline(std::cin, ivestis)){
                atlaisvintiAtminti(studentuSarasas, studentuSkaicius, talpa);
                delete[] vyrVardai; delete[] vyrPavardes; delete[] motVardai; delete[] motPavardes;
                return 0;
            }
            if (!(tikrintiIvesti(ivestis) && ivestis.size() == 1)){
                std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
            char pasirinkimas = ivestis[0];
            if (pasirinkimas == 'N' || pasirinkimas == 'n') break;
            if (!(pasirinkimas == 'T' || pasirinkimas == 't')){
                std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
            uztikrintiStudentuMasyvoTalpa(studentuSarasas, talpa, studentuSkaicius, studentuSkaicius + 1);
            studentuSarasas[studentuSkaicius] = new StudentasMasyvas();
            StudentasMasyvas* studentas = studentuSarasas[studentuSkaicius];
            studentuSkaicius++;
            while (true){
                std::cout << "Įveskite studento vardą: ";
                if (!getline(std::cin, studentas->Vardas)) return 0;
                if (tikrintiIvesti(studentas->Vardas)){
                    tvarkytiVarda(studentas->Vardas);
                    break;
                }
                std::cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true){
                std::cout << "Įveskite studento pavardę: ";
                if (!getline(std::cin, studentas->Pavarde)) return 0;
                if (tikrintiIvesti(studentas->Pavarde)){
                    tvarkytiPavarde(studentas->Pavarde);
                    break;
                }
                std::cout << "Studento pavardė negali likti tuščia.\n";
            }
            if (meniu == 2){
                generuotiRezultatus(studentas, maksimalusNDKiekis);
            } else{
                uztikrintiNamuDarbuMasyvoTalpa(studentas->namuDarbuTarpiniaiRezultatai, studentas->namuDarbuTalpa, studentas->namuDarbuKiekis, maksimalusNDKiekis);
                while (studentas->namuDarbuKiekis < maksimalusNDKiekis){
                    std::cout << "Įveskite studento namų darbų pažymius (1-10). Po kiekvieno įvesto pažymio paspauskite klavišą ENTER. Baigus tuščioje eilutėje paspauskite klavišą ENTER: ";
                    std::string ivestis;
                    if (!getline(std::cin, ivestis)) return 0;
                    if (ivestis.empty()) break;
                    int reiksme = 0;
                    if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= 1 && reiksme <= 10){
                        studentas->namuDarbuTarpiniaiRezultatai[studentas->namuDarbuKiekis] = reiksme;
                        studentas->namuDarbuKiekis++;
                        continue;
                    }
                    std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                }
                if (studentas->namuDarbuKiekis == maksimalusNDKiekis) std::cout << "Pasiektas maksimalus namų darbų pažymių kiekis.\n";
                while (studentas->namuDarbuKiekis < maksimalusNDKiekis){
                    studentas->namuDarbuTarpiniaiRezultatai[studentas->namuDarbuKiekis] = 0;
                    studentas->namuDarbuKiekis++;
                }
                studentas->egzaminoRezultatas = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ");
            }
        }
        parodytiRezultatuLentele(studentuSarasas, studentuSkaicius, skaiciavimoMetodoPasirinkimas);
        atlaisvintiAtminti(studentuSarasas, studentuSkaicius, talpa);
    }
    delete[] vyrVardai;
    delete[] vyrPavardes;
    delete[] motVardai;
    delete[] motPavardes;
    return 0;
}