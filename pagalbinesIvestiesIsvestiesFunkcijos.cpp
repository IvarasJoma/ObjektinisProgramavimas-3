#include "strukturaIvestisIsvestis.h"
#include "strukturaSkaiciavimai.h"
#include <iostream>
#include <charconv>
#include <sstream>
#include <fstream>

void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    out << std::string(98, '-') << "\n";
    out << std::format("{:<40}{:<40}{:<18}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    out << std::string(98, '-') << "\n";
    for (const auto& studentas : studentuSarasas){
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        out << std::format("{:<40}{:<40}{:<18.2f}\n", studentas.Vardas, studentas.Pavarde, galutinisRezultatas);
    }
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

bool tikrintiIvesti(const std::string& ivestis){
    for (char simbolis : ivestis){
        if (!isspace(static_cast<unsigned char>(simbolis))) return true;
    } return false;
}

void tvarkytiVarda(std::string& ivestis){
    std::stringstream eilutesSrautas(ivestis);
    std::string pirmasZodis, antrasZodis;
    eilutesSrautas >> pirmasZodis >> antrasZodis;
    if (!pirmasZodis.empty()){
        for (char& simbolis : pirmasZodis){
            simbolis = std::tolower(static_cast<unsigned char>(simbolis));
        }
        pirmasZodis[0] = std::toupper(static_cast<unsigned char>(pirmasZodis[0]));
    }
    if (!antrasZodis.empty()){
        for (char& simbolis : antrasZodis){
            simbolis = std::tolower(static_cast<unsigned char>(simbolis));
        }
        antrasZodis[0] = std::toupper(static_cast<unsigned char>(antrasZodis[0]));
    }
    if (antrasZodis.empty()) ivestis = pirmasZodis;
    else ivestis = pirmasZodis + " " + antrasZodis;
}

void tvarkytiPavarde(std::string& ivestis){
    std::stringstream eilutesSrautas(ivestis);
    std::string pirmasZodis;
    eilutesSrautas >> pirmasZodis;
    bool kitaDidzioji = true;
    for (char& simbolis : ivestis){
        simbolis = std::tolower(static_cast<unsigned char>(simbolis));
        if (kitaDidzioji && std::isalpha(static_cast<unsigned char>(simbolis))){
            simbolis = std::toupper(static_cast<unsigned char>(simbolis));
            kitaDidzioji = false;
        }
        if (simbolis == '-') kitaDidzioji = true;
    }
}

bool nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme){
    reiksme = 0;
    auto rezultatas = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
    return rezultatas.ec == std::errc{} && rezultatas.ptr == ivestis.data() + ivestis.size();
}

int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes){
    while (true){
        std::cout << std::string(98, '-') << "\n";
        for (const auto& eilute : eilutes)
            std::cout << eilute << "\n";
        std::cout << std::string(98, '-') << "\n";
        std::cout << "Pasirinkite programos eigą: ";
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        int meniu = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, meniu) && meniu >= 1 && meniu <= eilutes.size()-1) return meniu;
        std::cout << "Įveskite TIK ";
        for (int i = 1; i <= eilutes.size()-1; ++i){
            std::cout << i;
            if (i < eilutes.size() - 2) std::cout << ", ";
            else if (i == eilutes.size() - 2) std::cout << " arba ";
        }
        std::cout << ".\n";
    }
}

bool nuskaitytiPagrindinioMeniuPasirinkima(const std::vector<std::string>& eilutes, int& pasirinkimas){
    while (true){
        std::cout << std::string(98, '-') << "\n";
        for (const auto& eilute : eilutes)
            std::cout << eilute << "\n";
        std::cout << std::string(98, '-') << "\n";
        std::cout << "Pasirinkite programos eigą: ";
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        int meniu = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, pasirinkimas) && pasirinkimas >= 1 && pasirinkimas <= eilutes.size()-1) return true;
        std::cout << "Įveskite TIK ";
        for (int i = 1; i <= eilutes.size()-1; ++i){
            std::cout << i;
            if (i < eilutes.size() - 2) std::cout << ", ";
            else if (i == eilutes.size() - 2) std::cout << " arba ";
        }
        std::cout << ".\n";
    }
}

char nuskaitytiSkaiciavimoMetoda(){
    while (true){
        std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        if (tikrintiIvesti(ivestis) && ivestis.size() == 1){
            char raide = ivestis[0];
            if (raide == 'V' || raide == 'v' || raide == 'M' || raide == 'm') return raide;
        }
        std::cout << "Įveskite TIK vieną raidę: V arba M.\n";
    }
}

int nuskaitytiMinimaluSveikajiSkaiciu(const char* pranesimas, int minimaliReiksme){
    while (true){
        std::cout << pranesimas;
        std::string ivestis;
        if (!std::getline(std::cin, ivestis)) std::exit(0);
        if (!tikrintiIvesti(ivestis)){
            if (minimaliReiksme <= 0) std::cout << "Reikšmė turi būti neneigiamas skaičius (0 ir daugiau).\n";
            else std::cout << "Reikšmė turi būti teigiamas skaičius (1 ir daugiau).\n";
            continue;
        }
        int reiksme = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= minimaliReiksme) return reiksme;
        if (minimaliReiksme <= 0) std::cout << "Reikšmė turi būti neneigiamas skaičius (0 ir daugiau).\n";
        else std::cout << "Reikšmė turi būti teigiamas skaičius (1 ir daugiau).\n";
    }
}

int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas){ return nuskaitytiMinimaluSveikajiSkaiciu(pranesimas, 0);}

int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas){ return nuskaitytiMinimaluSveikajiSkaiciu(pranesimas, 1); }

int nuskaitytiPazymiNuo1iki10(const char* pranesimas){
    while (true){
        std::cout << pranesimas;
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        int reiksme = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= 1 && reiksme <= 10) return reiksme;
        std::cout << "Įveskite sveiką skaičių intervale nuo 1 iki 10.\n";
    }
}

void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    if (pasirinkimasIsvedimo == 1) parodytiRezultatuLentele(std::cout, studentuSarasas, skaiciavimoMetodoPasirinkimas);
    if (pasirinkimasIsvedimo == 2){
        std::ofstream isvedimoFailas("studentuRezultatai.txt");
        parodytiRezultatuLentele(isvedimoFailas, studentuSarasas, skaiciavimoMetodoPasirinkimas);
        isvedimoFailas.flush();
        isvedimoFailas.close();
    }
}

bool patvirtintiNaujoStudentoPridejima(){
    while (true){
        std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
        std::string ivestis;
        if (!std::getline(std::cin, ivestis)) std::exit(0);
        if (!(tikrintiIvesti(ivestis) && ivestis.size() == 1)) {
            std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
            continue;
        }
        char pasirinkimas = ivestis[0];
        if (pasirinkimas == 'T' || pasirinkimas == 't') return true;
        if (pasirinkimas == 'N' || pasirinkimas == 'n') return false;
        std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
    }
}

std::string nuskaitytiVardaArPavarde(const char* ivestiesPranesimas, void(*tvarkyti)(std::string&), const char* klaidosPranesimas){
    while (true) {
        std::cout << ivestiesPranesimas;
        std::string ivestis;
        if (!std::getline(std::cin, ivestis)) std::exit(0);
        if (tikrintiIvesti(ivestis)) {
            tvarkyti(ivestis);
            return ivestis;
        }
        std::cout << klaidosPranesimas;
    }
}