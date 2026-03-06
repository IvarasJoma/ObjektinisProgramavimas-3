#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/Failai.h"
#include <random>

void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis){
    const std::size_t ndKiekis = static_cast<std::size_t>(maksimalusNDKiekis);
    studentas.namuDarbuTarpiniaiRezultatai.clear();
    studentas.namuDarbuTarpiniaiRezultatai.reserve(ndKiekis);
    for (std::size_t i = 0; i < ndKiekis; ++i) studentas.namuDarbuTarpiniaiRezultatai.push_back(generuotiSveikaSkaiciu(0, 10));
    studentas.egzaminoRezultatas = generuotiSveikaSkaiciu(1, 10);
}

void generuotiVardaPavarde(StudentasVektorius& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()){
        studentas.Vardas = "Vardenis";
        studentas.Pavarde = "Pavardenis";
        return;
    }
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0){
        const auto vardoIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrPavardes.size()) - 1));
        studentas.Vardas = vyrVardai[vardoIndeksas];
        studentas.Pavarde = vyrPavardes[pavardesIndeksas];
    }
    else{
        const auto vardoIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motPavardes.size()) - 1));
        studentas.Vardas = motVardai[vardoIndeksas];
        studentas.Pavarde = motPavardes[pavardesIndeksas];
    }
}

int generuotiSveikaSkaiciu(int nuo, int iki){
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}

std::vector<StudentasVektorius> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai) {
    std::vector<StudentasVektorius> studentai;
    studentai.reserve(static_cast<std::size_t>(studentuKiekis));
    for (int i = 0; i < studentuKiekis; ++i) {
        StudentasVektorius studentas;
        generuotiVardaPavarde(studentas, failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
        generuotiRezultatus(studentas, maksimalusNDKiekis);
        studentai.push_back(std::move(studentas));
    }
    return studentai;
}