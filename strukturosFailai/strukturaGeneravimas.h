#ifndef STRUKTURAGENERAVIMAS_H
#define STRUKTURAGENERAVIMAS_H

#include <vector>
#include "../Studentas.h"
#include "../strukturosFailai/Failai.h"

std::pair<std::vector<int>, int> generuotiRezultatus(int maksimalusNDKiekis);
std::pair<std::string, std::string> generuotiVardaPavarde(const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes);
int generuotiSveikaSkaiciu(int nuo, int iki);
std::vector<Studentas> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai);

#endif