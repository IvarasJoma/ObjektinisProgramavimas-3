#include "../strukturosFailai/strukturaMeniu.h"

const std::array<MeniuEilute, 13> PAGRINDINIS_MENIU = {{
    "Galimi programos veikimo būdai:",
    "1 - Įvesti duomenis ranka",
    "2 - Generuoti tik pažymius",
    "3 - Generuoti vardus, pavardes ir pažymius",
    "4 - Nuskaityti duomenis iš failo",
    "5 - Įrašyti duomenis į failą",
    "6 - Testuoti duomenų įvedimą į programą",
    "7 - Testuoti duomenų išvedimą",
    "8 - Testuoti duomenų apdorojimą",
    "9 - Vykdyti nulintąją konteinerių testavimo strategiją",
    "10 -  Vykdyti pirmąją konteinerių testavimo strategiją",
    "11 - Vykdyti antrąją konteinerių testavimo strategiją",
    "12 - Baigti darbą"
}};

const std::array<MeniuEilute, 7> RIKIAVIMO_MENIU = {{
    "Pasirinkite, pagal ką norite rikiuoti studentus:",
    "1 - vardą didėjančia tvarka (A-Ž)",
    "2 - vardą mažėjančia tvarka (Ž-A)",
    "3 - pavardę didėjančia tvarka (A-Ž)",
    "4 - pavardę mažėjančia tvarka (Ž-A)",
    "5 - galutinį pažymį didėjančia tvarka (1-10)",
    "6 - galutinį pažymį mažėjančia tvarka (10-1)"
}};

const std::array<MeniuEilute, 4> RIKIAVIMO_MENIU_TIK_DIDEJANCIAI = {{
    "Pasirinkite, pagal ką norite rikiuoti studentus:",
    "1 - vardą didėjančia tvarka (A-Ž)",
    "2 - pavardę didėjančia tvarka (A-Ž)",
    "3 - galutinį pažymį didėjančia tvarka (1-10)"
}};

const std::array<MeniuEilute, 7> PAZANGIU_RIKIAVIMO_MENIU = {{
    "Pasirinkite, pagal ką norite rikiuoti pažangius studentus:",
    "1 - vardą didėjančia tvarka (A-Ž)",
    "2 - vardą mažėjančia tvarka (Ž-A)",
    "3 - pavardę didėjančia tvarka (A-Ž)",
    "4 - pavardę mažėjančia tvarka (Ž-A)",
    "5 - galutinį pažymį didėjančia tvarka (1-10)",
    "6 - galutinį pažymį mažėjančia tvarka (10-1)"
}};

const std::array<MeniuEilute, 7> SILPNU_RIKIAVIMO_MENIU = {{
    "Pasirinkite, pagal ką norite rikiuoti silpnus studentus:",
    "1 - vardą didėjančia tvarka (A-Ž)",
    "2 - vardą mažėjančia tvarka (Ž-A)",
    "3 - pavardę didėjančia tvarka (A-Ž)",
    "4 - pavardę mažėjančia tvarka (Ž-A)",
    "5 - galutinį pažymį didėjančia tvarka (1-10)",
    "6 - galutinį pažymį mažėjančia tvarka (10-1)"
}};

const std::array<MeniuEilute, 3> ISVEDIMO_MENIU = {{
    "Pasirinkite, kaip norite išvesti duomenis:",
    "1 - į terminalą",
    "2 - į failą"
}};

const std::array<MeniuEilute, 6> ISVEDIMO_I_FAILA_MENIU = {{
    "Pasirinkite, kiek studentų norite sugeneruoti:",
    "1 - 1000",
    "2 - 10000",
    "3 - 100000",
    "4 - 1000000",
    "5 - 10000000"
}};