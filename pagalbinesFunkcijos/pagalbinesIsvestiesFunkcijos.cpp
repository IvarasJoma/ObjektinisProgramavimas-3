#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaTestavimas.h"
#include "../strukturosFailai/Failai.h"
#include <iostream>
#include <fstream>
#include <format>


void parodytiRezultatuLentele(std::ostream& out, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    out << std::string(98, '-') << "\n";
    out << std::format("{:<40}{:<40}{:<18}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    out << std::string(98, '-') << "\n";
    for (const auto& studentas : studentuSarasas){
        double galutinisRezultatas = (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v') ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutineMediana(studentas);
        out << std::format("{:<40}{:<40}{:<18.2f}\n", studentas.Vardas, studentas.Pavarde, galutinisRezultatas);
    }
}

void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<StudentasVektorius>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    if (pasirinkimasIsvedimo == 1) parodytiRezultatuLentele(std::cout, studentuSarasas, skaiciavimoMetodoPasirinkimas);
    if (pasirinkimasIsvedimo == 2){
        std::ofstream isvedimoFailas("studentuRezultatai.txt");
        parodytiRezultatuLentele(isvedimoFailas, studentuSarasas, skaiciavimoMetodoPasirinkimas);
        isvedimoFailas.flush();
        isvedimoFailas.close();
    }
}

void spausdintiVidurkius(const TestoLaikai& laikai) {
    std::cout << "Duomenų nuskaitymas vidutiniškai užtruko: " << laikai.nuskaitymas << "s.\n";
    std::cout << "Galutinių rezultatų skaičiavimas vidutiniškai užtruko: " << laikai.skaiciavimas << "s.\n";
    std::cout << "Studentų rikiavimas vidutiniškai užtruko: " << laikai.rikiavimas << "s.\n";
    std::cout << "Studentų išvedimas vidutiniškai užtruko: " << laikai.isvedimas << "s.\n";
    std::cout << "Bendras programos veikimas vidutiniškai užtruko: " << apskaiciuotiBendraLaika(laikai) << "s.\n";
}

void parodytiStudentus(const std::vector<StudentasVektorius>& studentai, char skaiciavimoMetodas) {
    parodytiRezultatuLentele(std::cout, studentai, skaiciavimoMetodas);
}