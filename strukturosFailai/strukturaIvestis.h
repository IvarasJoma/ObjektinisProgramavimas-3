#ifndef STRUKTURAIVESTIS_H
#define STRUKTURAIVESTIS_H

#include <vector>
#include <string>
#include "../Studentas.h"
#include "../strukturosFailai/Failai.h"

/**
 * @file strukturaIvestis.h
 * @brief Funkcijos naudotojo įvesties nuskaitymui, tikrinimui ir apdorojimui.
 */

/**
 * @brief Nuskaito namų darbų pažymius iš naudotojo.
 * @param namuDarbuPazymiai Vektorius, į kurį įrašomi pažymiai.
 * @param maksimalusNDKiekis Maksimalus leidžiamas namų darbų kiekis.
 */
void nuskaitytiNamuDarbuPazymius(std::vector<int>& namuDarbuPazymiai, int maksimalusNDKiekis);

/**
 * @brief Nuskaito meniu pasirinkimą iš tekstinių eilučių sąrašo.
 * @param eilutes Meniu eilučių vektorius.
 * @return Pasirinktas meniu punktas.
 */
int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes);

/**
 * @brief Nuskaito pagrindinio meniu pasirinkimą.
 * @param eilutes Meniu eilučių vektorius.
 * @param pasirinkimas Kintamasis, į kurį įrašomas pasirinkimas.
 * @return `true`, jei pasirinkimas nuskaitytas sėkmingai.
 */
bool nuskaitytiPagrindinioMeniuPasirinkima(const std::vector<std::string>& eilutes, int& pasirinkimas);

/**
 * @brief Nuskaito neneigiamą sveikąjį skaičių.
 * @param pranesimas Įvesties pranešimas naudotojui.
 * @return Neneigiamas sveikasis skaičius.
 */
int nuskaitytiNeneigiamaSveikajiSkaiciu(const char* pranesimas);

/**
 * @brief Nuskaito teigiamą sveikąjį skaičių.
 * @param pranesimas Įvesties pranešimas naudotojui.
 * @return Teigiamas sveikasis skaičius.
 */
int nuskaitytiTeigiamaSveikajiSkaiciu(const char* pranesimas);

/**
 * @brief Nuskaito galutinio pažymio skaičiavimo metodą.
 * @return Skaičiavimo metodo simbolis.
 */
char nuskaitytiSkaiciavimoMetoda();

/**
 * @brief Nuskaito pažymį nuo 1 iki 10.
 * @param pranesimas Įvesties pranešimas naudotojui.
 * @return Pažymys intervale `[1; 10]`.
 */
int nuskaitytiPazymiNuo1iki10(const char* pranesimas);

/**
 * @brief Konvertuoja tekstinę įvestį į sveikąjį skaičių.
 * @param ivestis Tekstinė įvestis.
 * @param reiksme Kintamasis, į kurį įrašoma konvertuota reikšmė.
 */
void nuskaitytiSveikajiSkaiciu(const std::string& ivestis, int& reiksme);

/**
 * @brief Patikrina, ar įvestis yra korektiška.
 * @param ivestis Tikrinama tekstinė įvestis.
 * @throws std::exception Jei įvestis nekorektiška.
 */
void tikrintiIvesti(const std::string& ivestis);

/**
 * @brief Nuskaito vardą arba pavardę ir pritaiko nurodytą tvarkymo funkciją.
 * @param ivestiesPranesimas Pranešimas naudotojui.
 * @param tvarkyti Funkcija vardui arba pavardei tvarkyti.
 * @param klaidosPranesimas Klaidos pranešimas neteisingos įvesties atveju.
 * @return Sutvarkytas vardas arba pavardė.
 */
std::string nuskaitytiVardaArPavarde(
    const char* ivestiesPranesimas,
    void(*tvarkyti)(std::string&),
    const char* klaidosPranesimas
);

/**
 * @brief Paklausia naudotojo, ar pridėti dar vieną studentą.
 * @return `true`, jei naudotojas patvirtina naujo studento pridėjimą.
 */
bool patvirtintiNaujoStudentoPridejima();

/**
 * @brief Vykdo studentų įvedimo procesą.
 * @param generuotiPazymius Nurodo, ar pažymius generuoti automatiškai.
 */
void vykdytiStudentuIvedima(bool generuotiPazymius);

/**
 * @brief Vykdo pilną studentų generavimo scenarijų.
 * @param failai Vardų ir pavardžių failų duomenys.
 */
void vykdytiPilnaGeneravima(Failai& failai);

/**
 * @brief Sutvarko vardo įvestį.
 * @param ivestis Tvarkoma vardo eilutė.
 */
void tvarkytiVarda(std::string& ivestis);

/**
 * @brief Sutvarko pavardės įvestį.
 * @param ivestis Tvarkoma pavardės eilutė.
 */
void tvarkytiPavarde(std::string& ivestis);

/**
 * @brief Saugiai nuskaito vieną eilutę iš standartinės įvesties.
 * @return Nuskaityta eilutė.
 */
std::string saugiaiNuskaitytiEilute();

/**
 * @brief Parenka pažangių ir silpnų studentų rikiavimo būdus.
 * @param pasirinkimasRikiavimoPazangiu Pažangių studentų rikiavimo pasirinkimas.
 * @param pasirinkimasRikiavimoSilpnu Silpnų studentų rikiavimo pasirinkimas.
 */
void parinktiRikiavimoBudus(
    int& pasirinkimasRikiavimoPazangiu,
    int& pasirinkimasRikiavimoSilpnu
);

/**
 * @brief Suformuoja studento įvesties eilutę iš atskirų laukų.
 * @param vardas Studento vardas.
 * @param pavarde Studento pavardė.
 * @param namuDarbai Namų darbų pažymių vektorius.
 * @param egzaminoPazymys Egzamino pažymys.
 * @return Suformuota studento duomenų eilutė.
 */
std::string suformuotiStudentoIvestiesEilute(
    const std::string& vardas,
    const std::string& pavarde,
    const std::vector<int>& namuDarbai,
    int egzaminoPazymys
);

/**
 * @brief Sukuria studentą iš tekstinės eilutės naudojant įvesties operatorių.
 * @param eilute Studento duomenų eilutė.
 * @return Sukurtas @ref Studentas objektas.
 */
Studentas sukurtiStudentaIsEilutesPerOperatoriu(const std::string& eilute);

#endif