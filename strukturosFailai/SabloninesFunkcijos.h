#ifndef SABLONINESFUNKCIJOS_H
#define SABLONINESFUNKCIJOS_H

#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "../strukturosFailai/strukturaDarbasSuFailais.h"
#include <fstream>
#include <list>
#include <type_traits>
#include <utility>

template <typename StudentuKonteineris>
StudentuKonteineris nuskaitytiStudentuDuomenisIsFailo(const std::string& failas) {
    StudentuKonteineris studentuSarasas;
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    try {
        static char ivestiesBuferis[1 << 20];
        std::setvbuf(skaitomasFailas, ivestiesBuferis, _IOFBF, sizeof(ivestiesBuferis));
        char antraste[257];
        if (!std::fgets(antraste, sizeof(antraste), skaitomasFailas)) {
            std::fclose(skaitomasFailas);
            return studentuSarasas;
        }
        std::size_t namuDarbuKiekis = 0;
        char laikinaEilute[257];
        std::strncpy(laikinaEilute, antraste, sizeof(laikinaEilute));
        laikinaEilute[sizeof(laikinaEilute) - 1] = '\0';
        char* stulpelis = std::strtok(laikinaEilute, " \t\r\n");
        while (stulpelis) {
            if (stulpelis[0] == 'N' && stulpelis[1] == 'D') namuDarbuKiekis++;
            stulpelis = std::strtok(nullptr, " \t\r\n");
        }
        char eilute[1024];
        while (std::fgets(eilute, sizeof(eilute), skaitomasFailas)) {
            try {
                Studentas studentas(eilute, namuDarbuKiekis);
                studentuSarasas.push_back(std::move(studentas));
            } catch (...) {
                continue;
            }
        }
        std::fclose(skaitomasFailas);
        return studentuSarasas;
    }
    catch (const std::bad_alloc&) {
        std::fclose(skaitomasFailas);
        std::cerr << "Nepakanka atminties...\n";
        return studentuSarasas;
    }
}

template <typename StudentuKonteineris>
void rikiuotiStudentus(int pasirinkimasRikiavimo, StudentuKonteineris& studentuSarasas) {
    using StudentasTipas = typename StudentuKonteineris::value_type;
    auto rikiuoti = [&](auto comparator) {
        if constexpr (requires { studentuSarasas.sort(comparator); }) studentuSarasas.sort(comparator);
        else std::sort(studentuSarasas.begin(), studentuSarasas.end(), comparator);
    };
    if (pasirinkimasRikiavimo == 1) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getName));
    else if (pasirinkimasRikiavimo == 2) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getSurname));
    else if (pasirinkimasRikiavimo == 3) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::getFinalGrade));
}

template <typename StudentuKonteineris>
void apskaiciuotiGalutiniusPazymius(StudentuKonteineris& duomenys, char metodas) {
    for (auto& studentas : duomenys) studentas.setFinalGrade(studentas.calculateFinalGrade(metodas));
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void perkeltiStudentus(SaltinioKonteineris& studentai,
                       RezultatoKonteineris& pazangusStudentai,
                       RezultatoKonteineris& silpniStudentai) {
    pazangusStudentai.clear();
    silpniStudentai.clear();
    if constexpr (requires { pazangusStudentai.reserve(studentai.size() / 2); }) pazangusStudentai.reserve(studentai.size() / 2);
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    for (auto& studentas : studentai) {
        if (studentas.getFinalGrade() < 5.0) silpniStudentai.push_back(std::move(studentas));
        else pazangusStudentai.push_back(std::move(studentas));
    }
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void skirstytiIstrinantStudentus(SaltinioKonteineris& studentai,
                                 RezultatoKonteineris& silpniStudentai) {
    silpniStudentai.clear();
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) { return studentas.getFinalGrade() < 5.0; });
    silpniStudentai.insert(silpniStudentai.end(), std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    studentai.erase(studentai.begin(), it);
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void skirstytiIstrinantStudentusEfektyviau(SaltinioKonteineris& studentai, RezultatoKonteineris& silpniStudentai) {
    silpniStudentai.clear();
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& studentas) {
        if (studentas.getFinalGrade() < 5.0) {
            silpniStudentai.push_back(studentas);
            return true;
        }
            return false;
        });
    studentai.erase(it, studentai.end());
}

template <typename StudentuKonteineris>
void nuskaitytiDuomenisGeneric(int pasirinkimasNuskaitymo, StudentuKonteineris& studentuSarasas, std::string& katalogas) {
    try {
        auto failai = gautiTekstiniusFailus(katalogas);
        if (failai.empty()) throw std::runtime_error("Kataloge " + katalogas + " nerasta .txt failų.");
        if (pasirinkimasNuskaitymo < 1 ||
            static_cast<std::size_t>(pasirinkimasNuskaitymo) > failai.size()) {
            throw std::runtime_error("Neteisingas failo pasirinkimas.");
        }
        const std::size_t indeksas = static_cast<std::size_t>(pasirinkimasNuskaitymo - 1);
        const std::string failoKelias = failai[indeksas].string();
        studentuSarasas = nuskaitytiStudentuDuomenisIsFailo<StudentuKonteineris>(failoKelias);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida skaitant failą: " << e.what() << std::endl;
        studentuSarasas.clear();
    }
}

template <typename StudentuKonteineris>
void rikiuotiSuskirstytusStudentus(StudentuKonteineris& pazangiuSarasas, StudentuKonteineris& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu) {
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}

#endif