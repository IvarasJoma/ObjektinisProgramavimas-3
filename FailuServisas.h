#ifndef FAILUSERVISAS_H
#define FAILUSERVISAS_H

#include <string>
#include <vector>
#include <list>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <format>
#include <cstdio>
#include <cstring>

class FailuServisas {
public:
    template <typename StudentuKonteineris>
    static StudentuKonteineris nuskaitytiStudentusIsFailo(const std::string& failas) {
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
                if (stulpelis[0] == 'N' && stulpelis[1] == 'D') ++namuDarbuKiekis;
                stulpelis = std::strtok(nullptr, " \t\r\n");
            }
            char eilute[257];
            while (std::fgets(eilute, sizeof(eilute), skaitomasFailas)) {
                const char* rodykle = eilute;
                StudentasTipas studentas;
                if (!nuskaitytiZodi(rodykle, studentas.Vardas)) continue;
                if (!nuskaitytiZodi(rodykle, studentas.Pavarde)) continue;
                if constexpr (requires { studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis); }) {
                    studentas.namuDarbuTarpiniaiRezultatai.reserve(namuDarbuKiekis);
                }
                for (std::size_t i = 0; i < namuDarbuKiekis; ++i) {
                    int laikinasPazymys = 0;
                    if (!nuskaitytiSveikaSkaiciu(rodykle, laikinasPazymys)) laikinasPazymys = 0;
                    studentas.namuDarbuTarpiniaiRezultatai.push_back(laikinasPazymys);
                }
                if (!nuskaitytiSveikaSkaiciu(rodykle, studentas.egzaminoRezultatas)) studentas.egzaminoRezultatas = 0;
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
    static void irasytiStudentusIFaila(const StudentuKonteineris& studentuSarasas, const std::string& failoPavadinimas) {
        std::ofstream isvedamasFailas("tekstiniaiFailai/" + failoPavadinimas, std::ios::binary);
        if (!isvedamasFailas) throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
        static char failoBuferis[1 << 22];
        isvedamasFailas.rdbuf()->pubsetbuf(failoBuferis, sizeof(failoBuferis));
        std::size_t ndKiekis = 0;
        if (!studentuSarasas.empty()) ndKiekis = studentuSarasas.front().namuDarbuTarpiniaiRezultatai.size();
        std::string buferis;
        buferis.reserve(1 << 22);
        std::format_to(std::back_inserter(buferis), "{:<18}{:<18}", "Vardas", "Pavardė");
        for (std::size_t i = 1; i <= ndKiekis; ++i) std::format_to(std::back_inserter(buferis), "{:<10}", "ND" + std::to_string(i));
        std::format_to(std::back_inserter(buferis), "{:<10}\n", "Egz.");
        for (const auto& studentas : studentuSarasas) {
            std::format_to(std::back_inserter(buferis), "{:<18}{:<18}", studentas.Vardas, studentas.Pavarde);
            for (const auto& pazymys : studentas.namuDarbuTarpiniaiRezultatai) {
                std::format_to(std::back_inserter(buferis), "{:<10}", pazymys);
            }
            std::format_to(std::back_inserter(buferis), "{:<10}\n", studentas.egzaminoRezultatas);
            if (buferis.size() >= (1 << 22)) {
                isvedamasFailas.write(buferis.data(), static_cast<std::streamsize>(buferis.size()));
                buferis.clear();
            }
        }
        if (!buferis.empty()) isvedamasFailas.write(buferis.data(), static_cast<std::streamsize>(buferis.size()));
        if (!isvedamasFailas) throw std::runtime_error("Nepavyko įrašyti į failą: " + failoPavadinimas);
    }

    template <typename StudentuKonteineris>
    static void irasytiSuskirstytusStudentusIFailus(
        const StudentuKonteineris& pazangiuSarasas,
        const StudentuKonteineris& silpnuSarasas
    ) {
        irasytiStudentusIFaila(pazangiuSarasas, "pazangusStudentai.txt");
        irasytiStudentusIFaila(silpnuSarasas, "silpniStudentai.txt");
    }

    static std::vector<std::filesystem::path> gautiTekstiniusFailus(const std::string& katalogas);
    static std::vector<std::string> gautiNuskaitymoMeniu(const std::string& katalogas);
    static std::vector<std::string> nuskaitytiEilutesIVektoriu(const std::string& failas);

private:
    static void praleistiTarpa(const char*& rodykle);
    static bool nuskaitytiZodi(const char*& rodykle, std::string& isvestis);
    static bool nuskaitytiSveikaSkaiciu(const char*& rodykle, int& x);
};

#endif