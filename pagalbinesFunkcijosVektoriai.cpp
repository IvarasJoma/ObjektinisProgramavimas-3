#include "strukturaVektoriai.h"
#include "bendraStruktura.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <charconv>
#include <format>
#include <sstream>
#include <fstream>

static inline void skip_ws(const char*& p) {
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') ++p;
}

static inline bool read_word(const char*& p, std::string& out) {
    skip_ws(p);
    if (!*p) return false;
    const char* start = p;
    while (*p && *p!=' ' && *p!='\t' && *p!='\r' && *p!='\n') ++p;
    out.assign(start, static_cast<size_t>(p - start));
    return true;
}

static inline bool read_int(const char*& p, int& x){
    skip_ws(p);
    if (!*p) return false;
    int val = 0;
    while (*p >= '0' && *p <= '9') {
        val = val * 10 + (*p - '0');
        ++p;
    }
    x = val;
    return true;
}

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    double suma = 0;
    for (int pazymys : ndPazymiai) suma += pazymys;
    return suma / ndPazymiai.size();
}

double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas){
    double ndVidurkis = skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndVidurkis + 0.6 * studentas.egzaminoRezultatas;
}

double skaiciuotiNDMediana(std::vector<int> ndPazymiai){
    if (ndPazymiai.empty()) return 0.0;
    std::sort(ndPazymiai.begin(), ndPazymiai.end());
    int n = (int)ndPazymiai.size();
    if (n % 2 == 1) return ndPazymiai[n / 2];
    else return (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
}

double skaiciuotiGalutineMediana(const StudentasVektorius& studentas){
    double ndMediana = skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndMediana + 0.6 * studentas.egzaminoRezultatas;
}

void parodytiRezultatuLentele(const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    std::cout << std::string(98, '-') << "\n";
    std::cout << std::format("{:<40}{:<40}{:<18}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    std::cout << std::string(98, '-') << "\n";
    for (const auto& studentas : studentuSarasas){
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        std::cout << std::format("{:<40}{:<40}{:<18.2f}\n", studentas.Vardas, studentas.Pavarde, galutinisRezultatas);
    }
}

void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis){
    studentas.namuDarbuTarpiniaiRezultatai.clear();
    studentas.namuDarbuTarpiniaiRezultatai.reserve(maksimalusNDKiekis);
    for (int i = 0; i < maksimalusNDKiekis; ++i) studentas.namuDarbuTarpiniaiRezultatai.push_back(generuotiSveikaSkaiciu(0, 10));
    studentas.egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()){
        studentas.Vardas = "Vardenis";
        studentas.Pavarde = "Pavardenis";
        return;
    }
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0){
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)vyrVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)vyrPavardes.size() - 1);
        studentas.Vardas = vyrVardai[vardoIndeksas];
        studentas.Pavarde = vyrPavardes[pavardesIndeksas];
    }
    else{
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)motVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)motPavardes.size() - 1);
        studentas.Vardas = motVardai[vardoIndeksas];
        studentas.Pavarde = motPavardes[pavardesIndeksas];
    }
}

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas){
    std::vector<std::string> rezultatas;
    std::ifstream fin(failas);
    if (!fin){
        std::cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return rezultatas;
    }
    std::string eilute;
    while (getline(fin, eilute)){
        if (!eilute.empty()) rezultatas.push_back(eilute);
    }
    return rezultatas;
}

void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis){
    namuDarbuPazymiai.clear();
    while (namuDarbuPazymiai.size() < maksimalusNDKiekis){
        std::cout << "Įveskite studento namų darbų pažymius (1-10). Po kiekvieno įvesto pažymio paspauskite klavišą ENTER. Baigus tuščioje eilutėje paspauskite klavišą ENTER: ";
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        if (ivestis.empty()) break;
        int reiksme = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= 1 && reiksme <= 10) namuDarbuPazymiai.push_back(reiksme);
        else std::cout << "Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.\n";
    }
    if (namuDarbuPazymiai.size() == maksimalusNDKiekis) std::cout << "Pasiektas maksimalus namų darbų pažymių kiekis.\n";
    while (namuDarbuPazymiai.size() < maksimalusNDKiekis) namuDarbuPazymiai.push_back(0);
}

std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas){
    std::vector<StudentasVektorius> studentuSarasas;
    studentuSarasas.reserve(1000000);
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) return studentuSarasas;
    static char ivestiesBuferis[1 << 20];
    std::setvbuf(skaitomasFailas, ivestiesBuferis, _IOFBF, sizeof(ivestiesBuferis));
    char aprasas[257];
    if (!std::fgets(aprasas, sizeof(aprasas), skaitomasFailas)){
        std::fclose(skaitomasFailas);
        return studentuSarasas;
    }
    int namuDarbuKiekis = 0;
    char laikinaEilute[257];
    std::strncpy(laikinaEilute, aprasas, sizeof(laikinaEilute));
    laikinaEilute[sizeof(laikinaEilute) - 1] = '\0';
    char* stulpelis = std::strtok(laikinaEilute, " \t\r\n");
    while (stulpelis){
        if (stulpelis[0] == 'N' && stulpelis[1] == 'D') namuDarbuKiekis++;
        stulpelis = std::strtok(nullptr, " \t\r\n");
    }
    char eilute[257];
    while (std::fgets(eilute, sizeof(eilute), skaitomasFailas)){
        const char* rodykle = eilute;
        StudentasVektorius studentas;
        if (!read_word(rodykle, studentas.Vardas)) continue;
        if (!read_word(rodykle, studentas.Pavarde)) continue;
        studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis);
        for (int i = 0; i < namuDarbuKiekis; i++){
            int laikinasPazymys;
            if (!read_int(rodykle, laikinasPazymys)) laikinasPazymys = 0;
            studentas.namuDarbuTarpiniaiRezultatai.push_back(laikinasPazymys);
        }
        if (!read_int(rodykle, studentas.egzaminoRezultatas)) studentas.egzaminoRezultatas = 0;
        studentuSarasas.push_back(std::move(studentas));
    }
    std::fclose(skaitomasFailas);
    return studentuSarasas;
}