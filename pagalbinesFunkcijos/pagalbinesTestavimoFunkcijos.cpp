#include "../strukturosFailai/strukturaTestavimas.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaRikiavimas.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include <chrono>

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
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
}

double apskaiciuotiBendraLaika(const TestoLaikai& laikai){ return laikai.nuskaitymas + laikai.skaiciavimas + laikai.rikiavimas + laikai.isvedimas;}

void gautiVidurki(TestoLaikai& laikai, int kiekis){
    if (kiekis <= 0) return;
    laikai.nuskaitymas /= kiekis;
    laikai.skaiciavimas /= kiekis;
    laikai.rikiavimas /= kiekis;
    laikai.isvedimas /= kiekis;
}

double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga){
    return std::chrono::duration<double>(pabaiga - startas).count();
}