#include <string>

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
void apskaiciuotiGalutiniPazymi(T& duomenys, char metodas) {
    if constexpr (requires { duomenys.begin(); duomenys.end(); }) for (auto& studentas : duomenys) apskaiciuotiGalutiniPazymi(studentas, metodas);
    else {
        const double namuDarbuRezultatas = (metodas == 'V' || metodas == 'v') ? skaiciuotiNDVidurki(duomenys.namuDarbuTarpiniaiRezultatai) : skaiciuotiNDMediana(duomenys.namuDarbuTarpiniaiRezultatai);
        duomenys.galutinisRezultatas = 0.4 * namuDarbuRezultatas + 0.6 * duomenys.egzaminoRezultatas;
    }
}

template <typename SaltinioKonteineris, typename RezultatoKonteineris>
void suskirstytiStudentus(SaltinioKonteineris& studentai, RezultatoKonteineris& pazangusStudentai, RezultatoKonteineris& silpniStudentai) {
    pazangusStudentai.clear();
    silpniStudentai.clear();
    if constexpr (requires { pazangusStudentai.reserve(studentai.size() / 2); }) pazangusStudentai.reserve(studentai.size() / 2);
    if constexpr (requires { silpniStudentai.reserve(studentai.size() / 2); }) silpniStudentai.reserve(studentai.size() / 2);
    for (auto& studentas : studentai) {
        if (studentas.galutinisRezultatas < 5) silpniStudentai.push_back(std::move(studentas));
        else pazangusStudentai.push_back(std::move(studentas));
    }
}