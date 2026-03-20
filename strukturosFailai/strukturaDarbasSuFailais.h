#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include <filesystem>
#include "../strukturosFailai/VektoriuStudentoStruktura.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);
void vykdytiNuskaitymaIsFailo();
void irasytiDuomenis(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiStudentuDuomenisIFaila(const std::vector<StudentasVektorius>& studentuSarasas, std::string failoPavadinimas);
void vykdytiSkirstymaIFailus(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiSuskirstytusStudentusIFailus(const std::vector<StudentasVektorius>& pazangiuSarasas, const std::vector<StudentasVektorius>& silpnuSarasas);
std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);
void praleistiTarpaIsFailo(const char*& rodykle);
bool nuskaitytiZodiIsFailo(const char*& rodykle, std::string& isvestis);
bool nuskaitytiSveikaSkaiciuIsFailo(const char*& rodykle, int& x);

#endif