#ifndef STRUKTURASKAICIAVIMAI_H
#define STRUKTURASKAICIAVIMAI_H

#include <vector>
#include "../Studentas.h"

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const Studentas& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const Studentas& studentas);
template<typename T, typename Ret>
auto lygintiElementusPagalDidejanciaReiksme(Ret (T::*getter)() const) {
    return [getter](const T& a, const T& b) {
        return (a.*getter)() < (b.*getter)();
    };
}
template<typename T, typename Ret>
auto lygintiElementusPagalMazejanciaReiksme(Ret (T::*getter)() const) {
    return [getter](const T& a, const T& b) {
        return (a.*getter)() > (b.*getter)();
    };
}
void apskaiciuotiGalutiniPazymi(Studentas& studentas, char skaiciavimoMetodoPasirinkimas);
void apskaiciuotiGalutiniusPazymius(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void suskirstytiStudentus(const std::vector<Studentas>& studentuSarasas, std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas);

#endif