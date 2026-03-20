#include "strukturaVisi.h"
#include <iostream>
#include <algorithm>
#include <fstream>

int main(){
    try {
        Failai failai;
        int pasirinkimas = 0;
        while (nuskaitytiPagrindinioMeniuPasirinkima(PAGRINDINIS_MENIU, pasirinkimas)) {
            switch (pasirinkimas) {
                case 1: 
                    vykdytiStudentuIvedima(false);
                    break;
                case 2:
                    vykdytiStudentuIvedima(true);
                    break;
                case 3:
                    vykdytiPilnaGeneravima(failai);
                    break;
                case 4:
                    vykdytiNuskaitymaIsFailo();
                    break;
                case 5:
                    vykdytiIrasymaIFaila(failai);
                    break;
                case 6:
                    vykdytiIvedimoTestavima();
                    break;
                case 7:
                    vykdytiIsvedimoTestavima(failai);
                    break;
                case 8:
                    vykdytiDuomenuApdorojimoTestavima();
                    break;
                case 9:
                    vykdytiNulintajaKonteineriuTestavimoStrategija();
                    break;
                    /*Labai svarbu, kadangi tiek failų kūrimas, tiek ir surūšiuotų rezultatų išvedimas į failus nepriklauso nuo naudojamo konteinerio, todėl šioje užduotyje reiktų matuoti tik šiuos programoje atliekamus žingsnius:

    duomenų nuskaitymą iš failų į atitinkamą konteinerį (Failai visiems tyrimams turi būti tie patys, tyrimo patikimumui); 
    studentų rūšiavimą didėjimo tvarką konteineryje (funkcija sort);
    studentų skirstymo  į dvi grupes/kategorijas (naujų konteinerių su skirtingais studentais kūrimas);

Testavimas atliekamas su tais pačiais failais iš 1000, 10000, 100000, 1000000, 10000000 įrašų. Visi rezultatai turi būti apdoroti ir aprašyti readme.md faile, pateikiant testavimo sistemos parametrus (CPU, RAM, HDD (magnetinis, SSD)). */
                case 10:
                    vykdytiPirmajaKonteineriuTestavimoStrategija();
                case 11:
                    vykdytiAntrajaKonteineriuTestavimoStrategija();
                case 12:
                    vykdytiTreciajaKonteineriuTestavimoStrategija();
                case 13:
                    return 0;
                default:
                    break;
            }
        }
        return 0;
    } catch(const std::exception& e){
        std::cerr << "Klaida: " << e.what() << std::endl;
        return 1;
    }
}