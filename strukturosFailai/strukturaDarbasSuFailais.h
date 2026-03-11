#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include "../strukturosFailai/strukturaStudentas.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, std::size_t kiekis);
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas, Failai failai);
void vykdytiNuskaitymaIsFailo(Failai& failai);
void irasytiDuomenis(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiStudentuDuomenisIFaila(const std::vector<StudentasVektorius>& studentuSarasas, int maksimalusNDKiekis, std::string failoPavadinimas);
void vykdytiSkirstymaIFailus(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiSuskirstytusStudentusIFailus(const std::vector<StudentasVektorius>& pazangiuSarasas, const std::vector<StudentasVektorius>& silpnuSarasas);

#endif