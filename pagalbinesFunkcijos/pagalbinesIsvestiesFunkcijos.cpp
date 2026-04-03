#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaTestavimas.h"
#include "../strukturosFailai/Failai.h"
#include <iostream>
#include <fstream>
#include <format>


void parodytiRezultatuLentele(std::ostream& out, const std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    out << std::string(98, '-') << "\n";
    out << std::format("{:<40}{:<40}{:<18}\n", "Vardas", "Pavardė", (skaiciavimoMetodoPasirinkimas == 'V' || skaiciavimoMetodoPasirinkimas == 'v' ? "Galutinis (Vid.)" : "Galutinis (Med.)"));
    out << std::string(98, '-') << "\n";
    for (const auto& studentas : studentuSarasas){
        out << std::format("{:<40}{:<40}{:<18.2f}\n", studentas.getName(), studentas.getSurname(), studentas.calculateFinalGrade(skaiciavimoMetodoPasirinkimas));
    }
}

void isvestiStudentus(int pasirinkimasIsvedimo, const std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    if (pasirinkimasIsvedimo == 1) parodytiRezultatuLentele(std::cout, studentuSarasas, skaiciavimoMetodoPasirinkimas);
    if (pasirinkimasIsvedimo == 2){
        std::ofstream isvedimoFailas("studentuRezultatai.txt");
        parodytiRezultatuLentele(isvedimoFailas, studentuSarasas, skaiciavimoMetodoPasirinkimas);
        isvedimoFailas.flush();
        isvedimoFailas.close();
    }
}

void spausdintiVidurkius(const TestoLaikai& laikai){
    if (laikai.nuskaitymas > 0) std::cout << "Duomenų nuskaitymas vidutiniškai užtruko: " << laikai.nuskaitymas << "s.\n";
    if (laikai.skaiciavimas > 0) std::cout << "Galutinių rezultatų skaičiavimas vidutiniškai užtruko: " << laikai.skaiciavimas << "s.\n";
    if (laikai.rikiavimas > 0) std::cout << "Studentų rikiavimas vidutiniškai užtruko: " << laikai.rikiavimas << "s.\n";
    if (laikai.skirstymas > 0) std::cout << "Studentų skirstymas vidutiniškai užtruko: " << laikai.skirstymas << "s.\n";
    if (laikai.isvedimas > 0) std::cout << "Studentų išvedimas vidutiniškai užtruko: " << laikai.isvedimas << "s.\n";
    if (apskaiciuotiBendraLaika(laikai) > 0) std::cout << "Bendras programos veikimas vidutiniškai užtruko: "<< apskaiciuotiBendraLaika(laikai) << "s.\n";
}

void parodytiStudentus(const std::vector<Studentas>& studentai, char skaiciavimoMetodas){
    parodytiRezultatuLentele(std::cout, studentai, skaiciavimoMetodas);
}