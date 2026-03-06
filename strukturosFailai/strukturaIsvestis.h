#ifndef STRUKTURAISVESTIS_H
#define STRUKTURAISVESTIS_H

#include <vector>
#include <string>
#include <ostream>
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/strukturaTestavimas.h"

void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void apdorotiIrIsvestiStudentus(std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas, int pasirinkimasNuskaitymo);
void parodytiStudentus(const std::vector<StudentasVektorius>& studentai, char skaiciavimoMetodas);
void spausdintiVidurkius(const TestoLaikai& laikai);

#endif