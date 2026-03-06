#include "../strukturosFailai/strukturaDarbasSuFailais.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

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
    if (!skaitomasFailas) return studentuSarasas;
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

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas){
    std::vector<std::string> rezultatas;
    std::ifstream fin(failas);
    if (!fin.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    }
    std::string eilute;
    while (getline(fin, eilute)){
        if (!eilute.empty()) rezultatas.push_back(eilute);
    }
    return rezultatas;
}

void nuskaitytiDuomenis (int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas, Failai failai){
    if (pasirinkimasNuskaitymo == 1) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.kursiokai, 3);
    if (pasirinkimasNuskaitymo == 2) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai10000, 10000);
    if (pasirinkimasNuskaitymo == 3) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai100000, 100000);
    if (pasirinkimasNuskaitymo == 4) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(failai.studentai1000000, 1000000);
}

void vykdytiNuskaitymaIsFailo(Failai& failai){
    std::vector<StudentasVektorius> studentai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(NUSKAITYMO_MENIU);
    nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentai, failai);
    apdorotiIrIsvestiStudentus(studentai, skaiciavimoMetodas, pasirinkimasNuskaitymo);
}
