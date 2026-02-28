#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include "strukturaStudentas.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, int kiekis);
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas, Failai failai);

#endif