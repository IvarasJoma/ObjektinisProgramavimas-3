#ifndef STRUKTURAIVESTIS_H
#define STRUKTURAIVESTIS_H

#include <vector>
#include <string>
#include "../Studentas.h"
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
void parinktiRikiavimoBudus(int& pasirinkimasRikiavimoPazangiu, int& pasirinkimasRikiavimoSilpnu);
std::string suformuotiStudentoIvestiesEilute(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminoPazymys);
Studentas sukurtiStudentaIsEilutesPerOperatoriu(const std::string& eilute);

#endif