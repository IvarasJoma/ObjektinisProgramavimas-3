#ifndef STRUKTURAMENIU_H
#define STRUKTURAMENIU_H

#include <vector>
#include <string>

const std::vector<std::string> PAGRINDINIS_MENIU = {"Galimi programos veikimo būdai:", "1 - Įvesti duomenis ranka", "2 - Generuoti tik pažymius", "3 - Generuoti vardus, pavardes ir pažymius", "4 - Nuskaityti duomenis iš failo", "5 - Įrašyti duomenis į failą", "6 - Testuoti duomenų įvedimą į programą", "7 - Testuoti duomenų išvedimą iš programos", "8 - Baigti programą"};
const std::vector<std::string> NUSKAITYMO_MENIU = {"Pasirinkite iš kurio failo norite nuskaityti studentų duomenis:", "1 - kursiokai.txt", "2 - studentai10000.txt", "3 - studentai100000.txt", "4 - studentai1000000.txt"};
const std::vector<std::string> RIKIAVIMO_MENIU = {"Pasirinkite, pagal ką norite rikiuoti studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
const std::vector<std::string> PAZANGIU_RIKIAVIMO_MENIU = {"Pasirinkite, pagal ką norite rikiuoti pažangius studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
const std::vector<std::string> SILPNU_RIKIAVIMO_MENIU = {"Pasirinkite, pagal ką norite rikiuoti silpnus studentus:", "1 - vardą didėjančia tvarka (A-Ž)", "2 - vardą mažėjančia tvarka (Ž-A)", "3 - pavardę didėjančia tvarka (A-Ž)", "4 - pavardę mažėjančia tvarka (Ž-A)", "5 - galutinį pažymį didėjančia tvarka (1-10)", "6 - galutinį pažymį mažėjančia tvarka (10-1)"};
const std::vector<std::string> ISVEDIMO_MENIU = {"Pasirinkite, kaip norite išvesti duomenis:", "1 - į terminalą", "2 - į failą"};
const std::vector<std::string> ISVEDIMO_I_FAILA_MENIU = {"Pasirinkite, kiek studentų norite sugeneruoti:", "1 - 1000", "2 - 10000", "3 - 100000", "4 - 1000000", "5 - 10000000"};

#endif