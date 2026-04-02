#include <iostream>
#include <string>
#include <vector>

Studentas::Studentas(const char* eilute, std::size_t namuDarbuKiekis){readStudent(const char* eilute, std::size_t namuDarbuKiekis)};
Studentas::Studentas(bool generuotiPazymius, int ndKiekis){inputStudent(bool generuotiPazymius, int ndKiekis)};

Studentas::Studentas(const char* eilute, std::size_t namuDarbuKiekis) : examGrade_(0) {
    const char* rodykle = eilute;
    std::string vardas;
    std::string pavarde;
    if (!nuskaitytiZodiIsFailo(rodykle, vardas)) throw std::runtime_error("Nepavyko nuskaityti studento vardo");
    if (!nuskaitytiZodiIsFailo(rodykle, pavarde)) throw std::runtime_error("Nepavyko nuskaityti studento pavardes");
    name_ = vardas;
    surname_ = pavarde;
    for (std::size_t i = 0; i < namuDarbuKiekis; i++) {
        int laikinasPazymys = 0;
        if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, laikinasPazymys)) laikinasPazymys = 0;
        homeworkGrade_.push_back(laikinasPazymys);
    }
    int egzaminoRezultatas = 0;
    if (!nuskaitytiSveikaSkaiciuIsFailo(rodykle, egzaminoRezultatas)) egzaminoRezultatas = 0;
    examGrade_ = egzaminoRezultatas;
}

Studentas::Studentas(bool generuotiPazymius, int ndKiekis) : examGrade_(0) {
    name_ = nuskaitytiVardaArPavarde("Įveskite studento vardą: ", tvarkytiVarda, "Studento vardas negali būti tuščia eilutė.");
    surname_ = nuskaitytiVardaArPavarde("Įveskite studento pavardę: ", tvarkytiPavarde, "Studento pavardė negali būti tuščia eilutė.");
    if (generuotiPazymius) for (int i = 0; i < ndKiekis; ++i) homeworkGrade_.push_back(generuotiSveikaSkaiciu(1, 10));
    else for (int i = 0; i < ndKiekis; ++i) homeworkGrade_.push_back(nuskaitytiPazymiNuo1iki10("Įveskite namų darbo pažymį (1-10): "));
    examGrade_ = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ")
}

