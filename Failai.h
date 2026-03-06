#ifndef FAILAI_H
#define FAILAI_H

#include <vector>
#include <string>
#include "strukturaDarbasSuFailais.h"

struct Failai{
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    std::string studentai10000 = "tekstiniaiFailai/studentai10000.txt";
    std::string studentai100000 = "tekstiniaiFailai/studentai100000.txt";
    std::string studentai1000000 = "tekstiniaiFailai/studentai1000000.txt";
    std::string kursiokai = "tekstiniaiFailai/kursiokai.txt";
};

#endif