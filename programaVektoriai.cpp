#include "strukturaVektoriai.h"
#include "bendraStruktura.h"

int main(){
    std::vector<std::string> vyrVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_vyru_vardai.txt");
    std::vector<std::string> vyrPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_vyru_pavardes.txt");
    std::vector<std::string> motVardai = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviski_moteru_vardai.txt");
    std::vector<std::string> motPavardes = nuskaitytiEilutesIVektoriu("tekstiniaiFailai/Lietuviskos_moteru_pavardes.txt");
    std::string studentai10000 = "tekstiniaiFailai/studentai10000.txt";
    std::string studentai100000 = "tekstiniaiFailai/studentai100000.txt";
    std::string studentai1000000 = "tekstiniaiFailai/studentai1000000.txt";
    std::string kursiokai = "tekstiniaiFailai/kursiokai.txt";
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
            std::vector<std::string> meniuNuskaitymo = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            std::vector<std::string> meniuRikiavimo = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį pagal vidurkį didėjančia tvarka (1-10)", "6 - galutinį pažymį pagal medianą didėjančia tvarka (1-10)", "7 - galutinį pažymį pagal vidurkį mažėjančia tvarka (10-1)", "8 - galutinį pažymį pagal medianą mažėjančia tvarka (10-1)"};
            std::vector<std::string> meniuIsvedimo = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
            int kartai = nuskaitytiTeigiamaSveikajiSkaiciu("Įveskite norimą testų kiekį ir paspauskite ENTER: ");
            int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(meniuNuskaitymo);
            int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(meniuRikiavimo);
            int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(meniuIsvedimo);
            for (int i = 0; i < kartai; ++i){
                auto nuskaitymoStartas = std::chrono::steady_clock::now();
                if (pasirinkimasNuskaitymo == 1) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(kursiokai, 3);
                if (pasirinkimasNuskaitymo == 2) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai10000, 10000);
                if (pasirinkimasNuskaitymo == 3) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai100000, 100000);
                if (pasirinkimasNuskaitymo == 4) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai1000000, 1000000);
                auto nuskaitymoPabaiga = std::chrono::steady_clock::now();
                auto skaiciavimuStartas = std::chrono::steady_clock::now();
                for (auto& studentas : studentuSarasas){
                    double galutinisRezultatasPagalVidurki = skaiciuotiGalutiniVidurki(studentas);
                    studentas.galutinisRezultatasPagalVidurki = galutinisRezultatasPagalVidurki;
                    double galutinisRezultatasPagalMediana = skaiciuotiGalutineMediana(studentas);
                    studentas.galutinisRezultatasPagalMediana = galutinisRezultatasPagalMediana;
                }
                auto skaiciavimuPabaiga = std::chrono::steady_clock::now();
                auto rikiavimoStartas = std::chrono::steady_clock::now();
                if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisDidejanciaTvarka(&StudentasVektorius::vardasNr, &StudentasVektorius::Vardas));
                if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisMazejanciaTvarka(&StudentasVektorius::vardasNr, &StudentasVektorius::Vardas));
                if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisDidejanciaTvarka(&StudentasVektorius::pavardeNr, &StudentasVektorius::Pavarde));
                if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisMazejanciaTvarka(&StudentasVektorius::pavardeNr, &StudentasVektorius::Pavarde));
                if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalVidurki));
                if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalMediana));
                if (pasirinkimasRikiavimo == 7) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalVidurki));
                if (pasirinkimasRikiavimo == 8) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalMediana));
                auto rikiavimoPabaiga = std::chrono::steady_clock::now();
                auto isvedimoStartas = std::chrono::steady_clock::now();
                if (pasirinkimasIsvedimo == 1) parodytiRezultatuLentele(std::cout, studentuSarasas);
                if (pasirinkimasIsvedimo == 2){
                    std::ofstream isvedimoFailas("studentuRezultatai.txt");
                    parodytiRezultatuLentele(isvedimoFailas, studentuSarasas);
                    isvedimoFailas.flush();
                    isvedimoFailas.close();
                }  
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
            std::vector<std::string> meniuNuskaitymo = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
            int pasirinkimasNuskaitymo = nuskaitytiMeniuPasirinkima(meniuNuskaitymo);
            if (pasirinkimasNuskaitymo == 1) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(kursiokai,3 );
            if (pasirinkimasNuskaitymo == 2) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai10000, 10000);
            if (pasirinkimasNuskaitymo == 3) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai100000, 100000);
            if (pasirinkimasNuskaitymo == 4) studentuSarasas = nuskaitytiStudentuDuomenisIsFailo(studentai1000000, 1000000);
            for (auto& studentas : studentuSarasas){
                double galutinisRezultatasPagalVidurki = skaiciuotiGalutiniVidurki(studentas);
                studentas.galutinisRezultatasPagalVidurki = galutinisRezultatasPagalVidurki;
                double galutinisRezultatasPagalMediana = skaiciuotiGalutineMediana(studentas);
                studentas.galutinisRezultatasPagalMediana = galutinisRezultatasPagalMediana;
            }
            std::vector<std::string> meniuRikiavimo = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį pagal vidurkį didėjančia tvarka (1-10)", "6 - galutinį pažymį pagal medianą didėjančia tvarka (1-10)", "7 - galutinį pažymį pagal vidurkį mažėjančia tvarka (10-1)", "8 - galutinį pažymį pagal medianą mažėjančia tvarka (10-1)"};
            int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(meniuRikiavimo);
            if (pasirinkimasRikiavimo == 1) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisDidejanciaTvarka(&StudentasVektorius::vardasNr, &StudentasVektorius::Vardas));
            if (pasirinkimasRikiavimo == 2) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisMazejanciaTvarka(&StudentasVektorius::vardasNr, &StudentasVektorius::Vardas));
            if (pasirinkimasRikiavimo == 3) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisDidejanciaTvarka(&StudentasVektorius::pavardeNr, &StudentasVektorius::Pavarde));
            if (pasirinkimasRikiavimo == 4) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiVardaSuSkaiciaisMazejanciaTvarka(&StudentasVektorius::pavardeNr, &StudentasVektorius::Pavarde));
            if (pasirinkimasRikiavimo == 5) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalVidurki));
            if (pasirinkimasRikiavimo == 6) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalDidejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalMediana));
            if (pasirinkimasRikiavimo == 7) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalVidurki));
            if (pasirinkimasRikiavimo == 8) std::sort(studentuSarasas.begin(), studentuSarasas.end(), lygintiElementusPagalMazejanciaReiksme(&StudentasVektorius::galutinisRezultatasPagalMediana));
            std::vector<std::string> meniuIsvedimo = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
            int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(meniuIsvedimo);
            if (pasirinkimasIsvedimo == 1) parodytiRezultatuLentele(std::cout, studentuSarasas);
            if (pasirinkimasIsvedimo == 2){
                std::ofstream isvedimoFailas("studentuRezultatai.txt");
                parodytiRezultatuLentele(isvedimoFailas, studentuSarasas);
                isvedimoFailas.flush();
                isvedimoFailas.close();
            }    
        } else{
            char skaiciavimoMetodoPasirinkimas = nuskaitytiSkaiciavimoMetoda();
            if (pasirinkimas == 3){
                int generuojamuStudentuKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite norimą generuoti studentų kiekį ir paspauskite ENTER: ");
                int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų pažymių kiekį ir paspauskite ENTER: ");
                studentuSarasas.reserve(generuojamuStudentuKiekis);
                for (int i = 0; i < generuojamuStudentuKiekis; i++){
                    StudentasVektorius studentas;
                    generuotiVardaPavarde(studentas, vyrVardai, vyrPavardes, motVardai, motPavardes);
                    generuotiRezultatus(studentas, maksimalusNDKiekis);
                    studentuSarasas.push_back(std::move(studentas));
                }
                parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
                continue;
            }
            int maksimalusNDKiekis = 0;
            if (pasirinkimas == 1 || pasirinkimas == 2) maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
            while (true){
                std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
                std::string ivestis;
                if (!getline(std::cin, ivestis)) return 0;
                if (!(tikrintiIvesti(ivestis) && ivestis.size() == 1)){
                    std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                    continue;
                }
                char pasirinkimas = ivestis[0];
                if (pasirinkimas == 'N' || pasirinkimas == 'n') break;
                if (!(pasirinkimas == 'T' || pasirinkimas == 't')){
                    std::cout << "Įveskite TIK vieną raidę: T arba N.\n";
                    continue;
                }
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
            parodytiRezultatuLentele(studentuSarasas, skaiciavimoMetodoPasirinkimas);
        }
    }
    return 0;
}    