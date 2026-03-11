#ifndef STRUKTURARIKIAVIMAS_H
#define STRUKTURARIKIAVIMAS_H

#include <vector>
#include "../strukturosFailai/strukturaStudentas.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, std::vector<StudentasVektorius>& studentuSarasas);
void rikiuotiSuskirstytusStudentus(std::vector<StudentasVektorius>& pazangiuSarasas, std::vector<StudentasVektorius>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu);

#endif