#include "../strukturosFailai/strukturaTestavimas.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaRikiavimas.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/SabloninesFunkcijos.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <deque>
#include <list>
#include <cassert>
#include <type_traits>
#include <gtest/gtest.h>

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
                generuotiVardaPavarde(failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
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

void vykdytiTreciajaKonteineriuTestavimoStrategijaTikSuVektoriais(){
    TestoLaikai laikai;
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
    std::string katalogas = "KonteineriuTyrimuiSkirtiFailai";
    int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(gautiNuskaitymoMeniu(katalogas));
    for (int i = 0; i < kartai; ++i) {
        std::vector<Studentas> studentuSarasas;
        std::vector<Studentas> silpnuSarasas;
        laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, katalogas);});
        laikai.skaiciavimas += ismatuotiLaika([&](){apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodas);});
        laikai.skirstymas += ismatuotiLaika([&](){skirstytiIstrinantStudentusEfektyviau(studentuSarasas, silpnuSarasas);});
        irasytiSuskirstytusStudentusIFailus(studentuSarasas, silpnuSarasas, skaiciavimoMetodas);
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
}                    

namespace {

bool teksteYra(const std::string& tekstas, const std::string& ieskoma) {
    return tekstas.find(ieskoma) != std::string::npos;
}

Studentas sukurtiTestiniStudenta() {
    Studentas s;
    s.setName("Vardas");
    s.setSurname("Pavarde");
    s.setHomeworkGrades({8, 9, 10});
    s.setExamGrade(7);
    s.setFinalGrade(s.calculateFinalGrade('v'));
    return s;
}
}

void testuotiDefaultKonstruktoriu() {
    SCOPED_TRACE("0. Default konstruktorius");

    const Studentas s;

    EXPECT_TRUE(s.getName().empty());
    EXPECT_TRUE(s.getSurname().empty());
    EXPECT_EQ(s.getExamGrade(), 0);
    EXPECT_TRUE(s.getHomeworkGrades().empty());
    EXPECT_DOUBLE_EQ(s.getFinalGrade(), 0.0);
}

void testuotiParametriniKonstruktoriu() {
    SCOPED_TRACE("1. Parametrinis konstruktorius");

    const Studentas s("Vardenis", "Pavardenis", 8, {9, 10, 8}, 8.4);

    EXPECT_EQ(s.getName(), "Vardenis");
    EXPECT_EQ(s.getSurname(), "Pavardenis");
    EXPECT_EQ(s.getExamGrade(), 8);
    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({9, 10, 8}));
    EXPECT_DOUBLE_EQ(s.getFinalGrade(), 8.4);
}

void testuotiKonstruktoriuIsEilutes() {
    SCOPED_TRACE("2. Konstruktorius iš eilutės");

    const char* eilute = "Vardas Pavardenis 10 9 8 7 6";
    const Studentas s(eilute, static_cast<std::size_t>(4));

    EXPECT_EQ(s.getName(), "Vardas");
    EXPECT_EQ(s.getSurname(), "Pavardenis");
    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({10, 9, 8, 7}));
    EXPECT_EQ(s.getExamGrade(), 6);
}

void testuotiSetteriusIrGetterius() {
    SCOPED_TRACE("3. Setteriai ir getteriai");

    Studentas s;

    s.setName("Vardas");
    s.setSurname("Pavarde");
    s.setExamGrade(7);
    s.setFinalGrade(8.5);
    s.setHomeworkGrades({8, 9, 10});

    EXPECT_EQ(s.getName(), "Vardas");
    EXPECT_EQ(s.getSurname(), "Pavarde");
    EXPECT_EQ(s.getExamGrade(), 7);
    EXPECT_DOUBLE_EQ(s.getFinalGrade(), 8.5);
    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({8, 9, 10}));
}

void testuotiNamuDarbuPazymiuValdyma() {
    SCOPED_TRACE("4. Namų darbų pažymių valdymas");

    Studentas s;

    s.reserveHomeworkGrades(5);
    EXPECT_GE(s.getHomeworkGrades().capacity(), static_cast<std::size_t>(5));

    s.addHomeworkGrade(8);
    s.addHomeworkGrade(9);
    s.addHomeworkGrade(10);

    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({8, 9, 10}));

    s.clearHomeworkGrades();

    EXPECT_TRUE(s.getHomeworkGrades().empty());
}

void testuotiGalutinioPazymioSkaiciavimaPagalVidurki() {
    SCOPED_TRACE("5. Galutinio pažymio skaičiavimas pagal vidurkį");

    Studentas s;
    s.setHomeworkGrades({8, 9, 10});
    s.setExamGrade(7);

    const double tiketinasVidurkis = 0.4 * 9.0 + 0.6 * 7.0;

    EXPECT_NEAR(s.calculateFinalGrade('v'), tiketinasVidurkis, 1e-9);
}

void testuotiCopyKonstruktoriu() {
    SCOPED_TRACE("6. Copy konstruktorius");

    Studentas originalas = sukurtiTestiniStudenta();
    Studentas kopija(originalas);

    EXPECT_EQ(kopija.getName(), originalas.getName());
    EXPECT_EQ(kopija.getSurname(), originalas.getSurname());
    EXPECT_EQ(kopija.getExamGrade(), originalas.getExamGrade());
    EXPECT_EQ(kopija.getHomeworkGrades(), originalas.getHomeworkGrades());
    EXPECT_DOUBLE_EQ(kopija.getFinalGrade(), originalas.getFinalGrade());

    originalas.setName("Kitas");
    originalas.addHomeworkGrade(1);

    EXPECT_EQ(kopija.getName(), "Vardas");
    EXPECT_EQ(kopija.getHomeworkGrades(), std::vector<int>({8, 9, 10}));
}

void testuotiCopyPriskyrimoOperatoriu() {
    SCOPED_TRACE("7. Copy priskyrimo operatorius");

    Studentas originalas = sukurtiTestiniStudenta();
    Studentas priskirtas;

    priskirtas = originalas;

    EXPECT_EQ(priskirtas.getName(), originalas.getName());
    EXPECT_EQ(priskirtas.getSurname(), originalas.getSurname());
    EXPECT_EQ(priskirtas.getExamGrade(), originalas.getExamGrade());
    EXPECT_EQ(priskirtas.getHomeworkGrades(), originalas.getHomeworkGrades());
    EXPECT_DOUBLE_EQ(priskirtas.getFinalGrade(), originalas.getFinalGrade());

    originalas.setSurname("KitaPavarde");
    originalas.clearHomeworkGrades();

    EXPECT_EQ(priskirtas.getSurname(), "Pavarde");
    EXPECT_EQ(priskirtas.getHomeworkGrades(), std::vector<int>({8, 9, 10}));
}

void testuotiSelfCopyAssignment() {
    SCOPED_TRACE("8. Self copy assignment");

    Studentas s = sukurtiTestiniStudenta();

    Studentas& self = s;
    s = self;

    EXPECT_EQ(s.getName(), "Vardas");
    EXPECT_EQ(s.getSurname(), "Pavarde");
    EXPECT_EQ(s.getExamGrade(), 7);
    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({8, 9, 10}));
}

void testuotiMoveKonstruktoriu() {
    SCOPED_TRACE("9. Move konstruktorius - deep move check");

    Studentas laikinas("Pavardenis", "Vardenis", 9, {10, 9, 8}, 7.5);

    const int* pradinisNdBuferis = laikinas.getHomeworkGrades().data();
    const std::size_t pradinisNdKiekis = laikinas.getHomeworkGrades().size();
    const std::size_t pradineNdTalpa = laikinas.getHomeworkGrades().capacity();

    ASSERT_NE(pradinisNdBuferis, nullptr);
    EXPECT_EQ(pradinisNdKiekis, static_cast<std::size_t>(3));
    EXPECT_GE(pradineNdTalpa, pradinisNdKiekis);

    Studentas perkeltas(std::move(laikinas));

    EXPECT_EQ(perkeltas.getName(), "Pavardenis");
    EXPECT_EQ(perkeltas.getSurname(), "Vardenis");
    EXPECT_EQ(perkeltas.getExamGrade(), 9);
    EXPECT_EQ(perkeltas.getHomeworkGrades(), std::vector<int>({10, 9, 8}));
    EXPECT_DOUBLE_EQ(perkeltas.getFinalGrade(), 7.5);
    EXPECT_EQ(perkeltas.getHomeworkGrades().size(), pradinisNdKiekis);
    EXPECT_GE(perkeltas.getHomeworkGrades().capacity(), pradinisNdKiekis);
    EXPECT_EQ(perkeltas.getHomeworkGrades().data(), pradinisNdBuferis);
    EXPECT_TRUE(laikinas.getName().empty());
    EXPECT_TRUE(laikinas.getSurname().empty());
    EXPECT_EQ(laikinas.getExamGrade(), 0);
    EXPECT_TRUE(laikinas.getHomeworkGrades().empty());
    EXPECT_DOUBLE_EQ(laikinas.getFinalGrade(), 0.0);
}

void testuotiMovePriskyrimoOperatoriu() {
    SCOPED_TRACE("10. Move priskyrimo operatorius");

    Studentas saltinis("Pavardenis", "Vardenis", 9, {10, 9, 8}, 7.5);
    Studentas tikslas("Senas", "Studentas", 1, {1, 2, 3, 4, 5}, 1.0);

    const int* saltinioNdBuferis = saltinis.getHomeworkGrades().data();
    const std::size_t saltinioNdKiekis = saltinis.getHomeworkGrades().size();
    const int* senasTiksloNdBuferis = tikslas.getHomeworkGrades().data();

    ASSERT_NE(saltinioNdBuferis, nullptr);
    ASSERT_NE(senasTiksloNdBuferis, nullptr);

    tikslas = std::move(saltinis);

    EXPECT_EQ(tikslas.getName(), "Pavardenis");
    EXPECT_EQ(tikslas.getSurname(), "Vardenis");
    EXPECT_EQ(tikslas.getExamGrade(), 9);
    EXPECT_EQ(tikslas.getHomeworkGrades(), std::vector<int>({10, 9, 8}));
    EXPECT_DOUBLE_EQ(tikslas.getFinalGrade(), 7.5);

    EXPECT_EQ(tikslas.getHomeworkGrades().size(), saltinioNdKiekis);
    EXPECT_EQ(tikslas.getHomeworkGrades().data(), saltinioNdBuferis);
    EXPECT_NE(tikslas.getHomeworkGrades().data(), senasTiksloNdBuferis);
    EXPECT_TRUE(saltinis.getName().empty());
    EXPECT_TRUE(saltinis.getSurname().empty());
    EXPECT_EQ(saltinis.getExamGrade(), 0);
    EXPECT_TRUE(saltinis.getHomeworkGrades().empty());
    EXPECT_DOUBLE_EQ(saltinis.getFinalGrade(), 0.0);
}

void testuotiIsvestiesOperatoriu() {
    SCOPED_TRACE("11. operator<<");

    const Studentas s = sukurtiTestiniStudenta();
    std::ostringstream out;

    out << s;

    const std::string tekstas = out.str();

    EXPECT_FALSE(tekstas.empty());
    EXPECT_TRUE(teksteYra(tekstas, "Vardas"));
    EXPECT_TRUE(teksteYra(tekstas, "Pavarde"));
}

void testuotiIvestiesOperatoriu() {
    SCOPED_TRACE("12. operator>>");

    std::istringstream in("Vardyte Pavardyte 4 10 9 8 7 6");
    Studentas s;

    in >> s;

    ASSERT_FALSE(in.fail());
    EXPECT_EQ(s.getName(), "Vardyte");
    EXPECT_EQ(s.getSurname(), "Pavardyte");
    EXPECT_EQ(s.getHomeworkGrades(), std::vector<int>({10, 9, 8, 7}));
    EXPECT_EQ(s.getExamGrade(), 6);
}

void testuotiStudentasLenteleiIsvestiesOperatoriu() {
    SCOPED_TRACE("13. StudentasLentelei operator<<");

    const Studentas s = sukurtiTestiniStudenta();
    const StudentasLentelei eilute{s};
    std::ostringstream out;

    out << eilute;

    const std::string tekstas = out.str();

    EXPECT_FALSE(tekstas.empty());
    EXPECT_TRUE(teksteYra(tekstas, "Vardas"));
    EXPECT_TRUE(teksteYra(tekstas, "Pavarde"));
}

void testuotiPaveldimumoStruktura() {
    SCOPED_TRACE("14. Paveldimumo struktūra");

    EXPECT_TRUE(std::is_abstract<Zmogus>::value);
    EXPECT_TRUE((std::is_base_of<Zmogus, Studentas>::value));
    EXPECT_TRUE(std::has_virtual_destructor<Zmogus>::value);
}

void testuotiDestruktoriu() {
    SCOPED_TRACE("15. Destruktorius");

    std::ostringstream sugautaIsvestis;
    std::streambuf* senasCoutBuferis = std::cout.rdbuf(sugautaIsvestis.rdbuf());

    Studentas::arSpausdintiDestruktoriu = true;

    {
        Studentas s;
        s.setName("Destruktorius");
        s.setSurname("Veikiantis");
        s.addHomeworkGrade(10);
        s.setExamGrade(9);
    }

    Studentas::arSpausdintiDestruktoriu = false;
    std::cout.rdbuf(senasCoutBuferis);

    const std::string tekstas = sugautaIsvestis.str();

    EXPECT_FALSE(tekstas.empty());

    EXPECT_TRUE(
        teksteYra(tekstas, "[DTOR]") ||
        teksteYra(tekstas, "Destruktorius") ||
        teksteYra(tekstas, "destruktorius") ||
        teksteYra(tekstas, "destrukt")
    );
}

TEST(StudentasGoogleTest, DefaultKonstruktorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiDefaultKonstruktoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, ParametrinisKonstruktorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiParametriniKonstruktoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, KonstruktoriusIsEilutes) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiKonstruktoriuIsEilutes();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, SetteriaiIrGetteriai) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiSetteriusIrGetterius();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, NamuDarbuPazymiuValdymas) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiNamuDarbuPazymiuValdyma();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, GalutinioPazymioSkaiciavimasPagalVidurki) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiGalutinioPazymioSkaiciavimaPagalVidurki();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, CopyKonstruktorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiCopyKonstruktoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, CopyPriskyrimoOperatorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiCopyPriskyrimoOperatoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, SelfCopyAssignment) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiSelfCopyAssignment();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, MoveKonstruktorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiMoveKonstruktoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, MovePriskyrimoOperatorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiMovePriskyrimoOperatoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, IsvestiesOperatorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiIsvestiesOperatoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, IvestiesOperatorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiIvestiesOperatoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, StudentasLenteleiIsvestiesOperatorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiStudentasLenteleiIsvestiesOperatoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, PaveldimumoStruktura) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiPaveldimumoStruktura();
    Studentas::arSpausdintiDestruktoriu = false;
}

TEST(StudentasGoogleTest, Destruktorius) {
    Studentas::arSpausdintiDestruktoriu = false;
    testuotiDestruktoriu();
    Studentas::arSpausdintiDestruktoriu = false;
}