#include "strukturaVektoriai.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::from_chars;
using std::errc;
using std::move;

int main(){
    vector<StudentasVektorius> studentuSarasas;
    string ivestis;
    char skaiciavimoMetodoPasirinkimas;
    char ivestiesPasirinkimas;
    char pazymiuIvedimoBudas;
    vector<string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    vector<string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    vector<string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    vector<string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    int meniu = 0;
    while (true){
        cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        if (!getline(cin, ivestis)) return 0;
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            skaiciavimoMetodoPasirinkimas = ivestis[0];
            if (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'M' || skaiciavimoMetodoPasirinkimas == 'v' || skaiciavimoMetodoPasirinkimas == 'm') break;
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
        int reiksme = 0;
        auto rezultatas = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
        if (rezultatas.ec == errc{} && rezultatas.ptr == ivestis.data() + ivestis.size() && reiksme >= 1 && reiksme <= 4) {
            meniu = reiksme;
            break;
        }
        cout << "Įveskite TIK 1, 2, 3 arba 4.\n";
    }
    if (meniu == 4) return 0;
    while(true){
        StudentasVektorius studentas;
        while (true){
            cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
            if (!getline(cin, ivestis)) return 0;
            if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
                ivestiesPasirinkimas = ivestis[0];
                if (ivestiesPasirinkimas == 'T' || ivestiesPasirinkimas == 't') break;
                if (ivestiesPasirinkimas == 'N' || ivestiesPasirinkimas == 'n'){
                    parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
                    return 0;
                }
            }
            cout << "Įveskite TIK vieną raidę: T arba N.\n";
        }
        if (meniu == 3) {
            generuotiVardaPavarde(studentas, vyrVardai, vyrPavardes, motVardai, motPavardes);
        } else {
            while (true) {
                cout << "Įveskite studento vardą: ";
                if (!getline(cin, studentas.Vardas)) return 0;
                if (tikrintiIvesti(studentas.Vardas)) break;
                cout << "Studento vardas negali likti tuščias.\n";
            }
            while (true) {
                cout << "Įveskite studento pavardę: ";
                if (!getline(cin, studentas.Pavarde)) return 0;
                if (tikrintiIvesti(studentas.Pavarde)) break;
                cout << "Studento pavardė negali likti tuščia.\n";
            }
        }
        if (meniu == 2 || meniu == 3) {
            generuotiRezultatus(studentas);
        } else {
            studentas.namuDarbuTarpiniaiRezultatai.clear();
            while (true) {
                cout << "Įveskite studento namų darbų pažymius (skalėje nuo 1 iki 10). Įvedus pažymį, paspauskite klavišą ENTER. Suvedus visus pažymius, tuščiame lauke paspauskite klavišą ENTER: ";
                if (!getline(cin, ivestis)) return 0;
                if (ivestis.empty()) break;
                int reiksme = 0;
                auto rezultatas = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
                if (rezultatas.ec == errc{} && rezultatas.ptr == ivestis.data() + ivestis.size() && reiksme >= 1 && reiksme <= 10) {
                    studentas.namuDarbuTarpiniaiRezultatai.push_back(reiksme);
                    continue;
                }
                cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
            while (true) {
                cout << "Įveskite studento egzamino pažymį (skalėje nuo 1 iki 10).Įvedus pažymį, paspauskite klavišą ENTER: ";
                if (!getline(cin, ivestis)) return 0;
                if (!tikrintiIvesti(ivestis)) {
                    cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
                    continue;
                }
                int reiksme = 0;
                auto rezultatas = from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
                if (rezultatas.ec == errc{} && rezultatas.ptr == ivestis.data() + ivestis.size() && reiksme >= 1 && reiksme <= 10) {
                    studentas.egzaminoRezultatas = reiksme;
                    break;
                }
                cout << "Studento egzamino pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
            }
        }
        studentuSarasas.push_back(move(studentas));
    }
}