#include <algorithm>
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../Studentas.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, Vector<Studentas>& studentuSarasas){              
    if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::getName));
    if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::getName));
    if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::getSurname));
    if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::getSurname));
    if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&Studentas::getFinalGrade));
    if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&Studentas::getFinalGrade));
}

void rikiuotiSuskirstytusStudentus(Vector<Studentas>& pazangiuSarasas, Vector<Studentas>& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu){
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}