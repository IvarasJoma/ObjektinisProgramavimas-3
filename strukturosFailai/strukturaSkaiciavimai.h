#ifndef STRUKTURASKAICIAVIMAI_H
#define STRUKTURASKAICIAVIMAI_H

#include <vector>
#include "../Studentas.h"
#include "../Vector.h"
#include "../StudManAPI.h"

/**
 * @file strukturaSkaiciavimai.h
 * @brief Funkcijos studentų pažymių skaičiavimui ir skirstymui.
 */

/**
 * @brief Apskaičiuoja namų darbų pažymių vidurkį.
 * @param ndPazymiai Namų darbų pažymių vektorius.
 * @return Namų darbų pažymių vidurkis.
 */
STUDMAN_API double skaiciuotiNDVidurki(const Vector<int>& ndPazymiai);

/**
 * @brief Apskaičiuoja galutinį pažymį pagal namų darbų vidurkį.
 * @param studentas Studentas, kurio pažymys skaičiuojamas.
 * @return Galutinis pažymys pagal vidurkį.
 */
STUDMAN_API double skaiciuotiGalutiniVidurki(const Studentas& studentas);

/**
 * @brief Apskaičiuoja namų darbų pažymių medianą.
 * @param ndPazymiai Namų darbų pažymių vektorius.
 * @return Namų darbų pažymių mediana.
 */
STUDMAN_API double skaiciuotiNDMediana(Vector<int> ndPazymiai);

/**
 * @brief Apskaičiuoja galutinį pažymį pagal namų darbų medianą.
 * @param studentas Studentas, kurio pažymys skaičiuojamas.
 * @return Galutinis pažymys pagal medianą.
 */
STUDMAN_API double skaiciuotiGalutineMediana(const Studentas& studentas);
/**
 * @brief Sukuria palyginimo funkciją rikiavimui didėjančia tvarka.
 *
 * @tparam T Objekto tipas.
 * @tparam Ret Getter funkcijos grąžinamas tipas.
 * @param getter Klasės getter metodo rodyklė.
 * @return Lambda funkcija, tinkama rikiavimui didėjančia tvarka.
 */
template<typename T, typename Ret>
auto lygintiElementusPagalDidejanciaReiksme(Ret (T::*getter)() const) {
    return [getter](const T& a, const T& b) {
        return (a.*getter)() < (b.*getter)();
    };
}
/**
 * @brief Sukuria palyginimo funkciją rikiavimui mažėjančia tvarka.
 *
 * @tparam T Objekto tipas.
 * @tparam Ret Getter funkcijos grąžinamas tipas.
 * @param getter Klasės getter metodo rodyklė.
 * @return Lambda funkcija, tinkama rikiavimui mažėjančia tvarka.
 */
template<typename T, typename Ret>
auto lygintiElementusPagalMazejanciaReiksme(Ret (T::*getter)() const) {
    return [getter](const T& a, const T& b) {
        return (a.*getter)() > (b.*getter)();
    };
}
/**
 * @brief Apskaičiuoja ir nustato vieno studento galutinį pažymį.
 * @param studentas Studentas, kurio pažymys skaičiuojamas.
 * @param skaiciavimoMetodoPasirinkimas Skaičiavimo metodo pasirinkimas.
 */
STUDMAN_API void apskaiciuotiGalutiniPazymi(Studentas& studentas, char skaiciavimoMetodoPasirinkimas);
/**
 * @brief Apskaičiuoja ir nustato galutinius pažymius visiems studentams.
 * @param studentuSarasas Studentų sąrašas.
 * @param skaiciavimoMetodoPasirinkimas Skaičiavimo metodo pasirinkimas.
 */
STUDMAN_API void apskaiciuotiGalutiniusPazymius(Vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
/**
 * @brief Suskirsto studentus į pažangius ir silpnus pagal galutinį pažymį.
 *
 * Studentai, kurių galutinis pažymys mažesnis nei `5.0`, priskiriami silpniems.
 * Likę studentai priskiriami pažangiems.
 *
 * @param studentuSarasas Pradinis studentų sąrašas.
 * @param pazangiuSarasas Pažangių studentų sąrašas.
 * @param silpnuSarasas Silpnų studentų sąrašas.
 */
STUDMAN_API void suskirstytiStudentus(const Vector<Studentas>& studentuSarasas, Vector<Studentas>& pazangiuSarasas, Vector<Studentas>& silpnuSarasas);

#endif