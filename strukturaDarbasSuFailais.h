#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include "strukturaStudentas.h"

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, int kiekis);

#endif