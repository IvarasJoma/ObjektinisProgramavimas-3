#ifndef STRUKTURARIKIAVIMAS_H
#define STRUKTURARIKIAVIMAS_H

#include <vector>
#include "../Studentas.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, std::vector<Studentas>& studentuSarasas);
void rikiuotiSuskirstytusStudentus(std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu);

#endif