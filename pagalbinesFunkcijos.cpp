#include "strukturaMasyvai.h"
#include "strukturaVektoriai.h"

using std::cout;
using std::cerr;
using std::format;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;
using std::sort;
using std::isspace;
using std::mt19937;
using std::uniform_int_distribution;

bool tikrintiIvesti(const string& ivestis) {
    for (char simbolis : ivestis) {
        if (!isspace(static_cast<unsigned char>(simbolis))) return true;
    } return false;
}

double skaiciuotiNDVidurki(const vector<int>& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiNDVidurki(const int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    double suma = 0.0;
    for (int i = 0; i < pazymiuSkaicius; i++) suma += namuDarbuTarpiniaiRezultatai[i];
    return suma / pazymiuSkaicius;
}

double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiGalutiniVidurki(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiNDMediana(vector<int> ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    sort(ndPazymiai.begin(), ndPazymiai.end());
    int n = (int)ndPazymiai.size();
    if (n % 2 == 1) {
        return ndPazymiai[n / 2];
    } else {
        return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
    }
}

double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    sort(namuDarbuTarpiniaiRezultatai, namuDarbuTarpiniaiRezultatai + pazymiuSkaicius);
    if (pazymiuSkaicius % 2 == 1) return namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2];
    return (namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2 - 1] + namuDarbuTarpiniaiRezultatai[pazymiuSkaicius / 2]) / 2.0;
}

double skaiciuotiGalutineMediana(const StudentasVektorius& studentas) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiGalutineMediana(const StudentasMasyvas& studentas, int pazymiuSkaicius) {
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai, pazymiuSkaicius);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void parodytiRezultatuLentele(const vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    cout << format("{:<18} {:<18} {:<20}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    cout << string(56, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        cout << format("{:<18} {:<18} {:<20.2f}\n", studentas.Vardas, studentas.Pavarde, galutinisRezultatas);
    }
}

void parodytiRezultatuLentele(StudentasMasyvas** studentuSarasas, int studentuSkaicius, char skaiciavimoMetodoPasirinkimas){
    cout << format("{:<18} {:<18} {:<20}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    cout << string(56, '-') << "\n";
    for (int i = 0; i < studentuSkaicius; i++) {
        int studentoNamuDarbuKiekis = studentuSarasas[i]->namuDarbuKiekis;
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(*studentuSarasas[i], studentoNamuDarbuKiekis) : skaiciuotiGalutineMediana(*studentuSarasas[i], studentoNamuDarbuKiekis);
        cout << format("{:<18} {:<18} {:<20.2f}\n", studentuSarasas[i]->Vardas, studentuSarasas[i]->Pavarde, galutinisRezultatas);
    }
}

void uztikrintiStudentuMasyvoTalpa(StudentasMasyvas**& studentuSarasas, int& talpa, int studentuSkaicius, int dydis){
    if (dydis <= talpa) return;
    int naujaTalpa = (talpa == 0) ? 2 : talpa * 2;
    while (naujaTalpa < dydis) naujaTalpa *= 2;
    StudentasMasyvas** naujasMasyvas = new StudentasMasyvas*[naujaTalpa];
    for (int i = 0; i < studentuSkaicius; i++) naujasMasyvas[i] = studentuSarasas[i];
    for (int i = studentuSkaicius; i < naujaTalpa; i++) naujasMasyvas[i] = nullptr;
    delete[] studentuSarasas;
    studentuSarasas = naujasMasyvas;
    talpa = naujaTalpa;
}

void uztikrintiNamuDarbuMasyvoTalpa(int*& namuDarbuTarpiniaiRezultatai, int& talpa, int pazymiuKiekis, int dydis){
    if (dydis <= talpa) return;
    int naujaTalpa = (talpa == 0) ? 2 : talpa * 2;
    while (naujaTalpa < dydis) naujaTalpa *= 2;
    int* naujasMasyvas = new int[naujaTalpa];
    for (int i = 0; i < pazymiuKiekis; i++) naujasMasyvas[i] = namuDarbuTarpiniaiRezultatai[i];
    delete[] namuDarbuTarpiniaiRezultatai;
    namuDarbuTarpiniaiRezultatai = naujasMasyvas;
    talpa = naujaTalpa;
}

int generuotiSveikaSkaiciu(int nuo, int iki) {
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}

void generuotiRezultatus(StudentasVektorius& studentas) {
    int ndKiekis = generuotiSveikaSkaiciu(0, 20);
    studentas.namuDarbuTarpiniaiRezultatai.clear();
    studentas.namuDarbuTarpiniaiRezultatai.reserve(ndKiekis);
    for (int i = 0; i < ndKiekis; ++i) {
        studentas.namuDarbuTarpiniaiRezultatai.push_back(generuotiSveikaSkaiciu(1, 10));
    }
    studentas.egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

void generuotiRezultatus(StudentasMasyvas* studentas) {
    delete[] studentas->namuDarbuTarpiniaiRezultatai;
    studentas->namuDarbuTarpiniaiRezultatai = nullptr;
    studentas->namuDarbuKiekis = 0;
    studentas->namuDarbuTalpa = 0;
    int ndKiekis = generuotiSveikaSkaiciu(0, 20);
    uztikrintiNamuDarbuMasyvoTalpa(studentas->namuDarbuTarpiniaiRezultatai, studentas->namuDarbuTalpa, studentas->namuDarbuKiekis, ndKiekis);
    for (int i = 0; i < ndKiekis; ++i) {
        studentas->namuDarbuTarpiniaiRezultatai[studentas->namuDarbuKiekis] = generuotiSveikaSkaiciu(1, 10);
        studentas->namuDarbuKiekis++;
    }
    studentas->egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

int nuskaitytiEilutesIsFailo(const string& failas, string*& nuskaitytasMasyvas) {
    nuskaitytasMasyvas = nullptr;
    ifstream fin(failas);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return 0;
    }
    int kiekis = 0;
    string eilute;
    while (getline(fin, eilute)) {
        if (!eilute.empty()) kiekis++;
    }
    if (kiekis == 0) return 0;
    nuskaitytasMasyvas = new string[kiekis];
    fin.clear();
    fin.seekg(0);
    int i = 0;
    while (getline(fin, eilute)) {
        if (eilute.empty()) continue;
        if (i < kiekis) nuskaitytasMasyvas[i++] = eilute;
    }
    return i;
}

void generuotiVardaPavarde(string& vardas, string& pavarde, const string* vyrVardai, int vyrVarduKiekis, const string* vyrPavardes, int vyrPavardziuKiekis, const string* motVardai, int motVarduKiekis, const string* motPavardes, int motPavardziuKiekis){
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0) {
        if (vyrVarduKiekis <= 0 || vyrPavardziuKiekis <= 0) {
            vardas = "Vardenis";
            pavarde = "Pavardenis";
            return;
        }
        int vardoIndeksas = generuotiSveikaSkaiciu(0, vyrVarduKiekis - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, vyrPavardziuKiekis - 1);
        vardas = vyrVardai[vardoIndeksas];
        pavarde = vyrPavardes[pavardesIndeksas];
    } else {
        if (motVarduKiekis <= 0 || motPavardziuKiekis <= 0) {
            vardas = "Vardenė";
            pavarde = "Pavardenė";
            return;
        }
        int vardoIndeksas = generuotiSveikaSkaiciu(0, motVarduKiekis - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, motPavardziuKiekis - 1);
        vardas = motVardai[vardoIndeksas];
        pavarde = motPavardes[pavardesIndeksas];
    }
}

void generuotiVardaPavarde(StudentasVektorius& studentas, const vector<string>& vyrVardai, const vector<string>& vyrPavardes, const vector<string>& motVardai, const vector<string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()) {
        studentas.Vardas = "Vardenis";
        studentas.Pavarde = "Pavardenis";
        return;
    }
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0) {
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)vyrVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)vyrPavardes.size() - 1);
        studentas.Vardas = vyrVardai[vardoIndeksas];
        studentas.Pavarde = vyrPavardes[pavardesIndeksas];
    }
    else {
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)motVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)motPavardes.size() - 1);
        studentas.Vardas = motVardai[vardoIndeksas];
        studentas.Pavarde = motPavardes[pavardesIndeksas];
    }
}    

vector<string> nuskaitytiEilutesIVektoriu(const string& failas){
    vector<string> rezultatas;
    ifstream fin(failas);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return rezultatas;
    }
    string eilute;
    while (getline(fin, eilute)) {
        if (!eilute.empty()) {
            rezultatas.push_back(eilute);
        }
    }
    return rezultatas;
}