#include "../strukturosFailai/strukturaDarbasSuFailais.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/strukturaGeneravimas.h"
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

std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, std::size_t kiekis){
    std::vector<StudentasVektorius> studentuSarasas;
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    try{
        studentuSarasas.reserve(kiekis);
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

std::vector<StudentasVektorius> irasytiStudentuDuomenisIFaila(std::vector<StudentasVektorius>& studentuSarasas, int maksimalusNDKiekis, int studentuKiekis){
    std::ostringstream oss;
    std::string ND = "ND";
    oss << "studentai" << std::to_string(studentuKiekis) << ".txt";
    std::string failoPavadinimas = oss.str();
    FILE* isvedamasFailas = std::fopen(failoPavadinimas.c_str(), "w");
    if (!isvedamasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    try{
        static char isvestiesBuferis[1 << 20];
        std::setvbuf(isvedamasFailas, isvestiesBuferis, _IOFBF, sizeof(isvestiesBuferis));
        fprintf(isvedamasFailas, "%18s", "Vardas", "%18s", "Pavardė");
        for (int i = 1; i < maksimalusNDKiekis; ++i){
            fprintf(isvedamasFailas, "%10s", ND.append(std::to_string(i)));
        }
        fprintf(isvedamasFailas, "%10s", "Egz.");
        std::fclose(isvedamasFailas);
    } catch (const std::bad_alloc&){
        std::fclose(isvedamasFailas);
        std::cerr << "Nepakanka atminties...\n";
        return studentuSarasas;
    }
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

void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas, Failai failai){
    try {
        if (pasirinkimasNuskaitymo == 1) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.kursiokai, 3);
        else if (pasirinkimasNuskaitymo == 2) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai10000, 10000);
        else if (pasirinkimasNuskaitymo == 3) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai100000, 100000);
        else if (pasirinkimasNuskaitymo == 4) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai1000000, 1000000);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida skaitant failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}

void irasytiDuomenis(int pasirinkimasIrasymo, std::vector<StudentasVektorius>& studentuSarasas, int maksimalusNDKiekis, int studentuKiekis){
    try {
        if (pasirinkimasIrasymo == 1) irasytiStudentuDuomenisIFaila(studentuSarasas, maksimalusNDKiekis, studentuKiekis);
        else if (pasirinkimasIrasymo == 2) irasytiStudentuDuomenisIFaila(studentuSarasas, maksimalusNDKiekis, studentuKiekis);
        else if (pasirinkimasIrasymo == 3) irasytiStudentuDuomenisIFaila(studentuSarasas, maksimalusNDKiekis, studentuKiekis);
        else if (pasirinkimasIrasymo == 4) irasytiStudentuDuomenisIFaila(studentuSarasas, maksimalusNDKiekis, studentuKiekis);
        else if (pasirinkimasIrasymo == 5) irasytiStudentuDuomenisIFaila(studentuSarasas, maksimalusNDKiekis, studentuKiekis);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida rašant į failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}


void vykdytiNuskaitymaIsFailo(Failai& failai){
    std::vector<StudentasVektorius> studentuSarasas;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(NUSKAITYMO_MENIU);
    nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, failai);
    apdorotiIrIsvestiStudentus(studentuSarasas, skaiciavimoMetodas, pasirinkimasNuskaitymo);
}

void vykdytiIrasymaIFaila(Failai& failai){
    int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų pažymių kiekį ir paspauskite ENTER: ");
    int pasirinkimasIrasymo = nuskaitytiMeniuPasirinkima(ISVEDIMO_I_FAILA_MENIU);
    int studentuKiekis = 0;
    if (pasirinkimasIrasymo == 1) studentuKiekis = 1000;
    if (pasirinkimasIrasymo == 2) studentuKiekis = 10000;
    if (pasirinkimasIrasymo == 3) studentuKiekis = 100000;
    if (pasirinkimasIrasymo == 4) studentuKiekis = 1000000;
    if (pasirinkimasIrasymo == 5) studentuKiekis = 10000000;
    std::vector<StudentasVektorius> studentuSarasas = generuotiStudentus(studentuKiekis, maksimalusNDKiekis, failai);
    irasytiDuomenis(pasirinkimasIrasymo, studentuSarasas, maksimalusNDKiekis, studentuKiekis);
}