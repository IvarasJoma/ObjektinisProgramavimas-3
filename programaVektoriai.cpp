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
                    vykdytiNuskaitymaIsFailo(failai);
                    break;
                case 5:
                    vykdytiIrasymaIFaila();
                case 6:
                    vykdytiIvedimoTestavima(failai);
                    break;
                case 7:
                    vykdytiIsvedimoTestavima();
                    break;
                case 8:
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