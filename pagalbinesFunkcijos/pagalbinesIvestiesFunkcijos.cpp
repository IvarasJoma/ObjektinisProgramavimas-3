#include "../strukturosFailai/strukturaIvestis.h"
#include "../strukturosFailai/strukturaIsvestis.h"
#include "../strukturosFailai/strukturaRikiavimas.h"
#include "../strukturosFailai/strukturaGeneravimas.h"
#include "../strukturosFailai/strukturaSkaiciavimai.h"
#include "../strukturosFailai/strukturaMeniu.h"
#include "../strukturosFailai/Failai.h"
#include <iostream>
#include <charconv>
#include <sstream>

std::string saugiaiNuskaitytiEilute(){
    std::string ivestis;
    if (!std::getline(std::cin, ivestis)){
        if (std::cin.eof()){
            std::cout << "\nĮvestis netikėtai nutraukta. Programa baigiama.\n";
            std::exit(0);
        }
        throw std::runtime_error("Nepavyko nuskaityti įvesties.");
    }
    return ivestis;
}

void nuskaitytiNamuDarbuPazymius(Studentas& studentas, int maksimalusNDKiekis){
    studentas.clearHomeworkGrades();
    std::size_t ndKiekis = static_cast<std::size_t>(maksimalusNDKiekis);
    while (studentas.getHomeworkGrades().size() < ndKiekis){
        try{
            std::cout << "Įveskite studento namų darbų pažymius (1-10). Po kiekvieno įvesto pažymio paspauskite klavišą ENTER. Baigus tuščioje eilutėje paspauskite klavišą ENTER: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            if (ivestis.empty()) break;
            int reiksme = 0;
            nuskaitytiSveikajiSkaiciu(ivestis, reiksme);
            if (reiksme < 1 || reiksme > 10) throw std::out_of_range("Studento namų darbų pažymys turi būti sveikasis skaičius intervale nuo 1 iki 10.");
            studentas.addHomeworkGrade(reiksme);
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
    if (studentas.getHomeworkGrades().size() == ndKiekis) std::cout << "Pasiektas maksimalus namų darbų pažymių kiekis.\n";
    while (studentas.getHomeworkGrades().size() < ndKiekis) studentas.addHomeworkGrade(0);
}

void tikrintiIvesti(const std::string& ivestis){
    for (char simbolis : ivestis){
        if (!isspace(static_cast<unsigned char>(simbolis))) return;
    }
    throw std::invalid_argument("Įvestis negali būti tuščia arba sudaryta tik iš tarpų.");
}

void tvarkytiVarda(std::string& ivestis){
    std::stringstream eilutesSrautas(ivestis);
    std::string pirmasZodis, antrasZodis;
    eilutesSrautas >> pirmasZodis >> antrasZodis;
    if (!pirmasZodis.empty()){
        for (char& simbolis : pirmasZodis) simbolis = static_cast<char>(std::tolower(static_cast<unsigned char>(simbolis)));
        pirmasZodis[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(pirmasZodis[0])));
    }
    if (!antrasZodis.empty()){
        for (char& simbolis : antrasZodis) simbolis = static_cast<char>(std::tolower(static_cast<unsigned char>(simbolis)));
        antrasZodis[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(antrasZodis[0])));
    }
    if (antrasZodis.empty()) ivestis = pirmasZodis;
    else ivestis = pirmasZodis + " " + antrasZodis;
}

void tvarkytiPavarde(std::string& ivestis){
    std::stringstream eilutesSrautas(ivestis);
    bool kitaDidzioji = true;
    for (char& simbolis : ivestis){
        simbolis = static_cast<char>(std::tolower(static_cast<unsigned char>(simbolis)));
        if (kitaDidzioji && std::isalpha(static_cast<unsigned char>(simbolis))){
            simbolis = static_cast<char>(std::toupper(static_cast<unsigned char>(simbolis)));
            kitaDidzioji = false;
        }
        if (simbolis == '-') kitaDidzioji = true;
    }
}

void nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme){
    reiksme = 0;
    auto rezultatas = std::from_chars(ivestis.data(), ivestis.data() + ivestis.size(), reiksme);
    if (rezultatas.ec != std::errc{} || rezultatas.ptr != ivestis.data() + ivestis.size()) throw std::invalid_argument("Įvestis turi būti sveikasis skaičius.");
}

bool nuskaitytiPagrindinioMeniuPasirinkima(const std::vector<std::string>& eilutes, int& pasirinkimas){
    while (true){
        try{
            std::cout << std::string(98, '-') << "\n";
            for (const auto& eilute : eilutes)
                std::cout << eilute << "\n";
            std::cout << std::string(98, '-') << "\n";
            std::cout << "Pasirinkite programos eigą: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            const int maxMeniu = static_cast<int>(eilutes.size()) - 1;
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, pasirinkimas);
            if (pasirinkimas < 1 || pasirinkimas > maxMeniu) throw std::out_of_range("Pasirinkimas turi būti nuo 1 iki " + std::to_string(maxMeniu) + ".");
            return true;
        } catch (const std::exception& e){
        std::cout << "Klaida: " << e.what() << "\n";
        } 
    }
}

char nuskaitytiSkaiciavimoMetoda(){
    while (true){
        try{
            std::cout << "Pasirinkite galutinio pažymio skaičiavimo metodą: V - vidurkiu grįstas, M - mediana grįstas: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            tikrintiIvesti(ivestis);
            if (ivestis.size() != 1 || !std::isalpha(static_cast<unsigned char>(ivestis[0])) || (ivestis[0] != 'V' && ivestis[0] != 'v' && ivestis[0] != 'M' && ivestis[0] != 'm')) throw std::invalid_argument("Įveskite tik vieną raidę: V arba M.");
            return ivestis[0];
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

int nuskaitytiMinimaluSveikajiSkaiciu(const char* pranesimas, int minimaliReiksme){
    while (true){
        try{
            std::cout << pranesimas;
            std::string ivestis = saugiaiNuskaitytiEilute();
            int reiksme = 0;
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, reiksme);
            if (reiksme < minimaliReiksme)
                throw std::out_of_range(minimaliReiksme <= 0 ? "Reikšmė turi būti neneigiamas skaičius (0 ir daugiau)." : "Reikšmė turi būti teigiamas skaičius (1 ir daugiau).");
            return reiksme;
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas){ return nuskaitytiMinimaluSveikajiSkaiciu(pranesimas, 0);}

int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas){ return nuskaitytiMinimaluSveikajiSkaiciu(pranesimas, 1); }

int nuskaitytiPazymiNuo1iki10(const char* pranesimas){
    while (true){
        try{
            std::cout << pranesimas;
            std::string ivestis = saugiaiNuskaitytiEilute();
            int reiksme = 0;
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, reiksme);
            if (reiksme < 1 || reiksme > 10) throw std::out_of_range("Įveskite sveiką skaičių intervale nuo 1 iki 10.");
            return reiksme;
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

bool patvirtintiNaujoStudentoPridejima(){
    while (true){
        try{
            std::cout << "Pasirinkite, ar norite įvesti studentą: T - norite, N - nenorite: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            tikrintiIvesti(ivestis);
            if (ivestis.size() != 1 || !std::isalpha(static_cast<unsigned char>(ivestis[0])) || (ivestis[0] != 'T' && ivestis[0] != 't' && ivestis[0] != 'N' && ivestis[0] != 'n')) throw std::invalid_argument("Įveskite tik vieną raidę: T arba N.");
            return ivestis[0] == 'T' || ivestis[0] == 't';
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

std::string nuskaitytiVardaArPavarde(const char* ivestiesPranesimas, void(*tvarkyti)(std::string&), const char* klaidosPranesimas){
    while (true){
        try{
            std::cout << ivestiesPranesimas;
            std::string ivestis = saugiaiNuskaitytiEilute();
            try{
                tikrintiIvesti(ivestis);
            } catch (const std::exception&){
                throw std::invalid_argument(klaidosPranesimas);
            }
            for (char simbolis : ivestis){
                if (!std::isalpha(static_cast<unsigned char>(simbolis)) && simbolis != ' ' && simbolis != '-' && static_cast<unsigned char>(simbolis) < 128) throw std::invalid_argument("Varde arba pavardėje gali būti tik raidės, tarpai ir brūkšneliai.");
            }
            tvarkyti(ivestis);
            return ivestis;
        }
        catch (const std::exception& e){
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

void apdorotiIrIsvestiStudentus(std::vector<Studentas>& studentuSarasas, char skaiciavimoMetodoPasirinkimas){
    apskaiciuotiGalutiniusPazymius(studentuSarasas, skaiciavimoMetodoPasirinkimas);
    int pasirinkimasRikiavimo = nuskaitytiMeniuPasirinkima(RIKIAVIMO_MENIU);
    rikiuotiStudentus(pasirinkimasRikiavimo, studentuSarasas);
    int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(ISVEDIMO_MENIU);
    isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodoPasirinkimas);
}

Studentas sukurtiStudentaRankaArbaSuGeneruotaisPazymiais(bool generuotiPazymius, int maksimalusNDKiekis){
    Studentas studentas;
    studentas.setName(nuskaitytiVardaArPavarde("Įveskite studento vardą: ", tvarkytiVarda, "Studento vardas negali būti tuščia eilutė."));
    studentas.setSurname(nuskaitytiVardaArPavarde("Įveskite studento pavardę: ", tvarkytiPavarde, "Studento pavardė negali būti tuščia eilutė."));
    if (generuotiPazymius) generuotiRezultatus(studentas, maksimalusNDKiekis);
    else{
        nuskaitytiNamuDarbuPazymius(studentas, maksimalusNDKiekis);
        studentas.setExamGrade(nuskaitytiPazymiNuo1iki10("Įveskite studento egzamino pažymį (1-10): "));
    }
    return studentas;
}

std::vector<Studentas> ivestiStudentus(bool generuotiPazymius, int maksimalusNDKiekis){
    std::vector<Studentas> studentai;
    while (patvirtintiNaujoStudentoPridejima()) studentai.push_back(sukurtiStudentaRankaArbaSuGeneruotaisPazymiais(generuotiPazymius, maksimalusNDKiekis));
    return studentai;
}

void vykdytiStudentuIvedima(bool generuotiPazymius){
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų darbų pažymių kiekį ir paspauskite ENTER: ");
    auto studentai = ivestiStudentus(generuotiPazymius, maksimalusNDKiekis);
    parodytiStudentus(studentai, skaiciavimoMetodas);
}

void vykdytiPilnaGeneravima(Failai& failai){
    char skaiciavimoMetodas = nuskaitytiSkaiciavimoMetoda();
    int studentuKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite norimą generuoti studentų kiekį ir paspauskite ENTER: ");
    int maksimalusNDKiekis = nuskaitytiNeneigiamaSveikajiSkaiciu("Įveskite maksimalų galimą namų pažymių kiekį ir paspauskite ENTER: ");
    std::vector<Studentas> studentuSarasas = generuotiStudentus(studentuKiekis, maksimalusNDKiekis, failai);
    int pasirinkimasIsvedimo = nuskaitytiMeniuPasirinkima(ISVEDIMO_MENIU);
    isvestiStudentus(pasirinkimasIsvedimo, studentuSarasas, skaiciavimoMetodas);
}

void parinktiRikiavimoBudus(int& pasirinkimasRikiavimoPazangiu, int& pasirinkimasRikiavimoSilpnu){
    pasirinkimasRikiavimoPazangiu = nuskaitytiMeniuPasirinkima(PAZANGIU_RIKIAVIMO_MENIU);
    pasirinkimasRikiavimoSilpnu = nuskaitytiMeniuPasirinkima(SILPNU_RIKIAVIMO_MENIU);
}