#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/Failai.h"
#include "../strukturosFailai/strukturaIvestis.h"
#include <random>
#include <sstream>
#include <stdexcept>
#include <utility>

int generuotiSveikaSkaiciu(int nuo, int iki){
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}

std::pair<std::string, std::string> generuotiVardaPavarde(const Vector<std::string>& vyrVardai, const Vector<std::string>& vyrPavardes, const Vector<std::string>& motVardai, const Vector<std::string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()) return {"Vardenis", "Pavardenis"};
    const int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0) {
        const auto vardoIndeksas = static_cast<Vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<Vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrPavardes.size()) - 1));
        return {vyrVardai[vardoIndeksas], vyrPavardes[pavardesIndeksas]};
    }
    else {
        const auto vardoIndeksas = static_cast<Vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<Vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motPavardes.size()) - 1));
        return {motVardai[vardoIndeksas], motPavardes[pavardesIndeksas]};
    }
}

std::pair<Vector<int>, int> generuotiRezultatus(int maksimalusNDKiekis) {
    const std::size_t ndKiekis = static_cast<std::size_t>(maksimalusNDKiekis);
    Vector<int> namuDarbai;
    namuDarbai.reserve(ndKiekis);
    for (std::size_t i = 0; i < ndKiekis; ++i) namuDarbai.push_back(generuotiSveikaSkaiciu(0, 10));
    const int egzaminoPazymys = generuotiSveikaSkaiciu(1, 10);
    return {std::move(namuDarbai), egzaminoPazymys};
}

Studentas sugeneruotiStudenta(const Failai& failai, int maksimalusNDKiekis){
    const auto [vardas, pavarde] = generuotiVardaPavarde(failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
    const auto [namuDarbai, egzaminoPazymys] = generuotiRezultatus(maksimalusNDKiekis);
    const std::string eilute = suformuotiStudentoIvestiesEilute(vardas, pavarde, namuDarbai, egzaminoPazymys);
    return sukurtiStudentaIsEilutesPerOperatoriu(eilute);
}

Vector<Studentas> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai){
    Vector<Studentas> studentuSarasas;
    studentuSarasas.reserve(static_cast<std::size_t>(studentuKiekis));
    for (int i = 0; i < studentuKiekis; ++i) studentuSarasas.emplace_back(sugeneruotiStudenta(failai, maksimalusNDKiekis));
    return studentuSarasas;
}