#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include <filesystem>
#include "../Studentas.h"

/**
 * @file strukturaDarbasSuFailais.h
 * @brief Funkcijos darbui su tekstiniais failais ir studentų duomenų nuskaitymu bei įrašymu.
 */

struct Failai;

/**
 * @brief Nuskaito visas tekstinio failo eilutes į string tipo vektorių.
 * @param failas Failo kelias.
 * @return Vektorius su nuskaitytomis eilutėmis.
 */

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);

/**
 * @brief Nuskaito studentų duomenis iš failo į vektorių.
 * @param failas Failo kelias.
 * @return Studentų vektorius.
 */
std::vector<Studentas> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);

/**
 * @brief Vykdo studentų duomenų nuskaitymo iš failo scenarijų.
 */
void vykdytiNuskaitymaIsFailo();

/**
 * @brief Įrašo studentų duomenis pagal pasirinktą išvedimo scenarijų.
 * @param studentuSarasas Studentų sąrašas.
 */
void irasytiDuomenis(std::vector<Studentas>& studentuSarasas);

/**
 * @brief Įrašo studentų sąrašą į nurodytą failą.
 * @param studentuSarasas Studentų sąrašas.
 * @param failoPavadinimas Išvesties failo pavadinimas.
 */
void irasytiStudentuDuomenisIFaila(const std::vector<Studentas>& studentuSarasas, const std::string& failoPavadinimas);

/**
 * @brief Vykdo studentų skirstymą į atskirus failus.
 * @param studentuSarasas Studentų sąrašas.
 */
void vykdytiSkirstymaIFailus(std::vector<Studentas>& studentuSarasas);

/**
 * @brief Įrašo pažangius ir silpnus studentus į atskirus failus.
 * @param pazangiuSarasas Pažangių studentų sąrašas.
 * @param silpnuSarasas Silpnų studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Galutinio pažymio skaičiavimo metodas.
 */
void irasytiSuskirstytusStudentusIFailus(const std::vector<Studentas>& pazangiuSarasas, const std::vector<Studentas>& silpnuSarasas, const char& skaiciavimoMetodoPasirinkimas);

/**
 * @brief Grąžina visus tekstinius failus iš nurodyto katalogo.
 * @param katalogas Katalogo kelias.
 * @return Tekstinių failų kelių vektorius.
 */
std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);

/**
 * @brief Praleidžia tarpo simbolius skaitant tekstą iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 */
void praleistiTarpaIsFailo(const char*& rodykle);

/**
 * @brief Nuskaito vieną žodį iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 * @param isvestis Kintamasis, į kurį įrašomas nuskaitytas žodis.
 * @return `true`, jei žodis nuskaitytas sėkmingai, kitu atveju `false`.
 */
bool nuskaitytiZodiIsFailo(const char*& rodykle, std::string& isvestis);

/**
 * @brief Nuskaito sveikąjį skaičių iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 * @param x Kintamasis, į kurį įrašomas nuskaitytas skaičius.
 * @return `true`, jei skaičius nuskaitytas sėkmingai, kitu atveju `false`.
 */
bool nuskaitytiSveikaSkaiciuIsFailo(const char*& rodykle, int& x);

/**
 * @brief Nuskaito studentų duomenis pagal pasirinktą failą iš katalogo.
 * @param pasirinkimasNuskaitymo Pasirinkto failo numeris meniu sąraše.
 * @param studentuSarasas Studentų sąrašas, į kurį įrašomi nuskaityti duomenys.
 * @param katalogas Katalogas, kuriame ieškoma tekstinių failų.
 */
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<Studentas>& studentuSarasas, const std::string& katalogas);

#endif