#ifndef STRUKTURADARBASSUFAILAIS_H
#define STRUKTURADARBASSUFAILAIS_H

#include <vector>
#include <filesystem>
#include "../strukturosFailai/VektoriuStudentoStruktura.h"

struct Failai;

std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);
std::vector<StudentasVektorius> nuskaitytiStudentuDuomenisIsFailo(const std::string& failas);
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas);
void vykdytiNuskaitymaIsFailo();
void irasytiDuomenis(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiStudentuDuomenisIFaila(const std::vector<StudentasVektorius>& studentuSarasas, int maksimalusNDKiekis, std::string failoPavadinimas);
void vykdytiSkirstymaIFailus(std::vector<StudentasVektorius>& studentuSarasas);
void irasytiSuskirstytusStudentusIFailus(const std::vector<StudentasVektorius>& pazangiuSarasas, const std::vector<StudentasVektorius>& silpnuSarasas);
std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);

#endif