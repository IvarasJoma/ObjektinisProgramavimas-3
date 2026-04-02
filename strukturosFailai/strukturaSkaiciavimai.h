#ifndef STRUKTURASKAICIAVIMAI_H
#define STRUKTURASKAICIAVIMAI_H

#include <vector>
#include "../strukturosFailai/VektoriuStudentoStruktura.h"

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const Studentas& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const Studentas& studentas);
template<typename T, typename Member> auto lygintiElementusPagalDidejanciaReiksme(Member T::*member){ return [member](const T& a, const T& b){ return a.*member < b.*member; }; }
template<typename T, typename Member> auto lygintiElementusPagalMazejanciaReiksme(Member T::*member){ return [member](const T& a, const T& b){ return a.*member > b.*member; }; }
void apskaiciuotiGalutiniPazymi(Studentas& studentas, char skaiciavimoMetodoPasirinkimas);
void apskaiciuotiGalutiniusPazymius(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void suskirstytiStudentus(const std::vector<Studentas>& studentuSarasas, std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas);

#endif