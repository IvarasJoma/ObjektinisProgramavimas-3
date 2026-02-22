#include "bendraStruktura.h"

#include <iostream>
#include <charconv>
#include <random>
#include <chrono>
#include <format>

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
        for (char& simbolis : pirmasZodis) {
            simbolis = std::tolower(static_cast<unsigned char>(simbolis));
        }
        pirmasZodis[0] = std::toupper(static_cast<unsigned char>(pirmasZodis[0]));
    }
    if (!antrasZodis.empty()){
        for (char& simbolis : antrasZodis) {
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
    for (char& simbolis : ivestis) {
        simbolis = std::tolower(static_cast<unsigned char>(simbolis));
        if (kitaDidzioji && std::isalpha(static_cast<unsigned char>(simbolis))) {
            simbolis = std::toupper(static_cast<unsigned char>(simbolis));
            kitaDidzioji = false;
        }
        if (simbolis == '-') kitaDidzioji = true;
    }
}

int generuotiSveikaSkaiciu(int nuo, int iki){
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}

bool nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme){
    reiksme = 0;
    auto rezultatas = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
    return rezultatas.ec == std::errc{} && rezultatas.ptr == ivestis.data() + ivestis.size();
}

int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes) {
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

int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas){
    while (true){
        std::cout << pranesimas;
        std::string ivestis;
        if (!getline(std::cin, ivestis)) exit(0);
        if (!tikrintiIvesti(ivestis)){
            std::cout << "Reikšmė turi būti neneigiamas skaičius (0 ir daugiau).\n";
            continue;
        }
        int reiksme = 0;
        if (nuskaitytiSveikajiSkaiciu(ivestis, reiksme) && reiksme >= 0) return reiksme;
        std::cout << "Reikšmė turi būti neneigiamas skaičius (0 ir daugiau).\n";
    }
}

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