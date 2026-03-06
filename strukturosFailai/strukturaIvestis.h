#ifndef STRUKTURAIVESTIS_H
#define STRUKTURAIVESTIS_H

#include <vector>
#include <string>
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/Failai.h"

void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);
int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes);
bool nuskaitytiPagrindinioMeniuPasirinkima(const std::vector<std::string>& eilutes, int& pasirinkimas);
int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas);
int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas);
char nuskaitytiSkaiciavimoMetoda();
int nuskaitytiPazymiNuo1iki10(const char* pranesimas);
void nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme);
void tikrintiIvesti(const std::string& ivestis);
std::string nuskaitytiVardaArPavarde(const char* ivestiesPranesimas, void(*tvarkyti)(std::string&),const char* klaidosPranesimas);
bool patvirtintiNaujoStudentoPridejima();
void vykdytiStudentuIvedima(bool generuotiPazymius);
void vykdytiPilnaGeneravima(Failai& failai);
void tvarkytiVarda(std::string& ivestis);
void tvarkytiPavarde(std::string& ivestis);
std::string saugiaiNuskaitytiEilute();

#endif