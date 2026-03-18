#include "../strukturosFailai/strukturaDarbasSuFailais.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/VektoriuStudentoStruktura.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaRikiavimas.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sstream>

void praleistiTarpaIsFailo(const char*& rodykle){
    while (*rodykle == ' ' || *rodykle == '\t' || *rodykle == '\r' || *rodykle == '\n') ++rodykle;
}

bool nuskaitytiZodiIsFailo(const char*& rodykle, std::string& isvestis){
    praleistiTarpaIsFailo(rodykle);
    if (!*rodykle) return false;
    const char* pradzia = rodykle;
    while (*rodykle && *rodykle!=' ' && *rodykle!='\t' && *rodykle!='\r' && *rodykle!='\n') ++rodykle;
    isvestis.assign(pradzia, static_cast<size_t>(rodykle - pradzia));
    return true;
}

bool nuskaitytiSveikaSkaiciuIsFailo(const char*& rodykle, int& x){
    praleistiTarpaIsFailo(rodykle);
    if (!*rodykle) return false;
    int reiksme = 0;
    while (*rodykle >= '0' && *rodykle <= '9'){
        reiksme = reiksme * 10 + (*rodykle - '0');
        ++rodykle;
    }
    x = reiksme;
    return true;
}

std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas){
    std::vector<StudentasVektorius> studentuSarasas;
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    try{
        static char ivestiesBuferis[1 << 20];
        std::setvbuf(skaitomasFailas, ivestiesBuferis, _IOFBF, sizeof(ivestiesBuferis));
        char aprasas[257];
        if (!std::fgets(aprasas, sizeof(aprasas), skaitomasFailas)){
            std::fclose(skaitomasFailas);
            return studentuSarasas;
        }
        std::size_t namuDarbuKiekis = 0;
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
            if (!nuskaitytiZodiIsFailo(rodykle, studentas.Vardas)) continue;
            if (!nuskaitytiZodiIsFailo(rodykle, studentas.Pavarde)) continue;
            studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis);
            for (std::size_t i = 0; i < namuDarbuKiekis; i++){
                int laikinasPazymys;
                if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, laikinasPazymys)) laikinasPazymys = 0;
                studentas.namuDarbuTarpiniaiRezultatai.push_back(laikinasPazymys);
            }
            if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, studentas.egzaminoRezultatas)) studentas.egzaminoRezultatas = 0;
            studentuSarasas.push_back(std::move(studentas));
        }
        std::fclose(skaitomasFailas);
        return studentuSarasas;
    } catch (const std::bad_alloc&){
        std::fclose(skaitomasFailas);
        std::cerr << "Nepakanka atminties...\n";
        return studentuSarasas;
    }
}

void irasytiStudentuDuomenisIFaila(const std::vector<StudentasVektorius>& studentuSarasas, std::string failoPavadinimas) {
    std::ofstream isvedamasFailas("tekstiniaiFailai/" + failoPavadinimas);
    if (!isvedamasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    std::size_t ndKiekis = 0;
    if (!studentuSarasas.empty()) ndKiekis = studentuSarasas.front().namuDarbuTarpiniaiRezultatai.size();
    isvedamasFailas << std::format("{:<18}{:<18}", "Vardas", "Pavardė");
    for (std::size_t i = 1; i <= ndKiekis; ++i) isvedamasFailas << std::format("{:<10}", "ND" + std::to_string(i));
    isvedamasFailas << std::format("{:<10}\n", "Egz.");
    for (const auto& studentas : studentuSarasas) {
        isvedamasFailas << std::format("{:<18}{:<18}", studentas.Vardas, studentas.Pavarde);
        for (const auto pazymys : studentas.namuDarbuTarpiniaiRezultatai) isvedamasFailas << std::format("{:<10}", pazymys);
        isvedamasFailas << std::format("{:<10}\n", studentas.egzaminoRezultatas);
    }
    if (!isvedamasFailas) throw std::runtime_error("Nepavyko įrašyti į failą: " + failoPavadinimas);
}

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas){
    std::vector<std::string> rezultatas;
    std::ifstream fin(failas);
    if (!fin.is_open()) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    std::string eilute;
    while (getline(fin, eilute)){
        if (!eilute.empty()) rezultatas.push_back(eilute);
    }
    return rezultatas;
}

void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas) {
    try {
        auto failai = gautiTekstiniusFailus("tekstiniaiFailai");
        if (failai.empty()) throw std::runtime_error("Kataloge 'tekstiniaiFailai' nerasta .txt failų.");
        if (pasirinkimasNuskaitymo < 1 || static_cast<std::size_t>(pasirinkimasNuskaitymo) > failai.size()) throw std::runtime_error("Neteisingas failo pasirinkimas.");
        const std::size_t indeksas = static_cast<std::size_t>(pasirinkimasNuskaitymo - 1);
        const std::string failoKelias = failai[indeksas].string();
        studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failoKelias);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida skaitant failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}

void irasytiDuomenis(std::vector<StudentasVektorius>& studentuSarasas){
    try {
        std::ostringstream oss;
        oss << "studentai" << studentuSarasas.size() << ".txt";
        const std::string failoPavadinimas = oss.str();
        irasytiStudentuDuomenisIFaila(studentuSarasas, failoPavadinimas);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida rašant į failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}

void vykdytiNuskaitymaIsFailo(){
    std::vector<StudentasVektorius> studentuSarasas;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu("tekstiniaiFailai"));
    nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas);
    apdorotiIrIsvestiStudentus(studentuSarasas, skaiciavimoMetodas);
}

void vykdytiIrasymaIFaila(Failai& failai){
    int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
    int pasirinkimasIrasymo = nuskaitytiMeniuPasirinkima(ISVEDIMO_I_FAILA_MENIU);
    int studentuKiekis = 0;
    if (pasirinkimasIrasymo == 1) studentuKiekis = 1000;
    if (pasirinkimasIrasymo == 2) studentuKiekis = 10000;
    if (pasirinkimasIrasymo == 3) studentuKiekis = 100000;
    if (pasirinkimasIrasymo == 4) studentuKiekis = 1000000;
    if (pasirinkimasIrasymo == 5) studentuKiekis = 10000000;
    std::vector<StudentasVektorius> studentuSarasas = generuotiStudentus(studentuKiekis, maksimalusNDKiekis, failai);
    irasytiDuomenis(studentuSarasas);
    vykdytiSkirstymaIFailus(studentuSarasas);
}

void vykdytiSkirstymaIFailus(std::vector<StudentasVektorius>& studentuSarasas){
    std::vector<StudentasVektorius> pazangiuSarasas;
    std::vector<StudentasVektorius> silpnuSarasas;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);
    suskirstytiStudentus(studentuSarasas, pazangiuSarasas, silpnuSarasas);
    int pasirinkimasRikiavimoPazangiu = 0;
    int pasirinkimasRikiavimoSilpnu = 0;
    parinktiRikiavimoBudus(pasirinkimasRikiavimoPazangiu, pasirinkimasRikiavimoSilpnu);
    rikiuotiSuskirstytusStudentus(pazangiuSarasas, silpnuSarasas, pasirinkimasRikiavimoPazangiu, pasirinkimasRikiavimoSilpnu);
    irasytiSuskirstytusStudentusIFailus(pazangiuSarasas, silpnuSarasas);
}

void irasytiSuskirstytusStudentusIFailus(const std::vector<StudentasVektorius>& pazangiuSarasas, const std::vector<StudentasVektorius>& silpnuSarasas){
    irasytiStudentuDuomenisIFaila(pazangiuSarasas, "pazangusStudentai.txt");
    irasytiStudentuDuomenisIFaila(silpnuSarasas, "silpniStudentai.txt");
}

std::vector<std::string> gautiNuskaitymoMeniu(const std::string& katalogas){
    std::vector<std::string> meniu;
    meniu.push_back("Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:");
    int index = 1;
    for (const auto& entry : std::filesystem::directory_iterator(katalogas)){
        if (entry.path().extension() == ".txt"){
            meniu.push_back(std::to_string(index) + " - " + entry.path().filename().string());
            index++;
        }
    }
    return meniu;
}

std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas){
    std::vector<std::filesystem::path> failai;
    for (const auto& failas : std::filesystem::directory_iterator(katalogas)) if (failas.is_regular_file() && failas.path().extension() == ".txt") failai.push_back(failas.path());
    return failai;
}