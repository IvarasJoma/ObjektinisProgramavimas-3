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
    using StudentasTipas = typename StudentuKonteineris::value_type;
    StudentuKonteineris studentuSarasas;
    FILE* skaitomasFailas = std::fopen(failas.c_str(), "r");
    if (!skaitomasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failas);
    try {
        static char ivestiesBuferis[1 << 20];
        std::setvbuf(skaitomasFailas, ivestiesBuferis, _IOFBF, sizeof(ivestiesBuferis));
        char aprasas[257];
        if (!std::fgets(aprasas, sizeof(aprasas), skaitomasFailas)) {
            std::fclose(skaitomasFailas);
            return studentuSarasas;
        }
        std::size_t namuDarbuKiekis = 0;
        char laikinaEilute[257];
        std::strncpy(laikinaEilute, aprasas, sizeof(laikinaEilute));
        laikinaEilute[sizeof(laikinaEilute) - 1] = '\0';
        char* stulpelis = std::strtok(laikinaEilute, " \t\r\n");
        while (stulpelis) {
            if (stulpelis[0] == 'N' && stulpelis[1] == 'D') namuDarbuKiekis++;
            stulpelis = std::strtok(nullptr, " \t\r\n");
        }
        char eilute[257];
        while (std::fgets(eilute, sizeof(eilute), skaitomasFailas)) {
            const char* rodykle = eilute;
            StudentasTipas studentas;
            if (!nuskaitytiZodiIsFailo(rodykle, studentas.Vardas)) continue;
            if (!nuskaitytiZodiIsFailo(rodykle, studentas.Pavarde)) continue;
            if constexpr (requires { studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis); }) { // if constexpr patikrina if salyga kompliavimo metu, requires paziuri ar metodas (siuo atveju reserve) egzistuoja tokiam konteineriui
                studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis);
            }
            for (std::size_t i = 0; i < namuDarbuKiekis; ++i) {
                int laikinasPazymys;
                if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, laikinasPazymys)) laikinasPazymys = 0;
                studentas.namuDarbuTarpiniaiRezultatai.push_back(laikinasPazymys);
            }
            if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, studentas.egzaminoRezultatas)) studentas.egzaminoRezultatas = 0;
            studentuSarasas.push_back(std::move(studentas));
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
    if (pasirinkimasRikiavimo == 1) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::Vardas));
    else if (pasirinkimasRikiavimo == 2) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::Pavarde));
    else if (pasirinkimasRikiavimo == 3) rikiuoti(lygintiElementusPagalDidejanciaReiksme(&StudentasTipas::galutinisRezultatas));
}

template <typename PazymiuKonteineris>
double skaiciuotiNDVidurki(const PazymiuKonteineris& ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    const double suma = std::accumulate(ndPazymiai.begin(), ndPazymiai.end(), 0.0);
    return suma / ndPazymiai.size();
}

template <typename PazymiuKonteineris>
double skaiciuotiNDMediana(PazymiuKonteineris ndPazymiai) {
    if (ndPazymiai.empty()) return 0.0;
    if constexpr (requires { ndPazymiai.sort(); }) ndPazymiai.sort();
    else std::sort(ndPazymiai.begin(), ndPazymiai.end());
    auto vidurinisElementas = std::next(ndPazymiai.begin(), ndPazymiai.size() / 2);
    if (ndPazymiai.size() % 2) return *vidurinisElementas;
    return (*std::prev(vidurinisElementas) + *vidurinisElementas) / 2.0;
}

template <typename Studentas>
double skaiciuotiGalutiniPazymi(const Studentas& studentas, char pasirinkimas) {
    const double ndRezultatas = (pasirinkimas == 'V' || pasirinkimas == 'v') ? skaiciuotiNDVidurki(studentas.namuDarbuTarpiniaiRezultatai) : skaiciuotiNDMediana(studentas.namuDarbuTarpiniaiRezultatai);
    return 0.4 * ndRezultatas + 0.6 * studentas.egzaminoRezultatas;
}

template <typename T>
void apskaiciuotiGalutiniusPazymius(T& duomenys, char metodas) {
    for (auto& studentas : duomenys) studentas.galutinisRezultatas = skaiciuotiGalutiniPazymi(studentas, metodas);
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void perkeltiStudentus(SaltinioKonteineris& studentai, RezultatoKonteineris& pazangusStudentai, RezultatoKonteineris& silpniStudentai) {
    pazangusStudentai.clear();
    silpniStudentai.clear();
    if constexpr (requires { pazangusStudentai.reserve(studentai.size() / 2); }) pazangusStudentai.reserve(studentai.size() / 2);
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    for (auto& studentas : studentai) {
        if (studentas.galutinisRezultatas < 5) silpniStudentai.push_back(std::move(studentas));
        else pazangusStudentai.push_back(std::move(studentas));
    }
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void kopijuotiStudentus(SaltinioKonteineris& studentai, RezultatoKonteineris& pazangusStudentai, RezultatoKonteineris& silpniStudentai) {
    pazangusStudentai.clear();
    silpniStudentai.clear();
    if constexpr (requires { pazangusStudentai.reserve(studentai.size()); }) pazangusStudentai.reserve(studentai.size());
    if constexpr (requires { silpniStudentai.reserve(studentai.size()); }) silpniStudentai.reserve(studentai.size());
    for (auto& studentas : studentai) {
        if (studentas.galutinisRezultatas < 5) silpniStudentai.push_back(studentas);
        else pazangusStudentai.push_back(studentas);
    }
}

template <typename T>
struct is_std_list : std::false_type {};

template <typename T, typename Alloc>
struct is_std_list<std::list<T, Alloc>> : std::true_type {};

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void skirstytiIstrinantStudentus(SaltinioKonteineris& studentai, RezultatoKonteineris& silpniStudentai) {
    silpniStudentai.clear();
    if constexpr (requires { silpniStudentai.reserve(studentai.size()); }) silpniStudentai.reserve(studentai.size());
    auto it = studentai.begin();
    while (it != studentai.end()) {
        if (it->galutinisRezultatas < 5) {
            if constexpr (is_std_list<SaltinioKonteineris>::value && is_std_list<RezultatoKonteineris>::value) {
                auto current = it++;
                silpniStudentai.splice(silpniStudentai.end(), studentai, current);
            } else {
                silpniStudentai.push_back(std::move(*it));
                it = studentai.erase(it);
            }
        } else {
            ++it;
        }
    }
}

template <typename StudentuKonteineris>
void nuskaitytiDuomenis(int pasirinkimasNuskaitymo, StudentuKonteineris& studentuSarasas, std::string& katalogas) {
    try {
        auto failai = gautiTekstiniusFailus(katalogas);
        if (failai.empty()) throw std::runtime_error("Kataloge" + katalogas + "nerasta .txt failų.");
        if (pasirinkimasNuskaitymo < 1 || static_cast<std::size_t>(pasirinkimasNuskaitymo) > failai.size()) throw std::runtime_error("Neteisingas failo pasirinkimas.");
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
void rikiuotiSuskirstytusStudentus(StudentuKonteineris& pazangiuSarasas, StudentuKonteineris& silpnuSarasas, int pasirinkimasRikiavimoPazangiu, int pasirinkimasRikiavimoSilpnu){
    rikiuotiStudentus(pasirinkimasRikiavimoPazangiu, pazangiuSarasas);
    rikiuotiStudentus(pasirinkimasRikiavimoSilpnu, silpnuSarasas);
}

template <typename StudentuKonteineris>
void irasytiSuskirstytusStudentusIFailus(const StudentuKonteineris& pazangiuSarasas, const StudentuKonteineris& silpnuSarasas){
    irasytiStudentuDuomenisIFaila(pazangiuSarasas, "pazangusStudentai.txt");
    irasytiStudentuDuomenisIFaila(silpnuSarasas, "silpniStudentai.txt");
}

template <typename StudentuKonteineris>
void irasytiStudentuDuomenisIFaila(const StudentuKonteineris& studentuSarasas, const std::string& failoPavadinimas) {
    std::ofstream isvedamasFailas("tekstiniaiFailai/" + failoPavadinimas, std::ios::binary);
    if (!isvedamasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    static char failoBuferis[1 << 22]; // sukuriamas 4MB failo burferis
    isvedamasFailas.rdbuf()->pubsetbuf(failoBuferis, sizeof(failoBuferis)); // isakoma naudoti didesni buferi
    std::size_t ndKiekis = 0;
    if (!studentuSarasas.empty()) ndKiekis = studentuSarasas.front().namuDarbuTarpiniaiRezultatai.size();
    std::string buferis;
    buferis.reserve(1 << 22);
    std::format_to(std::back_inserter(buferis), "{:<18}{:<18}", "Vardas", "Pavardė");
    for (std::size_t i = 1; i <= ndKiekis; ++i) std::format_to(std::back_inserter(buferis), "{:<10}", "ND" + std::to_string(i));
    std::format_to(std::back_inserter(buferis), "{:<10}\n", "Egz.");
    for (const auto& studentas : studentuSarasas) {
        std::format_to(std::back_inserter(buferis), "{:<18}{:<18}", studentas.Vardas, studentas.Pavarde);
        for (const auto& pazymys : studentas.namuDarbuTarpiniaiRezultatai) std::format_to(std::back_inserter(buferis), "{:<10}", pazymys);
        std::format_to(std::back_inserter(buferis), "{:<10}\n", studentas.egzaminoRezultatas);
        if (buferis.size() >= (1 << 22)) { // jei buferis arti savo talpos
            if (!buferis.empty()) {
                isvedamasFailas.write(buferis.data(), static_cast<std::streamsize>(buferis.size())); // issiunciam info is buferio
                buferis.clear(); // isvalom buferi
            }
        }
    }
    if (!buferis.empty()) {
        isvedamasFailas.write(buferis.data(), static_cast<std::streamsize>(buferis.size())); // issiunciam info is buferio
        buferis.clear(); // isvalom buferi
    }
    if (!isvedamasFailas) {
        throw std::runtime_error("Nepavyko įrašyti į failą: " + failoPavadinimas);
    }
}

#endif