#include "strukturaMasyvai.h"
#include "strukturaVektoriai.h"

bool tikrintiIvesti(const std::string& ivestis) {
    for (char simbolis : ivestis) {
        if (!std::isspace(static_cast<unsigned char>(simbolis))) return true;
    } return false;
}

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai) {
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

double skaiciuotiNDMediana(std::vector<int> ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    int n = (int)ndPazymiai.size();
    if (n % 2 == 1) {
        return ndPazymiai[n / 2];
    } else {
        return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
    }
}

double skaiciuotiNDMediana(int* namuDarbuTarpiniaiRezultatai, int pazymiuSkaicius) {
    if (!namuDarbuTarpiniaiRezultatai || pazymiuSkaicius <= 0) return 0.0;
    std::sort(namuDarbuTarpiniaiRezultatai, namuDarbuTarpiniaiRezultatai + pazymiuSkaicius);
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

void parodytiRezultatuLentele(std::vector<StudentasVektorius> studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(14) << "Pavardė" << std::setw(18) << (skaiciavimoMetodoPasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (const auto& studentas : studentuSarasas) {
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        std::cout << std::left << std::setw(15) << studentas.Vardas << std::setw(14) << studentas.Pavarde << std::fixed << std::setprecision(2) << galutinisRezultatas << "\n";
    }
}

void parodytiRezultatuLentele(StudentasMasyvas**& studentuSarasas, int studentuSkaicius, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavardė" << std::setw(18) << (skaiciavimoMetodoPasirinkimas == 'V' ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
    std::cout << std::string(48, '-') << "\n";
    for (int i = 0; i < studentuSkaicius; i++) {
        int studentoNamuDarbuKiekis = studentuSarasas[i]->namuDarbuKiekis;
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V') ? skaiciuotiGalutiniVidurki(*studentuSarasas[i], studentoNamuDarbuKiekis) : skaiciuotiGalutineMediana(*studentuSarasas[i], studentoNamuDarbuKiekis);
        std::cout << std::left << std::setw(15) << studentuSarasas[i]->Vardas << std::setw(15) << studentuSarasas[i]->Pavarde << std::fixed << std::setprecision(2) << galutinisRezultatas << "\n";
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
    static std::mt19937 gen(static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(nuo, iki);
    return dist(gen);
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

int nuskaitytiEilutesIsFailo(const std::string& failas, std::string*& nuskaitytasMasyvas) {
    nuskaitytasMasyvas = nullptr;
    std::ifstream fin(failas);
    if (!fin) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return 0;
    }
    int count = 0;
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty()) count++;
    }
    if (count == 0) return 0;
    nuskaitytasMasyvas = new std::string[count];
    fin.clear();
    fin.seekg(0);
    int i = 0;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        if (i < count) nuskaitytasMasyvas[i++] = line;
    }
    return i;
}

void generuotiVardaPavarde(std::string& vardas, std::string& pavarde, const std::string* vyrVardai, int vyrVarduKiekis, const std::string* vyrPavardes, int vyrPavardziuKiekis, const std::string* motVardai, int motVarduKiekis, const std::string* motPavardes, int motPavardziuKiekis){
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

void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes){
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

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas){
    std::vector<std::string> rezultatas;
    std::ifstream fin(failas);
    if (!fin) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return rezultatas;
    }
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty()) {
            rezultatas.push_back(line);
        }
    }
    return rezultatas;
}