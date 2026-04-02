#include <algorithm>
#include "../strukturosFailai/strukturaSkaiciavimai.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, std::vector<Studentas>& studentuSarasas){              
    if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::Vardas));
    if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::Vardas));
    if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::Pavarde));
    if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::Pavarde));
    if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::galutinisRezultatas));
    if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::galutinisRezultatas));
}

void rikiuotiSuskirstytusStudentus(std::vector<Studentas>& pazangiuSarasas, std::vector<Studentas>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu){
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}