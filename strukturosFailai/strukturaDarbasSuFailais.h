#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include <filesystem>
#include "../Studentas.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<Studentas> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);
void vykdytiNuskaitymaIsFailo();
void irasytiDuomenis(std::vector<Studentas>& studentuSarasas);
void irasytiStudentuDuomenisIFaila(const std::vector<Studentas>& studentuSarasas, std::string failoPavadinimas);
void vykdytiSkirstymaIFailus(std::vector<Studentas>& studentuSarasas);
void irasytiSuskirstytusStudentusIFailus(const std::vector<Studentas>& pazangiuSarasas, const std::vector<Studentas>& silpnuSarasas, const char& skaiciavimoMetodoPasirinkimas);
std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);
void praleistiTarpaIsFailo(const char*& rodykle);
bool nuskaitytiZodiIsFailo(const char*& rodykle, std::string& isvestis);
bool nuskaitytiSveikaSkaiciuIsFailo(const char*& rodykle, int& x);
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<Studentas>& studentuSarasas, const std::string& katalogas);

#endif