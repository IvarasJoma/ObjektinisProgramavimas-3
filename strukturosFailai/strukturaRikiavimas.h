#ifndef STRUKTURARIKIAVIMAS_H
#define STRUKTURARIKIAVIMAS_H

#include <vector>
#include "../Studentas.h"
#include "../Vector.h"
#include "../StudManAPI.h"

/**
 * @file strukturaRikiavimas.h
 * @brief Funkcijos studentų sąrašams rikiuoti.
 */

/**
 * @brief Rikiuoja studentų sąrašą pagal pasirinktą kriterijų.
 *
 * Tipiniai pasirinkimai:
 * - pagal vardą;
 * - pagal pavardę;
 * - pagal galutinį pažymį.
 *
 * @param pasirinkimasRikiavimo Rikiavimo kriterijaus numeris.
 * @param studentuSarasas Studentų sąrašas, kuris bus rikiuojamas.
 */
STUDMAN_API void rikiuotiStudentus(int pasirinkimasRikiavimo, Vector<Studentas>& studentuSarasas);
/**
 * @brief Rikiuoja pažangių ir silpnų studentų sąrašus pagal pasirinktus kriterijus.
 * @param pazangiuSarasas Pažangių studentų sąrašas.
 * @param silpnuSarasas Silpnų studentų sąrašas.
 * @param pasirinkimasRikiavimoPazangiu Pažangių studentų rikiavimo kriterijus.
 * @param pasirinkimasRikiavimoSilpnu Silpnų studentų rikiavimo kriterijus.
 */
STUDMAN_API void rikiuotiSuskirstytusStudentus(Vector<Studentas>& pazangiuSarasas, Vector<Studentas>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu);

#endif