#ifndef STRUKTURAISVESTIS_H
#define STRUKTURAISVESTIS_H

#include <vector>
#include <string>
#include <ostream>
#include "../Studentas.h"
#include "../strukturosFailai/strukturaTestavimas.h"
#include "../Vector.h"
#include "../StudManAPI.h"

/**
 * @file strukturaIsvestis.h
 * @brief Funkcijos studentų duomenų ir testavimo rezultatų išvedimui.
 */

/**
 * @brief Parodo studentų rezultatų lentelę nurodytame išvesties sraute.
 * @param out Išvesties srautas.
 * @param studentuSarasas Studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Galutinio pažymio skaičiavimo metodas.
 */
STUDMAN_API void parodytiRezultatuLentele(std::ostream& out, const Vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);

/**
 * @brief Išveda studentų sąrašą pagal pasirinktą išvedimo būdą.
 * @param pasirinkimasIsvedimo Išvedimo būdo numeris.
 * @param studentuSarasas Studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Galutinio pažymio skaičiavimo metodas.
 */
STUDMAN_API void isvestiStudentus(int pasirinkimasIsvedimo, const Vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);

/**
 * @brief Apdoroja studentų sąrašą ir išveda rezultatus.
 * @param studentuSarasas Studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Galutinio pažymio skaičiavimo metodas.
 */
STUDMAN_API void apdorotiIrIsvestiStudentus(Vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);

/**
 * @brief Išveda studentus į ekraną.
 * @param studentai Studentų sąrašas.
 * @param skaiciavimoMetodas Galutinio pažymio skaičiavimo metodas.
 */
STUDMAN_API void parodytiStudentus(const Vector<Studentas>& studentai, char skaiciavimoMetodas);

/**
 * @brief Spausdina testavimo laikų vidurkius.
 * @param laikai Testavimo laikų struktūra.
 */
STUDMAN_API void spausdintiVidurkius(const TestoLaikai& laikai);

/**
 * @brief Vykdo studentų duomenų generavimą ir įrašymą į failą.
 * @param failai Vardų ir pavardžių failų duomenų struktūra.
 */
STUDMAN_API void vykdytiIrasymaIFaila(Failai& failai);

/**
 * @brief Įrašo sugeneruotus studentų duomenis į failą.
 * @param studentuSarasas Studentų sąrašas.
 * @param maksimalusNDKiekis Maksimalus namų darbų kiekis.
 * @param studentuKiekis Studentų kiekis.
 * @param failai Vardų ir pavardžių failų duomenų struktūra.
 */
STUDMAN_API void irasytiStudentuDuomenisIFaila(Vector<Studentas>& studentuSarasas, int maksimalusNDKiekis, int studentuKiekis, Failai& failai);

#endif