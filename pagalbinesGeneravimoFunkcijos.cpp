#include "strukturaGeneravimas.h"
#include <random>

void generuotiRezultatus(StudentasVektorius& studentas, int maksimalusNDKiekis){
    studentas.namuDarbuTarpiniaiRezultatai.clear();
    studentas.namuDarbuTarpiniaiRezultatai.reserve(maksimalusNDKiekis);
    for (int i = 0; i < maksimalusNDKiekis; ++i) studentas.namuDarbuTarpiniaiRezultatai.push_back(generuotiSveikaSkaiciu(0, 10));
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
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)vyrVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)vyrPavardes.size() - 1);
        studentas.Vardas = vyrVardai[vardoIndeksas];
        studentas.Pavarde = vyrPavardes[pavardesIndeksas];
    }
    else{
        int vardoIndeksas = generuotiSveikaSkaiciu(0, (int)motVardai.size() - 1);
        int pavardesIndeksas = generuotiSveikaSkaiciu(0, (int)motPavardes.size() - 1);
        studentas.Vardas = motVardai[vardoIndeksas];
        studentas.Pavarde = motPavardes[pavardesIndeksas];
    }
}

int generuotiSveikaSkaiciu(int nuo, int iki){
    static std::mt19937 generatorius(std::random_device{}());
    std::uniform_int_distribution<int> distribucija(nuo, iki);
    return distribucija(generatorius);
}