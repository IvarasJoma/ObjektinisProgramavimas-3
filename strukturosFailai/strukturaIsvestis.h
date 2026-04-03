#ifndef STRUKTURAISVESTIS_H
#define STRUKTURAISVESTIS_H

#include <vector>
#include <string>
#include <ostream>
#include "../Studentas.h"
#include "../strukturosFailai/strukturaTestavimas.h"

void parodytiRezultatuLentele(std::ostream& out, const std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void apdorotiIrIsvestiStudentus(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas);
void parodytiStudentus(const std::vector<Studentas>& studentai, char skaiciavimoMetodas);
void spausdintiVidurkius(const TestoLaikai& laikai);
void vykdytiIrasymaIFaila(Failai& failai);
void irasytiStudentuDuomenisIFaila(std::vector<Studentas>& studentuSarasas, int maksimalusNDKiekis, int studentuKiekis, Failai& failai);

#endif