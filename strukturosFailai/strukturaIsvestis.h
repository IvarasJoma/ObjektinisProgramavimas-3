#ifndef STRUKTURAISVESTIS_H
#define STRUKTURAISVESTIS_H

#include <vector>
#include <string>
#include <ostream>
#include "../strukturosFailai/strukturaStudentas.h"
#include "../strukturosFailai/strukturaTestavimas.h"

void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void apdorotiIrIsvestiStudentus(std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void parodytiStudentus(const std::vector<StudentasVektorius>& studentai, char skaiciavimoMetodas);
void spausdintiVidurkius(const TestoLaikai& laikai);
void vykdytiIrasymaIFaila(Failai& failai);
void irasytiStudentuDuomenisIFaila(std::vector<StudentasVektorius>& studentuSarasas, int maksimalusNDKiekis, int studentuKiekis, Failai& failai);

#endif