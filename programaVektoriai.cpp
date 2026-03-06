#include "strukturaVisi.h"
#include <iostream>
#include <algorithm>
#include <fstream>

int main(){
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
                vykdytiTestavima(failai);
                break;
            case 6:
                return 0;
            default:
                break;
        }
    }
    return 0;
}    