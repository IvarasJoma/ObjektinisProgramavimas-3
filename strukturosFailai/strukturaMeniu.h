#ifndef STRUKTURAMENIU_H
#define STRUKTURAMENIU_H

#include <array>
#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../strukturosFailai/strukturaIvestis.h"

/**
 * @file strukturaMeniu.h
 * @brief Programos meniu konstantos ir meniu pasirinkimų nuskaitymo funkcijos.
 */

/** @brief Meniu eilutės tipas. */
using MeniuEilute = std::string_view;

/** @brief Pagrindinio programos meniu eilutės. */
extern const std::array<MeniuEilute, 15> PAGRINDINIS_MENIU;

/** @brief Bendro rikiavimo meniu eilutės. */
extern const std::array<MeniuEilute, 7> RIKIAVIMO_MENIU;

/** @brief Rikiavimo tik didėjančia tvarka meniu eilutės. */
extern const std::array<MeniuEilute, 4> RIKIAVIMO_MENIU_TIK_DIDEJANCIAI;

/** @brief Pažangių studentų rikiavimo meniu eilutės. */
extern const std::array<MeniuEilute, 7> PAZANGIU_RIKIAVIMO_MENIU;

/** @brief Silpnų studentų rikiavimo meniu eilutės. */
extern const std::array<MeniuEilute, 7> SILPNU_RIKIAVIMO_MENIU;

/** @brief Išvedimo būdų meniu eilutės. */
extern const std::array<MeniuEilute, 3> ISVEDIMO_MENIU;

/** @brief Išvedimo į failą meniu eilutės. */
extern const std::array<MeniuEilute, 6> ISVEDIMO_I_FAILA_MENIU;

/**
 * @brief Nuskaito pasirinkimą iš statinio meniu masyvo.
 *
 * Funkcija kartoja įvestį tol, kol naudotojas įveda korektišką pasirinkimą.
 *
 * @tparam N Meniu eilučių kiekis.
 * @param eilutes Meniu eilučių masyvas.
 * @return Pasirinkto meniu punkto numeris.
 */
template <std::size_t N>
int nuskaitytiMeniuPasirinkima(const std::array<std::string_view, N>& eilutes) {
    while (true) {
        try {
            std::cout << std::string(98, '-') << "\n";
            for (const auto& eilute : eilutes) std::cout << eilute << "\n";
            std::cout << std::string(98, '-') << "\n";
            std::cout << "Pasirinkite programos eigą: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            int meniu = 0;
            const int maxMeniu = static_cast<int>(eilutes.size()) - 1;
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, meniu);
            if (meniu < 1 || meniu > maxMeniu) throw std::out_of_range("Pasirinkimas turi būti nuo 1 iki " + std::to_string(maxMeniu) + ".");
            return meniu;
        } catch (const std::exception& e) {
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

/**
 * @brief Sugeneruoja failų nuskaitymo meniu pagal kataloge esančius tekstinius failus.
 * @param katalogas Katalogas, kuriame ieškoma tekstinių failų.
 * @return Meniu eilučių vektorius.
 */
std::vector<std::string> gautiNuskaitymoMeniu(const std::string& katalogas);

/**
 * @brief Nuskaito pagrindinio meniu pasirinkimą iš statinio meniu masyvo.
 *
 * Funkcija kartoja įvestį tol, kol naudotojas įveda korektišką pasirinkimą.
 *
 * @tparam N Meniu eilučių kiekis.
 * @param eilutes Meniu eilučių masyvas.
 * @param pasirinkimas Kintamasis, į kurį įrašomas pasirinkimas.
 * @return `true`, jei pasirinkimas nuskaitytas sėkmingai.
 */
template <std::size_t N>
bool nuskaitytiPagrindinioMeniuPasirinkima(const std::array<std::string_view, N>& eilutes, int& pasirinkimas) {
    const int didziausiasPasirinkimas = static_cast<int>(N) - 1;
    while (true) {
        try {
            std::cout << std::string(98, '-') << '\n';
            for (const auto& eilute : eilutes) {
                std::cout << eilute << '\n';
            }
            std::cout << std::string(98, '-') << '\n';
            std::cout << "Pasirinkite programos eigą: ";
            const std::string ivestis = saugiaiNuskaitytiEilute();
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, pasirinkimas);
            if (pasirinkimas < 1 || pasirinkimas > didziausiasPasirinkimas) throw std::out_of_range( "Pasirinkimas turi būti nuo 1 iki " + std::to_string(didziausiasPasirinkimas) + ".");
            return true;
        } catch (const std::exception& klaida) {
            std::cout << "Klaida: " << klaida.what() << '\n';
        }
    }
}

/**
 * @brief Nuskaito pasirinkimą iš dinaminio meniu eilučių vektoriaus.
 * @param eilutes Meniu eilučių vektorius.
 * @return Pasirinkto meniu punkto numeris.
 */
inline int nuskaitytiMeniuPasirinkima(const std::vector<std::string>& eilutes) {
    while (true) {
        try {
            std::cout << std::string(98, '-') << "\n";
            for (const auto& eilute : eilutes) { std::cout << eilute << "\n";}
            std::cout << std::string(98, '-') << "\n";
            std::cout << "Pasirinkite programos eigą: ";
            std::string ivestis = saugiaiNuskaitytiEilute();
            int meniu = 0;
            const int maxMeniu = static_cast<int>(eilutes.size()) - 1;
            tikrintiIvesti(ivestis);
            nuskaitytiSveikajiSkaiciu(ivestis, meniu);
            if (meniu < 1 || meniu > maxMeniu) throw std::out_of_range("Pasirinkimas turi būti nuo 1 iki " + std::to_string(maxMeniu) + ".");
            return meniu;
        } catch (const std::exception& e) {
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}

#endif