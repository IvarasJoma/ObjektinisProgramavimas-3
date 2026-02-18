#ifndef BENDRASTRUKTURA_H
#define BENDRASTRUKTURA_H

#include <iostream>

bool tikrintiIvesti(const std::string& ivestis);
void tvarkytiVarda(std::string& ivestis);
void tvarkytiPavarde(std::string& ivestis);
bool nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme);
int nuskaitytiMeniuPasirinkima();
char nuskaitytiSkaiciavimoMetoda();
int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas);
int nuskaitytiPazymiNuo1iki10(const char* pranesimas);
int generuotiSveikaSkaiciu(int nuo, int iki);

#endif