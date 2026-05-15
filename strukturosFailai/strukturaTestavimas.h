#ifndef STRUKTURATESTAVIMAS_H
#define STRUKTURATESTAVIMAS_H

#include "../strukturosFailai/Failai.h"
#include <chrono>
#include "../Vector.h"
#include "../StudManAPI.h"

/**
 * @file strukturaTestavimas.h
 * @brief Programos veikimo greičio, konteinerių strategijų ir Studentas klasės testavimo funkcijos.
 */

/**
 * @struct TestoLaikai
 * @brief Saugo atskirų programos etapų vykdymo laikus.
 */
struct STUDMAN_API TestoLaikai {
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
STUDMAN_API double apskaiciuotiBendraLaika(const TestoLaikai& laikai);

/**
 * @brief Apskaičiuoja vidutinius laikus pagal atliktų testų kiekį.
 * @param laikai Laikų struktūra, kurios reikšmės bus padalintos iš testų kiekio.
 * @param kiekis Testų kiekis.
 */
STUDMAN_API void gautiVidurki(TestoLaikai& laikai, int kiekis);

/**
 * @brief Apskaičiuoja laiko skirtumą tarp dviejų momentų.
 * @param startas Pradžios laiko momentas.
 * @param pabaiga Pabaigos laiko momentas.
 * @return Laiko skirtumas sekundėmis.
 */
STUDMAN_API double apskaiciuotiLaika(
    std::chrono::steady_clock::time_point startas,
    std::chrono::steady_clock::time_point pabaiga
);

/**
 * @brief Išmatuoja perduotos funkcijos arba veiksmo vykdymo laiką.
 * @tparam Func Funkcijos arba lambda tipas.
 * @param veiksmas Veiksmas, kurio vykdymo laikas matuojamas.
 * @return Vykdymo laikas sekundėmis.
 */
template <typename Func>
double ismatuotiLaika(Func veiksmas) {
    auto pradzia = std::chrono::steady_clock::now();
    veiksmas();
    auto pabaiga = std::chrono::steady_clock::now();
    return apskaiciuotiLaika(pradzia, pabaiga);
}

/**
 * @brief Vykdo studentų įvedimo testavimą.
 */
STUDMAN_API void vykdytiIvedimoTestavima();

/**
 * @brief Vykdo studentų išvedimo testavimą.
 * @param failai Vardų ir pavardžių failų duomenys.
 */
STUDMAN_API void vykdytiIsvedimoTestavima(Failai& failai);

/**
 * @brief Vykdo bendrą duomenų apdorojimo testavimą.
 */
STUDMAN_API void vykdytiDuomenuApdorojimoTestavima();

/**
 * @brief Vykdo nulinę konteinerių testavimo strategiją.
 */
STUDMAN_API void vykdytiNulintajaKonteineriuTestavimoStrategija();

/**
 * @brief Vykdo pirmąją konteinerių testavimo strategiją.
 */
STUDMAN_API void vykdytiPirmajaKonteineriuTestavimoStrategija();

/**
 * @brief Vykdo antrąją konteinerių testavimo strategiją.
 */
STUDMAN_API void vykdytiAntrajaKonteineriuTestavimoStrategija();

/**
 * @brief Vykdo trečiąją konteinerių testavimo strategiją.
 */
STUDMAN_API void vykdytiTreciajaKonteineriuTestavimoStrategija();

/**
 * @brief Vykdo trečiąją konteinerių testavimo strategiją tik su `Vector`.
 */
STUDMAN_API void vykdytiTreciajaKonteineriuTestavimoStrategijaTikSuVektoriais();

/**
 * @name Studentas klasės Google Test pagalbinės funkcijos
 * @brief Atskiros funkcijos, kurias kviečia Google Test `TEST(...)` blokai.
 *
 * Šios funkcijos naudoja Google Test makrokomandas savo `.cpp` faile.
 * Į šį `.h` failą `#include <gtest/gtest.h>` dėti nereikia.
 */
///@{

/**
 * @brief Testuoja numatytąjį `Studentas` konstruktorių.
 */
STUDMAN_API void testuotiDefaultKonstruktoriu();

/**
 * @brief Testuoja parametrinį `Studentas` konstruktorių.
 */
STUDMAN_API void testuotiParametriniKonstruktoriu();

/**
 * @brief Testuoja `Studentas` konstruktorių, kuris sukuria objektą iš tekstinės eilutės.
 */
STUDMAN_API void testuotiKonstruktoriuIsEilutes();

/**
 * @brief Testuoja `Studentas` setterius ir getterius.
 */
STUDMAN_API void testuotiSetteriusIrGetterius();

/**
 * @brief Testuoja namų darbų pažymių pridėjimą, rezervavimą ir išvalymą.
 */
STUDMAN_API void testuotiNamuDarbuPazymiuValdyma();

/**
 * @brief Testuoja galutinio pažymio skaičiavimą pagal namų darbų vidurkį.
 */
STUDMAN_API void testuotiGalutinioPazymioSkaiciavimaPagalVidurki();

/**
 * @brief Testuoja `Studentas` kopijavimo konstruktorių.
 */
STUDMAN_API void testuotiCopyKonstruktoriu();

/**
 * @brief Testuoja `Studentas` kopijavimo priskyrimo operatorių.
 */
STUDMAN_API void testuotiCopyPriskyrimoOperatoriu();

/**
 * @brief Testuoja savęs priskyrimo atvejį naudojant kopijavimo priskyrimo operatorių.
 */
STUDMAN_API void testuotiSelfCopyAssignment();

/**
 * @brief Testuoja `Studentas` perkėlimo konstruktorių.
 */
STUDMAN_API void testuotiMoveKonstruktoriu();

/**
 * @brief Testuoja `Studentas` perkėlimo priskyrimo operatorių.
 */
STUDMAN_API void testuotiMovePriskyrimoOperatoriu();

/**
 * @brief Testuoja `Studentas` išvesties operatorių `operator<<`.
 */
STUDMAN_API void testuotiIsvestiesOperatoriu();

/**
 * @brief Testuoja `Studentas` įvesties operatorių `operator>>`.
 */
STUDMAN_API void testuotiIvestiesOperatoriu();

/**
 * @brief Testuoja `StudentasLentelei` išvesties operatorių `operator<<`.
 */
STUDMAN_API void testuotiStudentasLenteleiIsvestiesOperatoriu();

/**
 * @brief Testuoja paveldėjimo ryšį tarp `Zmogus` ir `Studentas`.
 */
STUDMAN_API void testuotiPaveldimumoStruktura();

/**
 * @brief Testuoja, ar `Studentas` destruktorius iškviečiamas ir sukuria tikėtiną šalutinį efektą.
 */
STUDMAN_API void testuotiDestruktoriu();

#endif