#include "strukturaMasyvai.h"

using std::string;
using std::cout;
using std::cin;
using std::toupper;
using std::from_chars;
using std::errc;

int main(){
    string ivestis;
    char ivestiesPasirinkimas;
    char skaiciavimoMetodoPasirinkimas;
    StudentasMasyvas** studentuSarasas = nullptr;
    int studentuSkaicius = 0;
    int pazymiuSkaicius = 0;
    int talpa = 0;
    string* vyrVardai = nullptr;
    int vyrVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_vyru_vardai.txt", vyrVardai);
    string* vyrPavardes = nullptr;
    int vyrPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt", vyrPavardes);
    string* motVardai = nullptr;
    int motVarduKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviski_moteru_vardai.txt", motVardai);
    string* motPavardes = nullptr;
    int motPavardziuKiekis = nuskaitytiEilutesIsFailo("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt", motPavardes);
    int meniu = 0;
    while (true){
        cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!getline(cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1) {
            skaiciavimoMetodoPasirinkimas = (char)toupper(static_cast<unsigned char>(ivestis[0]));
            if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'M') break;
        }
        cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
    while (true) {
        cout << "Galimi programos veikimo būdai:\n";
        cout << "1 - Įvesti duomenis ranka\n";
        cout << "2 - Generuoti tik pažymius\n";
        cout << "3 - Generuoti vardus, pavardes ir pažymius\n";
        cout << "4 - Baigti darbą\n";
        cout << "Pasirinkite programos eigą: ";
        if (!getline(cin, ivestis)) return 0;
        int val = 0;
        auto res = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
        if (res.ec == errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 4) {
            meniu = val;
            break;
        }
        cout << "Įveskite TIK 1, 2, 3 arba 4.\n";
    }
    if (meniu == 4) {
        delete[] vyrVardai;
        delete[] vyrPavardes;
        delete[] motVardai;
        delete[] motPavardes;
        return 0;
    }
    while (true){
        cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
        if (!getline(cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            ivestiesPasirinkimas = (char)toupper(static_cast<unsigned char>(ivestis[0]));
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
                cout << "Įveskite TIK vieną raidę: T arba N.\n";
                continue;
            }
        } else {
            cout << "Įveskite TIK vieną raidę: T arba N.\n";
            continue;
        }
        StudentasMasyvas* s = studentuSarasas[studentuSkaicius - 1];
        if (meniu == 3) {
            generuotiVardaPavarde(s->Vardas, s->Pavarde, vyrVardai, vyrVarduKiekis, vyrPavardes, vyrPavardziuKiekis, motVardai, motVarduKiekis, motPavardes, motPavardziuKiekis);
        } else {
            while (true) {
                cout << "Įveskite studento vardą: ";
                if (!getline(cin, s->Vardas)) return 0;
                if (tikrintiIvesti(s->Vardas)) break;
                cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true) {
                cout << "Įveskite studento pavardę: ";
                if (!getline(cin, s->Pavarde)) return 0;
                if (tikrintiIvesti(s->Pavarde)) break;
                cout << "Studento pavardė negali likti tuščia.\n";
            }
        }
        if (meniu == 2 || meniu == 3) {
            generuotiRezultatus(s);
        } else {
            while (true) {
                cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus pažymį, paspauskite klavišą ENTER. Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
                if (!getline(cin, ivestis)) return 0;
                if (ivestis.empty()) break;
                int val = 0;
                auto res = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    uztikrintiNamuDarbuMasyvoTalpa(s->namuDarbuTarpiniaiRezultatai, s->namuDarbuTalpa, s->namuDarbuKiekis, s->namuDarbuKiekis + 1);
                    s->namuDarbuTarpiniaiRezultatai[s->namuDarbuKiekis] = val;
                    s->namuDarbuKiekis++;
                    continue;
                }
                cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            while (true) {
                cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10): ";
                if (!getline(cin, ivestis)) return 0;
                if (!tikrintiIvesti(ivestis)) {
                    cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                    continue;
                }
                int val = 0;
                auto res = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), val);
                if (res.ec == errc{} && res.ptr == ivestis.data() + ivestis.size() && val >= 1 && val <= 10) {
                    s->egzaminoRezultatas = val;
                    break;
                }
                cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
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