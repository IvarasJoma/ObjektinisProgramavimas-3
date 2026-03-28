#ifndef STRUKTURASKAICIAVIMAI_H
#define STRUKTURASKAICIAVIMAI_H

#include <vector>
#include "../strukturosFailai/VektoriuStudentoStruktura.h"

double gautiMediana(std::vector<int> ndPazymiai);
double gautiVidurki(const std::vector<int>& ndPazymiai);
template<typename T, typename Member> auto lygintiElementusPagalDidejanciaReiksme(Member T::*member){ return [member](const T& a, const T& b){ return a.*member < b.*member; }; }
template<typename T, typename Member> auto lygintiElementusPagalMazejanciaReiksme(Member T::*member){ return [member](const T& a, const T& b){ return a.*member > b.*member; }; }
void apskaiciuotiGalutiniusPazymius(std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void suskirstytiStudentus(const std::vector<StudentasVektorius>& studentuSarasas, std::vector<StudentasVektorius>& pazangiuSarasas, std::vector<StudentasVektorius>& silpnuSarasas);

#endif