#ifndef STRUKTURAGENERAVIMAS_H
#define STRUKTURAGENERAVIMAS_H

#include <vector>
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/Failai.h"

void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis);
void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes);
int generuotiSveikaSkaiciu(int nuo, int iki);
std::vector<StudentasVektorius> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai);

#endif