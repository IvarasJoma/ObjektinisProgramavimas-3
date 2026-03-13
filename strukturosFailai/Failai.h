#ifndef FAILAI_H
#define FAILAI_H

#include <vector>
#include <string>
#include "../strukturosFailai/strukturaDarbasSuFailais.h"

struct Failai{
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("VarduIrPavardziuSarasai/Lietuviskos_moteru_pavardes.txt");
};

#endif