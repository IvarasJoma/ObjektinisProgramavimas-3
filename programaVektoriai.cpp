#include "strukturaDarbasSuFailais.h"
#include "strukturaGeneravimas.h"
#include "strukturaIvestisIsvestis.h"
#include "strukturaLaikoMatavimas.h"
#include "strukturaSkaiciavimai.h"
#include "strukturaStudentas.h"
#include "strukturaRikiavimas.h"
#include "Failai.h"
#include <iostream>
#include <algorithm>
#include <fstream>

int main(){
    Failai failai;
    while (true){
        std::vector<std::string> meniu = {"Galimi programos veikimo būdai:", "1 - Įvesti duomenis ranka", "2 - Generuoti tik pažymius", "3 - Generuoti vardus, pavardes ir pažymius", "4 - Nuskaityti duomenis iš failo", "5 - Testuoti programą", "6 - Baigti darbą"};
        int pasirinkimas = nuskaitytiMeniuPasirinkima(meniu);
        if (pasirinkimas == 6) break;
        std::vector<StudentasVektorius> studentuSarasas;
        studentuSarasas.clear();
        if (pasirinkimas == 5){
            double sumaNuskaitymo = 0.0;
            double sumaSkaiciavimo = 0.0;
            double sumaRikiavimo = 0.0;
            double sumaIsvedimo = 0.0;
            char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
            std::vector<std::string> meniuNuskaitymo = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            std::vector<std::string> meniuRikiavimo = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
            std::vector<std::string> meniuIsvedimo = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
            int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
            int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(meniuNuskaitymo);
            int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(meniuRikiavimo);
            int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(meniuIsvedimo);
            for (int i = 0; i < kartai; ++i){
                auto nuskaitymoStartas = std::chrono::steady_clock::now();
                nuskaitytiDuomenis(pasirinkimasNuskaitymo, studentuSarasas, failai);
                auto nuskaitymoPabaiga = std::chrono::steady_clock::now();
                auto skaiciavimuStartas = std::chrono::steady_clock::now();
                for (auto& studentas : studentuSarasas){
                    apskaiciuotiGalutiniPazymi(studentas, skaiciavimoMetodoPasirinkimas);
                }
                auto skaiciavimuPabaiga = std::chrono::steady_clock::now();
                auto rikiavimoStartas = std::chrono::steady_clock::now();
                rikiuotiStudentus(pasirinkimasRikiavimo, pasirinkimasNuskaitymo, studentuSarasas);
                auto rikiavimoPabaiga = std::chrono::steady_clock::now();
                auto isvedimoStartas = std::chrono::steady_clock::now();
                isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodoPasirinkimas);  
                auto isvedimoPabaiga = std::chrono::steady_clock::now();
                sumaNuskaitymo += apskaiciuotiLaika(nuskaitymoStartas, nuskaitymoPabaiga);
                sumaSkaiciavimo += apskaiciuotiLaika(skaiciavimuStartas, skaiciavimuPabaiga);
                sumaRikiavimo += apskaiciuotiLaika(rikiavimoStartas, rikiavimoPabaiga);
                sumaIsvedimo += apskaiciuotiLaika(isvedimoStartas, isvedimoPabaiga);
            }
            double vidurkisNuskaitymo = sumaNuskaitymo / kartai;
            double vidurkisSkaiciavimo = sumaSkaiciavimo / kartai;
            double vidurkisRikiavimo = sumaRikiavimo / kartai;
            double vidurkisIsvedimo = sumaIsvedimo / kartai;
            std::cout << "Duomenų nuskaitymas vidutiniškai užtruko: " << vidurkisNuskaitymo << "s.\n";
            std::cout << "Galutinių rezultatų skaičiavimas vidutiniškai užtruko: " << vidurkisSkaiciavimo << "s.\n";
            std::cout << "Studentų rikiavimas vidutiniškai užtruko: " << vidurkisRikiavimo << "s.\n";
            std::cout << "Studentų išvedimas vidutiniškai užtruko: " << vidurkisIsvedimo << "s.\n";
            std::cout << "Bendras programos veikimas vidutiniškai užtruko: " << vidurkisNuskaitymo + vidurkisSkaiciavimo + vidurkisRikiavimo + vidurkisIsvedimo << "s.\n";
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
                studentuSarasas.reserve(generuojamuStudentuKiekis);
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
                while (true){
                    std::cout << "Įveskite studento vardą: ";
                    if (!getline(std::cin, studentas.Vardas)) return 0;
                    if (tikrintiIvesti(studentas.Vardas)){
                        tvarkytiVarda(studentas.Vardas);
                        break;
                    }
                    std::cout << "Studento vardas negali likti tuščias.\n";
                }
                while (true){
                    std::cout << "Įveskite studento pavardę: ";
                    if (!getline(std::cin, studentas.Pavarde)) return 0;
                    if (tikrintiIvesti(studentas.Pavarde)){
                        tvarkytiPavarde(studentas.Pavarde);
                        break;
                    }
                    std::cout << "Studento pavardė negali likti tuščia.\n";
                }
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