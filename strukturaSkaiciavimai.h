#ifndef STRUKTURASKAICIAVIMAI_H
#define STRUKTURASKAICIAVIMAI_H

#include <vector>
#include "strukturaStudentas.h"

double skaiciuotiNDVidurki(const std::vector<int>& ndPazymiai);
double skaiciuotiGalutiniVidurki(const StudentasVektorius& studentas);
double skaiciuotiNDMediana(std::vector<int> ndPazymiai);
double skaiciuotiGalutineMediana(const StudentasVektorius& studentas);
template<typename T, typename Member> auto lygintiElementusPagalDidejanciaReiksme(Member T::*member) { return [member](const T& a, const T& b) { return a.*member < b.*member; }; }
template<typename T, typename Member> auto lygintiElementusPagalMazejanciaReiksme(Member T::*member) { return [member](const T& a, const T& b) { return a.*member > b.*member; }; }
void apskaiciuotiGalutiniPazymi(StudentasVektorius& studentas, char skaiciavimoMetodoPasirinkimas);

#endif