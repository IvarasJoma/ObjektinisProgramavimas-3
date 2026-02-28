#ifndef STRUKTURAIVESTISISVESTIS_H
#define STRUKTURAIVESTISISVESTIS_H

#include <vector>
#include "strukturaStudentas.h"

void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);
int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes);
int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas);
int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas);
char nuskaitytiSkaiciavimoMetoda();
bool tikrintiIvesti(const std::string& ivestis);
void tvarkytiVarda(std::string& ivestis);
void tvarkytiPavarde(std::string& ivestis);
int nuskaitytiPazymiNuo1iki10(const char* pranesimas);
bool nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme);
void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);

#endif