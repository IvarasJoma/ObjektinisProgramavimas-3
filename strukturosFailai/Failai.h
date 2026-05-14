#ifndef FAILAI_H
#define FAILAI_H

#include <vector>
#include <string>
#include "../strukturosFailai/strukturaDarbasSuFailais.h"

/**
 * @file Failai.h
 * @brief Failų, kuriuose saugomi vardai ir pavardės, nuskaitymo struktūra.
 *
 * Šiame faile aprašoma struktūra @ref Failai, kuri saugo lietuviškų vyrų ir moterų
 * vardų bei pavardžių sąrašus. Duomenys nuskaitomi iš tekstinių failų naudojant
 * funkciją @ref nuskaitytiEilutesIVektoriu.
 */

/**
 * @struct Failai
 * @brief Saugo vardų ir pavardžių sąrašus, naudojamus studentų generavimui.
 *
 * Struktūra automatiškai inicijuoja keturis vektorius, nuskaitydama duomenis
 * iš nurodytų tekstinių failų.
 */
struct Failai{
    Vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviski_vyru_vardai.txt");
    Vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviskos_vyru_pavardes.txt");
    Vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviski_moteru_vardai.txt");
    Vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviskos_moteru_pavardes.txt");
};

#endif