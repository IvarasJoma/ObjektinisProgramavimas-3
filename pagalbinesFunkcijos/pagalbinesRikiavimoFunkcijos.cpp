#include <algorithm>
#include "../strukturosFailai/strukturaSkaiciavimai.h"

void rikiuotiStudentus(int pasirinkimasRikiavimo, int pasirinkimasNuskaitymo, std::vector<StudentasVektorius>& studentuSarasas){              
    if (pasirinkimasRikiavimo == 1 && pasirinkimasNuskaitymo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::Vardas));
    if (pasirinkimasRikiavimo == 2 && pasirinkimasNuskaitymo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::Vardas));
    if (pasirinkimasRikiavimo == 3 && pasirinkimasNuskaitymo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::Pavarde));
    if (pasirinkimasRikiavimo == 4 && pasirinkimasNuskaitymo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::Pavarde));
    if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatas));
    if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatas));
}