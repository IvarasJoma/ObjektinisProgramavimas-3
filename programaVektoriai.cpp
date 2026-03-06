#include "strukturaVisi.h"
#include <iostream>
#include <algorithm>
#include <fstream>

int main(){
    Failai failai;
    std::vector<std::string> meniu = {"Galimi programos veikimo būdai:", "1 - Įvesti duomenis ranka", "2 - Generuoti tik pažymius", "3 - Generuoti vardus, pavardes ir pažymius", "4 - Nuskaityti duomenis iš failo", "5 - Testuoti programą", "6 - Baigti darbą"};
    int pasirinkimas = 0;
    while (nuskaitytiPagrindinioMeniuPasirinkima(meniu, pasirinkimas)){
        if (pasirinkimas == 6) break;
        std::vector<StudentasVektorius> studentuSarasas;
        studentuSarasas.clear();
        if (pasirinkimas == 5){
            TestoLaikai laikai;
            char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
            std::vector<std::string> meniuNuskaitymo = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            std::vector<std::string> meniuRikiavimo = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
            std::vector<std::string> meniuIsvedimo = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
            int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
            int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(meniuNuskaitymo);
            int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(meniuRikiavimo);
            int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(meniuIsvedimo);
            for (int i = 0; i < kartai; ++i){
                laikai.nuskaitymas += ismatuotiLaika([&](){nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, failai);});
                laikai.skaiciavimas += ismatuotiLaika([&]() {for (auto& studentas : studentuSarasas) {apskaiciuotiGalutiniPazymi(studentas, skaiciavimoMetodoPasirinkimas);}});
                laikai.rikiavimas += ismatuotiLaika([&]() {rikiuotiStudentus(pasirinkimasRikiavimo, pasirinkimasNuskaitymo, studentuSarasas);});
                laikai.isvedimas += ismatuotiLaika([&]() {isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodoPasirinkimas);});
            }
            laikai.padalintiIs(kartai);
            spausdintiVidurkius(laikai);
        }
        else if (pasirinkimas == 4){
            char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
            std::vector<std::string> meniuNuskaitymo = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(meniuNuskaitymo);
            nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, failai);
            for (auto& studentas : studentuSarasas){
                apskaiciuotiGalutiniPazymi(studentas, skaiciavimoMetodoPasirinkimas);
            }
            std::vector<std::string> meniuRikiavimo = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
            int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(meniuRikiavimo);
            rikiuotiStudentus(pasirinkimasRikiavimo, pasirinkimasNuskaitymo, studentuSarasas);
            std::vector<std::string> meniuIsvedimo = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
            int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(meniuIsvedimo);
            isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodoPasirinkimas);    
        } else{
            char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
            if (pasirinkimas == 3){
                int generuojamuStudentuKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite norimą generuoti studentų kiekį ir paspauskite ENTER: ");
                int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų pažymių kiekį ir paspauskite ENTER: ");
                studentuSarasas.reserve(static_cast<std::size_t>(generuojamuStudentuKiekis));
                for (int i = 0; i < generuojamuStudentuKiekis; i++){
                    StudentasVektorius studentas;
                    generuotiVardaPavarde(studentas, failai.vyrVardai, failai.vyrPavardes, failai.motVardai, failai.motPavardes);
                    generuotiRezultatus(studentas, maksimalusNDKiekis);
                    studentuSarasas.push_back(std::move(studentas));
                }
                parodytiRezultatuLentele(std::cout,studentuSarasas, skaiciavimoMetodoPasirinkimas);
                continue;
            }
            int maksimalusNDKiekis = 0;
            if (pasirinkimas == 1 || pasirinkimas == 2) maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
            while (patvirtintiNaujoStudentoPridejima()){
                StudentasVektorius studentas;
                studentas.Vardas = nuskaitytiVardaArPavarde("Įveskite studento vardą: ", tvarkytiVarda, "Studento vardas negali būti tuščia eilutė.\n");
                studentas.Pavarde = nuskaitytiVardaArPavarde("Įveskite studento pavardę: ", tvarkytiPavarde, "Studento pavardė negali būti tuščia eilutė.\n");
                if (pasirinkimas == 2) generuotiRezultatus(studentas, maksimalusNDKiekis);
                else{
                    nuskaitytiNamuDarbuPazymius(studentas.namuDarbuTarpiniaiRezultatai, maksimalusNDKiekis);
                    studentas.egzaminoRezultatas = nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): ");
                }
                studentuSarasas.push_back(std::move(studentas));
            }
            parodytiRezultatuLentele(std::cout, studentuSarasas, skaiciavimoMetodoPasirinkimas);
        }
    }
    return 0;
}    