#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/Failai.h"
#include <random>

void generuotiRezultatus(Studentas& studentas, int maksimalusNDKiekis){
    const std::size_t ndKiekis = static_cast<std::size_t>(maksimalusNDKiekis);
    studentas.clearHomeworkGrades();
    studentas.reserveHomeworkGrades(ndKiekis);
    for (std::size_t i = 0; i < ndKiekis; ++i) studentas.addHomeworkGrade(generuotiSveikaSkaiciu(0, 10));
    studentas.setExamGrade() = generuotiSveikaSkaiciu(1, 10);
}

void generuotiVardaPavarde(Studentas& studentas, const std::vector<std::string>& vyrVardai, const std::vector<std::string>& vyrPavardes, const std::vector<std::string>& motVardai, const std::vector<std::string>& motPavardes){
    if (vyrVardai.empty() || vyrPavardes.empty() || motVardai.empty() || motPavardes.empty()){
        studentas.setName("Vardenis");
        studentas.setSurname("Pavardenis");
        return;
    }
    int lytis = generuotiSveikaSkaiciu(0, 1);
    if (lytis == 0){
        const auto vardoIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(vyrPavardes.size()) - 1));
        studentas.setName(vyrVardai[vardoIndeksas]);
        studentas.setSurname(vyrPavardes[pavardesIndeksas]);
    }
    else{
        const auto vardoIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motVardai.size()) - 1));
        const auto pavardesIndeksas = static_cast<std::vector<std::string>::size_type>(generuotiSveikaSkaiciu(0, static_cast<int>(motPavardes.size()) - 1));
        studentas.setName(motVardai[vardoIndeksas]);
        studentas.setSurname(motPavardes[pavardesIndeksas]);
    }
}

int generuotiSveikaSkaiciu(int nuo, int iki){
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}

std::vector<Studentas> generuotiStudentus(int studentuKiekis, int maksimalusNDKiekis, const Failai& failai){
    std::vector<Studentas> studentuSarasas;
    studentuSarasas.reserve(static_cast<std::size_t>(studentuKiekis));
    for (int i = 0; i < studentuKiekis; ++i){
        Studentas studentas;
        generuotiVardaPavarde(studentas, failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
        generuotiRezultatus(studentas, maksimalusNDKiekis);
        studentuSarasas.push_back(std::move(studentas));
    }
    return studentuSarasas;
}