#ifndef SABLONINESFUNKCIJOS_H
#define SABLONINESFUNKCIJOS_H

#include <string>
#include <algorithm>
#include "../Vector.h"
#include <numeric>
#include <iostream>
#include "../strukturosFailai/strukturaDarbasSuFailais.h"
#include <fstream>
#include <list>
#include <type_traits>
#include <utility>

/**
 * @file SabloninesFunkcijos.h
 * @brief Šabloninės funkcijos, leidžiančios apdoroti studentus skirtinguose konteineriuose.
 *
 * Funkcijos pritaikytos darbui su tokiais konteineriais kaip `Vector` ir `std::list`.
 * Kai įmanoma, naudojamos konteinerio specifinės operacijos, pavyzdžiui, `list::sort`.
 */

/**
 * @brief Nuskaito studentų duomenis iš failo į pasirinktą konteinerį.
 *
 * Funkcija nuskaito failo antraštę, pagal ją nustato namų darbų kiekį,
 * o kiekvieną kitą eilutę bando konvertuoti į @ref Studentas objektą.
 * Nekorektiškos eilutės praleidžiamos.
 *
 * @tparam StudentuKonteineris Konteinerio tipas, pvz. `Vector<Studentas>` arba `std::list<Studentas>`.
 * @param failas Failo kelias.
 * @return Konteineris su nuskaitytais studentais.
 *
 * @throws std::runtime_error Jei failo nepavyksta atidaryti.
 */
template <typename StudentuKonteineris>
StudentuKonteineris nuskaitytiStudentuDuomenisIsFailo(const std::string& failas) {
    StudentuKonteineris studentuSarasas;
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    try {
        static char ivestiesBuferis[1 << 20];
        std::setvbuf(skaitomasFailas, ivestiesBuferis, _IOFBF, sizeof(ivestiesBuferis));
        char antraste[257];
        if (!std::fgets(antraste, sizeof(antraste), skaitomasFailas)) {
            std::fclose(skaitomasFailas);
            return studentuSarasas;
        }
        std::size_t namuDarbuKiekis = 0;
        char laikinaEilute[257];
        std::strncpy(laikinaEilute, antraste, sizeof(laikinaEilute));
        laikinaEilute[sizeof(laikinaEilute) - 1] = '\0';
        char* stulpelis = std::strtok(laikinaEilute, " \t\r\n");
        while (stulpelis) {
            if (stulpelis[0] == 'N' && stulpelis[1] == 'D') namuDarbuKiekis++;
            stulpelis = std::strtok(nullptr, " \t\r\n");
        }
        char eilute[1024];
        while (std::fgets(eilute, sizeof(eilute), skaitomasFailas)) {
            try {
                Studentas studentas(eilute, namuDarbuKiekis);
                studentuSarasas.push_back(std::move(studentas));
            } catch (...) {
                continue;
            }
        }
        std::fclose(skaitomasFailas);
        return studentuSarasas;
    }
    catch (const std::bad_alloc&) {
        std::fclose(skaitomasFailas);
        std::cerr << "Nepakanka atminties...\n";
        return studentuSarasas;
    }
}

/**
 * @brief Rikiuoja studentus pagal pasirinktą kriterijų.
 *
 * Pasirinkimai:
 * - `1` — pagal vardą;
 * - `2` — pagal pavardę;
 * - `3` — pagal galutinį pažymį.
 *
 * Jei konteineris turi metodą `sort`, naudojamas jis. Kitu atveju naudojama `std::sort`.
 *
 * @tparam StudentuKonteineris Studentų konteinerio tipas.
 * @param pasirinkimasRikiavimo Rikiavimo kriterijaus numeris.
 * @param studentuSarasas Studentų konteineris, kuris bus rikiuojamas.
 */
template <typename StudentuKonteineris>
void rikiuotiStudentus(int pasirinkimasRikiavimo, StudentuKonteineris& studentuSarasas) {
    using StudentasTipas = typename StudentuKonteineris::value_type;
    auto rikiuoti = [&](auto comparator) {
        if constexpr (requires { studentuSarasas.sort(comparator); }) studentuSarasas.sort(comparator);
        else std::sort(studentuSarasas.begin(), studentuSarasas.end(), comparator);
    };
    if (pasirinkimasRikiavimo == 1) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getName));
    else if (pasirinkimasRikiavimo == 2) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getSurname));
    else if (pasirinkimasRikiavimo == 3) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getFinalGrade));
}

/**
 * @brief Apskaičiuoja galutinį pažymį visiems studentams konteineryje.
 * @tparam StudentuKonteineris Studentų konteinerio tipas.
 * @param duomenys Studentų konteineris.
 * @param metodas Skaičiavimo metodas, pvz. vidurkis arba mediana.
 */
template <typename StudentuKonteineris>
void apskaiciuotiGalutiniusPazymius(StudentuKonteineris& duomenys, char metodas) {
    for (auto& studentas : duomenys) studentas.setFinalGrade(studentas.calculateFinalGrade(metodas));
}

/**
 * @brief Perkelia studentus į pažangių ir silpnų studentų konteinerius.
 *
 * Studentai, kurių galutinis pažymys mažesnis nei `5.0`, perkeliami į silpnų studentų sąrašą.
 * Kiti studentai perkeliami į pažangių studentų sąrašą.
 *
 * @tparam SaltinioKonteineris Pradinio studentų konteinerio tipas.
 * @tparam RezultatoKonteineris Rezultato konteinerio tipas.
 * @param studentai Pradinis studentų konteineris.
 * @param pazangusStudentai Konteineris pažangiems studentams.
 * @param silpniStudentai Konteineris silpniems studentams.
 */
template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void perkeltiStudentus(SaltinioKonteineris& studentai,
                       RezultatoKonteineris& pazangusStudentai,
                       RezultatoKonteineris& silpniStudentai) {
    pazangusStudentai.clear();
    silpniStudentai.clear();
    if constexpr (requires { pazangusStudentai.reserve(studentai.size() / 2); }) pazangusStudentai.reserve(studentai.size() / 2);
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    for (auto& studentas : studentai) {
        if (studentas.getFinalGrade() < 5.0) silpniStudentai.push_back(std::move(studentas));
        else pazangusStudentai.push_back(std::move(studentas));
    }
}

/**
 * @brief Išskiria silpnus studentus iš pradinio konteinerio naudojant `std::partition`.
 *
 * Po funkcijos vykdymo pradiniame konteineryje lieka tik pažangūs studentai,
 * o silpni studentai perkeliami į atskirą konteinerį.
 *
 * @tparam SaltinioKonteineris Pradinio studentų konteinerio tipas.
 * @tparam RezultatoKonteineris Rezultato konteinerio tipas.
 * @param studentai Pradinis studentų konteineris.
 * @param silpniStudentai Konteineris silpniems studentams.
 */
template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void skirstytiIstrinantStudentus(SaltinioKonteineris& studentai,
                                 RezultatoKonteineris& silpniStudentai) {
    silpniStudentai.clear();
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    auto it = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) { return studentas.getFinalGrade() < 5.0; });
    silpniStudentai.insert(silpniStudentai.end(), std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    studentai.erase(studentai.begin(), it);
}

/**
 * @brief Išskiria silpnus studentus naudojant `std::remove_if`.
 *
 * Funkcija nukopijuoja silpnus studentus į rezultatų konteinerį ir pašalina juos
 * iš pradinio konteinerio.
 *
 * @tparam SaltinioKonteineris Pradinio studentų konteinerio tipas.
 * @tparam RezultatoKonteineris Rezultato konteinerio tipas.
 * @param studentai Pradinis studentų konteineris.
 * @param silpniStudentai Konteineris silpniems studentams.
 */
template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void skirstytiIstrinantStudentusEfektyviau(SaltinioKonteineris& studentai, RezultatoKonteineris& silpniStudentai) {
    silpniStudentai.clear();
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& studentas) {
        if (studentas.getFinalGrade() < 5.0) {
            silpniStudentai.push_back(studentas);
            return true;
        }
            return false;
        });
    studentai.erase(it, studentai.end());
}

/**
 * @brief Nuskaito studentų duomenis iš pasirinkto katalogo failo į pasirinktą konteinerį.
 * @tparam StudentuKonteineris Studentų konteinerio tipas.
 * @param pasirinkimasNuskaitymo Pasirinkto failo numeris.
 * @param studentuSarasas Studentų konteineris, į kurį bus įrašyti duomenys.
 * @param katalogas Katalogas, kuriame ieškoma `.txt` failų.
 */
template <typename StudentuKonteineris>
void nuskaitytiDuomenisGeneric(int pasirinkimasNuskaitymo, StudentuKonteineris& studentuSarasas, std::string& katalogas) {
    try {
        auto failai = gautiTekstiniusFailus(katalogas);
        if (failai.empty()) throw std::runtime_error("Kataloge " + katalogas + " nerasta .txt failų.");
        if (pasirinkimasNuskaitymo < 1 ||
            static_cast<std::size_t>(pasirinkimasNuskaitymo) > failai.size()) {
            throw std::runtime_error("Neteisingas failo pasirinkimas.");
        }
        const std::size_t indeksas = static_cast<std::size_t>(pasirinkimasNuskaitymo - 1);
        const std::string failoKelias = failai[indeksas].string();
        studentuSarasas = nuskaitytiStudentuDuomenisIsFailo<StudentuKonteineris>(failoKelias);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida skaitant failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}

/**
 * @brief Rikiuoja pažangių ir silpnų studentų konteinerius pagal pasirinktus kriterijus.
 * @tparam StudentuKonteineris Studentų konteinerio tipas.
 * @param pazangiuSarasas Pažangių studentų konteineris.
 * @param silpnuSarasas Silpnų studentų konteineris.
 * @param pasirinkimasRikiavimoPazangiu Pažangių studentų rikiavimo kriterijus.
 * @param pasirinkimasRikiavimoSilpnu Silpnų studentų rikiavimo kriterijus.
 */
template <typename StudentuKonteineris>
void rikiuotiSuskirstytusStudentus(StudentuKonteineris& pazangiuSarasas, StudentuKonteineris& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu) {
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}

#endif