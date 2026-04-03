#include "../strukturosFailai/strukturaTestavimas.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaRikiavimas.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/SabloninesFunkcijos.h"
#include "../strukturosFailai/strukturaStudentas.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <deque>
#include <list>

void vykdytiIvedimoTestavima(){
    std::vector<Studentas> studentuSarasas;
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    std::string katalogas = "tekstiniaiFailai";
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU);
    int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(ISVEDIMO_MENIU);
    for (int i = 0; i < kartai; ++i){
        studentuSarasas.clear();
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.isvedimas += ismatuotiLaika([&](){isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
}

void vykdytiDuomenuApdorojimoTestavima(){
    if (std::filesystem::exists("ApdorojimoTyrimuiSkirtiFailai/PazangusStudentai.txt") && std::filesystem::exists("ApdorojimoTyrimuiSkirtiFailai/SilpniStudentai.txt")) {
        std::filesystem::remove("ApdorojimoTyrimuiSkirtiFailai/PazangusStudentai.txt");
        std::filesystem::remove("ApdorojimoTyrimuiSkirtiFailai/SilpniStudentai.txt");
    }
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu("ApdorojimoTyrimuiSkirtiFailai"));
    int pasirinkimasRikiavimoPazangiu = 0;
    int pasirinkimasRikiavimoSilpnu = 0;
    parinktiRikiavimoBudus(pasirinkimasRikiavimoPazangiu, pasirinkimasRikiavimoSilpnu);
    for (int i = 0; i < kartai; ++i) {
        std::vector<Studentas> studentuSarasas;
        std::vector<Studentas> pazangiuSarasas;
        std::vector<Studentas> silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, "ApdorojimoTyrimuiSkirtiFailai");});
        laikai.skaiciavimas += ismatuotiLaika([&](){
            apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);
            suskirstytiStudentus(studentuSarasas, pazangiuSarasas, silpnuSarasas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiSuskirstytusStudentus(pazangiuSarasas, silpnuSarasas, pasirinkimasRikiavimoPazangiu, pasirinkimasRikiavimoSilpnu);});
        laikai.isvedimas += ismatuotiLaika([&](){irasytiSuskirstytusStudentusIFailus(pazangiuSarasas, silpnuSarasas, skaiciavimoMetodas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
}

void vykdytiIsvedimoTestavima(Failai& failai){
    TestoLaikai laikai;
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
    int pasirinkimasIrasymo = nuskaitytiMeniuPasirinkima(ISVEDIMO_I_FAILA_MENIU);
    int studentuKiekis = 0;
    if (pasirinkimasIrasymo == 1) studentuKiekis = 1000;
    if (pasirinkimasIrasymo == 2) studentuKiekis = 10000;
    if (pasirinkimasIrasymo == 3) studentuKiekis = 100000;
    if (pasirinkimasIrasymo == 4) studentuKiekis = 1000000;
    if (pasirinkimasIrasymo == 5) studentuKiekis = 10000000;
    std::string failoPavadinimas = "studentai" + std::to_string(studentuKiekis) + ".txt";
    std::string pilnasKelias = "FailuKurimoTyrimuiSkirtiFailai/" + failoPavadinimas;
    for (int i = 0; i < kartai; ++i){
        laikai.isvedimas += ismatuotiLaika([&]() {
            std::ofstream failas(pilnasKelias);
            if (!failas) {
                throw std::runtime_error("Nepavyko sukurti failo: " + failoPavadinimas);
            }
            failas << std::format("{:<18}{:<18}", "Vardas", "Pavardė");
            for (int j = 1; j <= maksimalusNDKiekis; ++j) {
                failas << std::format("{:<10}", "ND" + std::to_string(j));
            }
            failas << std::format("{:<10}\n", "Egz.");
            for (int j = 0; j < studentuKiekis; ++j) {
                Studentas studentas;
                generuotiVardaPavarde(studentas, failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
                generuotiRezultatus(studentas, maksimalusNDKiekis);
                failas << std::format("{:<18}{:<18}", studentas.getName(), studentas.getSurname());
                for (const auto pazymys : studentas.getHomeworkGrades()) failas << std::format("{:<10}", pazymys);
                failas << std::format("{:<10}\n", studentas.getExamGrade());
            }
            if (!failas) {
                throw std::runtime_error("Nepavyko įrašyti į failą: " + failoPavadinimas);
            }
        });
    }
    gautiVidurki(laikai, kartai);
    std::cout << "Vidutinis failo kūrimo ir uždarymo laikas: " << laikai.isvedimas << " s\n";
    if (std::filesystem::exists(pilnasKelias)) {
        std::filesystem::remove(pilnasKelias);
    }
}

double apskaiciuotiBendraLaika(const TestoLaikai& laikai){ return laikai.nuskaitymas + laikai.skaiciavimas + laikai.rikiavimas + laikai.isvedimas + laikai.skirstymas;}

void gautiVidurki(TestoLaikai& laikai, int kiekis){
    if (kiekis <= 0) return;
    laikai.nuskaitymas /= kiekis;
    laikai.skaiciavimas /= kiekis;
    laikai.rikiavimas /= kiekis;
    laikai.skirstymas /= kiekis;
    laikai.isvedimas /= kiekis;
}

double apskaiciuotiLaika(std::chrono::steady_clock::time_point startas, std::chrono::steady_clock::time_point pabaiga){
    return std::chrono::duration<double>(pabaiga - startas).count();
}

void vykdytiPirmajaKonteineriuTestavimoStrategija(){
    using VectorKonteineris = std::vector<Studentas>;
    using ListKonteineris = std::list<Studentas>;
    using DequeKonteineris = std::deque<Studentas>;
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    std::string katalogas = "KonteineriuTyrimuiSkirtiFailai";
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU_TIK_DIDEJANCIAI);
    std::cout << "VEKTORIU TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        VectorKonteineris studentuSarasas;
        VectorKonteineris pazangiuSarasas;
        VectorKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){perkeltiStudentus(studentuSarasas, pazangiuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "LIST TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        ListKonteineris studentuSarasas;
        ListKonteineris pazangiuSarasas;
        ListKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){perkeltiStudentus(studentuSarasas, pazangiuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "DEQUE TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        DequeKonteineris studentuSarasas;
        DequeKonteineris pazangiuSarasas;
        DequeKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){perkeltiStudentus(studentuSarasas, pazangiuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
};

void vykdytiAntrajaKonteineriuTestavimoStrategija(){
    using VectorKonteineris = std::vector<Studentas>;
    using ListKonteineris = std::list<Studentas>;
    using DequeKonteineris = std::deque<Studentas>;
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    std::string katalogas = "KonteineriuTyrimuiSkirtiFailai";
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU_TIK_DIDEJANCIAI);
    std::cout << "VEKTORIU TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        VectorKonteineris studentuSarasas;
        VectorKonteineris pazangiuSarasas;
        VectorKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentus(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "LIST TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        ListKonteineris studentuSarasas;
        ListKonteineris pazangiuSarasas;
        ListKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentus(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "DEQUE TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        DequeKonteineris studentuSarasas;
        DequeKonteineris pazangiuSarasas;
        DequeKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentus(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
};

void vykdytiTreciajaKonteineriuTestavimoStrategija(){
    using VectorKonteineris = std::vector<Studentas>;
    using ListKonteineris = std::list<Studentas>;
    using DequeKonteineris = std::deque<Studentas>;
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    std::string katalogas = "KonteineriuTyrimuiSkirtiFailai";
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU_TIK_DIDEJANCIAI);
    std::cout << "VEKTORIU TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        VectorKonteineris studentuSarasas;
        VectorKonteineris pazangiuSarasas;
        VectorKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentusEfektyviau(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "LIST TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        ListKonteineris studentuSarasas;
        ListKonteineris pazangiuSarasas;
        ListKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentusEfektyviau(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
    laikai = TestoLaikai{};
    std::cout << "DEQUE TESTAS:\n";
    for (int i = 0; i < kartai; ++i) {
        DequeKonteineris studentuSarasas;
        DequeKonteineris pazangiuSarasas;
        DequeKonteineris silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenisGeneric(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.rikiavimas += ismatuotiLaika([&](){rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentusEfektyviau(studentuSarasas, silpnuSarasas);});
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
};