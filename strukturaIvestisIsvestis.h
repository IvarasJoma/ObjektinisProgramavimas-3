#ifndef STRUKTURAIVESTISISVESTIS_H
#define STRUKTURAIVESTISISVESTIS_H

#include <vector>
#include "strukturaStudentas.h"
#include "Failai.h"

void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);
int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes);
bool nuskaitytiPagrindinioMeniuPasirinkima(const std::vector<std::string>& eilutes, int& pasirinkimas);
int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas);
int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas);
char nuskaitytiSkaiciavimoMetoda();
bool tikrintiIvesti(const std::string& ivestis);
void tvarkytiVarda(std::string& ivestis);
void tvarkytiPavarde(std::string& ivestis);
int nuskaitytiPazymiNuo1iki10(const char* pranesimas);
bool nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme);
void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
bool patvirtintiNaujoStudentoPridejima();
std::string nuskaitytiVardaArPavarde(const char* ivestiesPranesimas, void(*tvarkyti)(std::string&), const char* klaidosPranesimas);
void apdorotiIrIsvestiStudentus(std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas, int pasirinkimasNuskaitymo);
void vykdytiStudentuIvedima(bool generuotiPazymius);
void vykdytiPilnaGeneravima(Failai& failai);
void parodytiStudentus(const std::vector<StudentasVektorius>& studentai, char skaiciavimoMetodas);

#endif