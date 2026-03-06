#include "strukturaLaikoMatavimas.h"
#include "Failai.h"
#include "strukturaMeniu.h"
#include "strukturaIvestisIsvestis.h"
#include "strukturaRikiavimas.h"
#include "strukturaSkaiciavimai.h"

void vykdytiTestavima(Failai& failai) {
    std::vector<StudentasVektorius> studentai;
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(NUSKAITYMO_MENIU);
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU);
    int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(ISVEDIMO_MENIU);
    for (int i = 0; i < kartai; ++i) {
        studentai.clear();
        laikai.nuskaitymas += ismatuotiLaika([&]() {nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentai, failai);});
        laikai.skaiciavimas += ismatuotiLaika([&]() {apskaiciuotiGalutiniusPazymius(studentai, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&]() {rikiuotiStudentus(pasirinkimasRikiavimo, pasirinkimasNuskaitymo, studentai);});
        laikai.isvedimas += ismatuotiLaika([&]() {isvestiStudentus(pasirinkimasIsvedimo, studentai, skaiciavimoMetodas);});
    }
    laikai.padalintiIs(kartai);
    spausdintiVidurkius(laikai);
}