#include <algorithm>
#include "../strukturosFailai/strukturaSkaiciavimai.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, std::vector<StudentasVektorius>& studentuSarasas){              
    if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::Vardas));
    if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::Vardas));
    if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::Pavarde));
    if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::Pavarde));
    if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatas));
    if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatas));
}

void rikiuotiSuskirstytusStudentus(std::vector<StudentasVektorius>& pazangiuSarasas, std::vector<StudentasVektorius>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu){
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}