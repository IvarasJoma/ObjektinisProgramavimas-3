#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include <filesystem>
#include "../Vector.h"
#include "../Studentas.h"
#include "../StudManAPI.h"

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

STUDMAN_API Vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);

/**
 * @brief Nuskaito studentų duomenis iš failo į vektorių.
 * @param failas Failo kelias.
 * @return Studentų vektorius.
 */
STUDMAN_API Vector<Studentas> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);

/**
 * @brief Vykdo studentų duomenų nuskaitymo iš failo scenarijų.
 */
STUDMAN_API void vykdytiNuskaitymaIsFailo();

/**
 * @brief Įrašo studentų duomenis pagal pasirinktą išvedimo scenarijų.
 * @param studentuSarasas Studentų sąrašas.
 */
STUDMAN_API void irasytiDuomenis(Vector<Studentas>& studentuSarasas);

/**
 * @brief Įrašo studentų sąrašą į nurodytą failą.
 * @param studentuSarasas Studentų sąrašas.
 * @param failoPavadinimas Išvesties failo pavadinimas.
 */
STUDMAN_API void irasytiStudentuDuomenisIFaila(const Vector<Studentas>& studentuSarasas, const std::string& failoPavadinimas);

/**
 * @brief Vykdo studentų skirstymą į atskirus failus.
 * @param studentuSarasas Studentų sąrašas.
 */
STUDMAN_API void vykdytiSkirstymaIFailus(Vector<Studentas>& studentuSarasas);

/**
 * @brief Įrašo pažangius ir silpnus studentus į atskirus failus.
 * @param pazangiuSarasas Pažangių studentų sąrašas.
 * @param silpnuSarasas Silpnų studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Galutinio pažymio skaičiavimo metodas.
 */
STUDMAN_API void irasytiSuskirstytusStudentusIFailus(const Vector<Studentas>& pazangiuSarasas, const Vector<Studentas>& silpnuSarasas, const char& skaiciavimoMetodoPasirinkimas);

/**
 * @brief Grąžina visus tekstinius failus iš nurodyto katalogo.
 * @param katalogas Katalogo kelias.
 * @return Tekstinių failų kelių vektorius.
 */
STUDMAN_API Vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);

/**
 * @brief Praleidžia tarpo simbolius skaitant tekstą iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 */
STUDMAN_API void praleistiTarpaIsFailo(const char*& rodykle);

/**
 * @brief Nuskaito vieną žodį iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 * @param isvestis Kintamasis, į kurį įrašomas nuskaitytas žodis.
 * @return `true`, jei žodis nuskaitytas sėkmingai, kitu atveju `false`.
 */
STUDMAN_API bool nuskaitytiZodiIsFailo(const char*& rodykle, std::string& isvestis);

/**
 * @brief Nuskaito sveikąjį skaičių iš simbolių rodyklės.
 * @param rodykle Rodyklė į einamąją teksto poziciją.
 * @param x Kintamasis, į kurį įrašomas nuskaitytas skaičius.
 * @return `true`, jei skaičius nuskaitytas sėkmingai, kitu atveju `false`.
 */
STUDMAN_API bool nuskaitytiSveikaSkaiciuIsFailo(const char*& rodykle, int& x);

/**
 * @brief Nuskaito studentų duomenis pagal pasirinktą failą iš katalogo.
 * @param pasirinkimasNuskaitymo Pasirinkto failo numeris meniu sąraše.
 * @param studentuSarasas Studentų sąrašas, į kurį įrašomi nuskaityti duomenys.
 * @param katalogas Katalogas, kuriame ieškoma tekstinių failų.
 */
STUDMAN_API void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, Vector<Studentas>& studentuSarasas, const std::string& katalogas);

#endif