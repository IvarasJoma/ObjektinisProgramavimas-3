#include <algorithm>
#include "../strukturosFailai/strukturaSkaiciavimai.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, std::vector<Studentas>& studentuSarasas){              
    if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::name_));
    if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::name_));
    if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::surname_));
    if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::surname_));
    if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::calculateFinalGrade()));
    if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::calculateFinalGrade()));
}

void rikiuotiSuskirstytusStudentus(std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu){
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}