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
    }
    gautiVidurki(laikai, kartai);
    spausdintiVidurkius(laikai);
}                    


bool spausdintiTestoRezultata(const std::string& pavadinimas, bool salyga) {
    std::cout << (salyga ? "[OK]   " : "[FAIL] ") << pavadinimas << '\n';
    return salyga;
}

void testuotiStudenta() {
    std::cout << "========================================\n";
    std::cout << "Pradedami Studentas klases testai\n";
    std::cout << "========================================\n\n";
    int kiekPraejo = 0;
    int kiekViso = 0;
    auto testas = [&](const std::string& pavadinimas, bool salyga) {
        ++kiekViso;
        if (spausdintiTestoRezultata(pavadinimas, salyga)) ++kiekPraejo;
    };
    std::cout << "0. Testuojami konstruktoriai\n";
    Studentas numatytasis;
    std::cout << "   Default konstruktorius sukure objekta.\n";
    testas("default konstruktorius vardas tuscias", numatytasis.getName().empty());
    testas("default konstruktorius pavarde tuscia", numatytasis.getSurname().empty());
    testas("default konstruktorius egzaminas = 0", numatytasis.getExamGrade() == 0);
    testas("default konstruktorius nd tuscias", numatytasis.getHomeworkGrades().empty());
    testas("default konstruktorius galutinis = 0", numatytasis.getFinalGrade() == 0.0);
    Studentas parametrinis("Vardenis", "Pavardenis", 8, {9, 10, 8}, 8.4);
    std::cout << "   Parametrinis konstruktorius sukure: " << parametrinis.getName() << ' ' << parametrinis.getSurname() << '\n';
    testas("parametrinis konstruktorius vardas", parametrinis.getName() == "Vardenis");
    testas("parametrinis konstruktorius pavarde", parametrinis.getSurname() == "Pavardenis");
    testas("parametrinis konstruktorius egzaminas", parametrinis.getExamGrade() == 8);
    testas("parametrinis konstruktorius nd kiekis", parametrinis.getHomeworkGrades().size() == 3);
    testas("parametrinis konstruktorius galutinis", parametrinis.getFinalGrade() == 8.4);
    const char* eilute = "Vardas Pavardenis 10 9 8 7 6";
    Studentas isEilutes(eilute, static_cast<std::size_t>(4));
    std::cout << "   Konstruktorius is eilutes sukure: " << isEilutes.getName() << ' ' << isEilutes.getSurname() << '\n';
    testas("eilutes konstruktorius vardas", isEilutes.getName() == "Vardas");
    testas("eilutes konstruktorius pavarde", isEilutes.getSurname() == "Pavardenis");
    testas("eilutes konstruktorius nd kiekis", isEilutes.getHomeworkGrades().size() == 4);
    testas("eilutes konstruktorius pirmas nd", !isEilutes.getHomeworkGrades().empty() && isEilutes.getHomeworkGrades()[0] == 10);
    testas("eilutes konstruktorius egzaminas", isEilutes.getExamGrade() == 6);
    std::cout << "\n   Rankinio konstruktoriaus testas\n";
    std::cout << "   Dabar bus kvieciamas Studentas(bool generuotiPazymius, int ndKiekis).\n";
    std::cout << "   Iveskite duomenis pagal pateikiamus klausimus.\n";
    Studentas interaktyvus(false, 2);
    std::cout << "   Rankiniu budu sukurtas studentas:\n";
    std::cout << "   Vardas: " << interaktyvus.getName() << '\n';
    std::cout << "   Pavarde: " << interaktyvus.getSurname() << '\n';
    std::cout << "   Egzaminas: " << interaktyvus.getExamGrade() << '\n';
    std::cout << "   ND kiekis: " << interaktyvus.getHomeworkGrades().size() << '\n';
    testas("rankinio konstruktoriaus vardas netuscias", !interaktyvus.getName().empty());
    testas("rankinio konstruktoriaus pavarde netuscia", !interaktyvus.getSurname().empty());
    testas("rankinio konstruktoriaus nd kiekis = 2", interaktyvus.getHomeworkGrades().size() == 2);
    testas("rankinio konstruktoriaus egzaminas intervale [1,10]",
           interaktyvus.getExamGrade() >= 1 && interaktyvus.getExamGrade() <= 10);
    std::cout << "\n1. Kuriamas pradinis objektas\n";
    Studentas s1;
    s1.setName("Vardas");
    s1.setSurname("Pavarde");
    s1.addHomeworkGrade(8);
    s1.addHomeworkGrade(9);
    s1.addHomeworkGrade(10);
    s1.setExamGrade(7);
    s1.setFinalGrade(s1.calculateFinalGrade('v'));
    std::cout << "   Vardas: " << s1.getName() << '\n';
    std::cout << "   Pavarde: " << s1.getSurname() << '\n';
    std::cout << "   Egzaminas: " << s1.getExamGrade() << '\n';
    std::cout << "   ND kiekis: " << s1.getHomeworkGrades().size() << '\n';
    std::cout << "   Galutinis: " << s1.getFinalGrade() << "\n\n";
    testas("set/get vardas", s1.getName() == "Vardas");
    testas("set/get pavarde", s1.getSurname() == "Pavarde");
    testas("set/get egzamino pazymys", s1.getExamGrade() == 7);
    testas("namu darbu kiekis", s1.getHomeworkGrades().size() == 3);
    const double tiketinasVidurkis = 0.4 * 9.0 + 0.6 * 7.0;
    testas("galutinio balo skaiciavimas (vidurkis)", s1.getFinalGrade() == tiketinasVidurkis);
    std::cout << "\n2. Testuojamas copy konstruktorius\n";
    Studentas s2(s1);
    std::cout << "   Nukopijuotas studentas: " << s2.getName() << ' ' << s2.getSurname() << "\n\n";
    testas("copy konstruktorius vardas", s2.getName() == s1.getName());
    testas("copy konstruktorius  pavarde", s2.getSurname() == s1.getSurname());
    testas("copy konstruktorius  egzaminas", s2.getExamGrade() == s1.getExamGrade());
    testas("copy konstruktorius nd", s2.getHomeworkGrades() == s1.getHomeworkGrades());
    std::cout << "\n3. Testuojamas copy priskyrimo operatorius\n";
    Studentas s3;
    s3 = s1;
    std::cout << "   Priskirtas studentas: " << s3.getName() << ' ' << s3.getSurname() << "\n\n";
    testas("copy priskyrimo operatorius vardas", s3.getName() == s1.getName());
    testas("copy priskyrimo operatorius pavarde", s3.getSurname() == s1.getSurname());
    testas("copy priskyrimo operatorius egzaminas", s3.getExamGrade() == s1.getExamGrade());
    testas("copy priskyrimo operatorius nd", s3.getHomeworkGrades() == s1.getHomeworkGrades());
    std::cout << "\n4. Testuojamas move konstruktorius\n";
    Studentas laikinas("Pavardenis", "Vardenis", 9, {10, 9, 8}, 0.0);
    Studentas s4(std::move(laikinas));
    std::cout << "   Perkeltas studentas: " << s4.getName() << ' ' << s4.getSurname() << "\n\n";
    testas("move konstruktorius vardas", s4.getName() == "Pavardenis");
    testas("move konstruktorius pavarde", s4.getSurname() == "Vardenis");
    testas("move konstruktorius egzaminas", s4.getExamGrade() == 9);
    testas("move konstruktorius nd kiekis", s4.getHomeworkGrades().size() == 3);
    std::cout << "\n5. Testuojamas move priskyrimo operatorius\n";
    Studentas s5;
    s5 = std::move(s4);
    std::cout << "   Perimtas studentas: " << s5.getName() << ' ' << s5.getSurname() << "\n\n";
    testas("move priskyrimo operatorius vardas", s5.getName() == "Pavardenis");
    testas("move priskyrimo operatorius pavarde", s5.getSurname() == "Vardenis");
    testas("move priskyrimo operatorius egzaminas", s5.getExamGrade() == 9);
    testas("move priskyrimo operatorius nd kiekis", s5.getHomeworkGrades().size() == 3);
    std::cout << "\n6. Testuojamas operator<<\n";
    std::ostringstream out;
    out << s1;
    std::string tekstas = out.str();
    std::cout << "   Sugeneruota isvestis: " << tekstas << "\n\n";
    testas("operator<< sugeneruoja netuscia teksta", !tekstas.empty());
    std::cout << "\n7. Testuojamas operator>>\n";
    std::istringstream in("Vardyte Pavardyte 4 10 9 8 7 6");
    Studentas s6;
    in >> s6;
    std::cout << "   Nuskaitytas studentas:\n";
    std::cout << "   Vardas: " << s6.getName() << '\n';
    std::cout << "   Pavarde: " << s6.getSurname() << '\n';
    std::cout << "   Egzaminas: " << s6.getExamGrade() << '\n';
    std::cout << "   ND kiekis: " << s6.getHomeworkGrades().size() << "\n\n";
    testas("operator>> vardas", s6.getName() == "Vardyte");
    testas("operator>> pavarde", s6.getSurname() == "Pavardyte");
    testas("operator>> nd kiekis", s6.getHomeworkGrades().size() == 4);
    testas("operator>> egzamino pazymys", s6.getExamGrade() == 6);
    std::cout << "\n8. Testuojamas destruktorius\n";
    std::cout << "   Kuriamas lokalus objektas...\n";
    Studentas::arSpausdintiDestruktoriu = true;
    {
        Studentas s7;
        s7.setName("Destruktorius");
        s7.setSurname("Veikiantis");
        s7.addHomeworkGrade(10);
        s7.setExamGrade(9);
        std::cout << "   Objektas sukurtas: " << s7.getName() << ' ' << s7.getSurname() << '\n';
        std::cout << "   Iseinant is sio bloko turetu buti iskviestas destruktorius.\n";
    }
    Studentas::arSpausdintiDestruktoriu = false;
    std::cout << "   Jei auksciau pasirode [DTOR] eilute, destruktorius veikia.\n";
    testas("destruktorius vizualiai iskviestas", true);
    std::cout << "9. Testuojama paveldimumo struktura\n";
    bool abstrakti = std::is_abstract<Zmogus>::value;
    bool derived   = std::is_base_of<Zmogus, Studentas>::value;
    std::cout << "   Zmogus abstrakti klase: " << (abstrakti ? "TAIP" : "NE") << '\n';
    std::cout << "   Studentas isvestine klase: " << (derived ? "TAIP" : "NE") << "\n\n";
    testas("Zmogus yra abstrakti klase", abstrakti);
    testas("Studentas paveldi is Zmogus", derived);
    std::cout << "\n========================================\n";
    std::cout << "Testu santrauka: " << kiekPraejo << " / " << kiekViso << " praejo\n";
    std::cout << (kiekPraejo == kiekViso ? "Visi Studentas klases testai sekmingi.\n"
                                         : "Dalis testu nepraejo.\n");
    std::cout << "========================================\n";
}
