#ifndef STRUKTURATESTAVIMAS_H
#define STRUKTURATESTAVIMAS_H

#include "../strukturosFailai/Failai.h"
#include <chrono>

/**
 * @file strukturaTestavimas.h
 * @brief Programos veikimo greičio ir konteinerių strategijų testavimo funkcijos.
 */

/**
 * @struct TestoLaikai
 * @brief Saugo atskirų programos etapų vykdymo laikus.
 */
struct TestoLaikai{
    /** @brief Duomenų nuskaitymo laikas sekundėmis. */
    double nuskaitymas = 0.0;

    /** @brief Galutinių pažymių skaičiavimo laikas sekundėmis. */
    double skaiciavimas = 0.0;

    /** @brief Studentų rikiavimo laikas sekundėmis. */
    double rikiavimas = 0.0;

    /** @brief Studentų skirstymo laikas sekundėmis. */
    double skirstymas = 0.0;

    /** @brief Rezultatų išvedimo laikas sekundėmis. */
    double isvedimas = 0.0;
};

/**
 * @brief Apskaičiuoja bendrą testavimo laiką.
 * @param laikai Struktūra su atskirų etapų laikais.
 * @return Bendras laikas sekundėmis.
 */
double apskaiciuotiBendraLaika(const TestoLaikai& laikai);

/**
 * @brief Apskaičiuoja vidutinius laikus pagal atliktų testų kiekį.
 * @param laikai Laikų struktūra, kurios reikšmės bus padalintos iš testų kiekio.
 * @param kiekis Testų kiekis.
 */
void gautiVidurki(TestoLaikai& laikai, int kiekis);

/**
 * @brief Apskaičiuoja laiko skirtumą tarp dviejų momentų.
 * @param startas Pradžios laiko momentas.
 * @param pabaiga Pabaigos laiko momentas.
 * @return Laiko skirtumas sekundėmis.
 */
double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga);

/**
 * @brief Išmatuoja perduotos funkcijos arba veiksmo vykdymo laiką.
 * @tparam Func Funkcijos arba lambda tipas.
 * @param veiksmas Veiksmas, kurio vykdymo laikas matuojamas.
 * @return Vykdymo laikas sekundėmis.
 */
template <typename Func> double ismatuotiLaika(Func veiksmas){
    auto pradzia = std::chrono::steady_clock::now();
    veiksmas();
    auto pabaiga = std::chrono::steady_clock::now();
    return apskaiciuotiLaika(pradzia, pabaiga);
}
/** @brief Vykdo studentų įvedimo testavimą. */
void vykdytiIvedimoTestavima();

/**
 * @brief Vykdo studentų išvedimo testavimą.
 * @param failai Vardų ir pavardžių failų duomenys.
 */
void vykdytiIsvedimoTestavima(Failai& failai);

/** @brief Vykdo bendrą duomenų apdorojimo testavimą. */
void vykdytiDuomenuApdorojimoTestavima();

/** @brief Vykdo nulinę konteinerių testavimo strategiją. */
void vykdytiNulintajaKonteineriuTestavimoStrategija();

/** @brief Vykdo pirmąją konteinerių testavimo strategiją. */
void vykdytiPirmajaKonteineriuTestavimoStrategija();

/** @brief Vykdo antrąją konteinerių testavimo strategiją. */
void vykdytiAntrajaKonteineriuTestavimoStrategija();

/** @brief Vykdo trečiąją konteinerių testavimo strategiją. */
void vykdytiTreciajaKonteineriuTestavimoStrategija();

/** @brief Vykdo trečiąją konteinerių testavimo strategiją tik su `std::vector`. */
void vykdytiTreciajaKonteineriuTestavimoStrategijaTikSuVektoriais();

/** @brief Testuoja @ref Studentas klasės funkcionalumą. */
void testuotiStudenta();

#endif