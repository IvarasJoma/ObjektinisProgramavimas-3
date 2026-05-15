#ifndef STRUKTURAGENERAVIMAS_H
#define STRUKTURAGENERAVIMAS_H

#include <vector>
#include "../Vector.h"
#include "../Studentas.h"
#include "../strukturosFailai/Failai.h"
#include "../StudManAPI.h"

/**
 * @file strukturaGeneravimas.h
 * @brief Funkcijos studentų vardams, pavardėms ir pažymiams generuoti.
 */

/**
 * @brief Sugeneruoja namų darbų pažymius ir egzamino rezultatą.
 * @param maksimalusNDKiekis Maksimalus namų darbų kiekis.
 * @return Pora: namų darbų pažymių vektorius ir egzamino pažymys.
 */
STUDMAN_API std::pair<Vector<int>, int> generuotiRezultatus(int maksimalusNDKiekis);

/**
 * @brief Sugeneruoja atsitiktinį vardą ir pavardę.
 * @param vyrVardai Vyrų vardų sąrašas.
 * @param vyrPavardes Vyrų pavardžių sąrašas.
 * @param motVardai Moterų vardų sąrašas.
 * @param motPavardes Moterų pavardžių sąrašas.
 * @return Pora: sugeneruotas vardas ir pavardė.
 */
STUDMAN_API std::pair<std::string, std::string> generuotiVardaPavarde(const Vector<std::string>& vyrVardai, const Vector<std::string>& vyrPavardes, const Vector<std::string>& motVardai, const Vector<std::string>& motPavardes);

/**
 * @brief Sugeneruoja atsitiktinį sveikąjį skaičių nurodytame intervale.
 * @param nuo Apatinė intervalo riba.
 * @param iki Viršutinė intervalo riba.
 * @return Atsitiktinis sveikasis skaičius iš intervalo `[nuo; iki]`.
 */
STUDMAN_API int generuotiSveikaSkaiciu(int nuo, int iki);

/**
 * @brief Sugeneruoja nurodytą kiekį studentų.
 * @param studentuKiekis Studentų kiekis.
 * @param maksimalusNDKiekis Maksimalus namų darbų kiekis.
 * @param failai Struktūra su vardų ir pavardžių sąrašais.
 * @return Sugeneruotų studentų vektorius.
 */
STUDMAN_API Vector<Studentas> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai);

#endif