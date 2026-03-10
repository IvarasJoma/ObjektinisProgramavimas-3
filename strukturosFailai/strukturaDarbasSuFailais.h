#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include "../strukturosFailai/strukturaStudentas.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas, std::size_t kiekis);
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas, Failai failai);
void vykdytiNuskaitymaIsFailo(Failai& failai);
void irasytiDuomenis(int pasirinkimasIrasymo, std::vector<StudentasVektorius>& studentuSarasas);

#endif