#include "../strukturosFailai/StudentoKlase.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"

Studentas::Studentas(std::istream& ivestis){
    nuskaitytiStudenta(ivestis);
}

double Studentas::apskaiciuotiGalutini(double (*apskaiciuoti) (std::vector<int>)) const {
    double ndRezultatas = apskaiciuoti(namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndRezultatas + 0.6 * egzaminoRezultatas;
}