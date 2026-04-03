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
                /*case 9:
                    vykdytiNulintajaKonteineriuTestavimoStrategija();
                    break;
                case 10:
                    vykdytiPirmajaKonteineriuTestavimoStrategija();
                    break;
                case 11:
                    vykdytiAntrajaKonteineriuTestavimoStrategija();
                    break;
                case 12:
                    vykdytiTreciajaKonteineriuTestavimoStrategija();
                    break;*/
                case 13: {
                    TestoLaikai laikai;
                    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
                    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
                    std::string katalogas = "KonteineriuTyrimuiSkirtiFailai";
                    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
                    for (int i = 0; i < kartai; ++i) {
                        std::vector<Studentas> studentuSarasas;
                        std::vector<Studentas> silpnuSarasas;
                        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
                        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
                        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentusEfektyviau(studentuSarasas, silpnuSarasas);});
                    }
                    gautiVidurki(laikai, kartai);
                    spausdintiVidurkius(laikai);
                    break;
                }    
                case 14:
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