#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

/**
 * @file Zmogus.h
 * @brief Abstrakti bazinė žmogaus klasė.
 *
 * Šiame faile aprašoma abstrakti bazinė klasė @ref Zmogus.
 * Ji saugo bendrus žmogaus duomenis: vardą ir pavardę.
 * Klasė skirta paveldėjimui, todėl tiesiogiai `Zmogus` objektai nekuriami.
 */

/**
 * @class Zmogus
 * @brief Abstrakti bazinė klasė žmogaus vardui ir pavardei saugoti.
 *
 * Klasė turi grynai virtualius metodus vardui ir pavardei gauti.
 * Iš jos paveldi konkretesnės klasės, pavyzdžiui, @ref Studentas.
 */
class Zmogus {
protected:
    /**
     * @brief Žmogaus vardas.
     */
    std::string name_;

    /**
     * @brief Žmogaus pavardė.
     */
    std::string surname_;

public:
    /**
     * @brief Numatytasis konstruktorius.
     *
     * Sukuria tuščią bazinės klasės objektą.
     */
    Zmogus() = default;

    /**
     * @brief Konstruktorius su vardu ir pavarde.
     *
     * @param name Žmogaus vardas.
     * @param surname Žmogaus pavardė.
     */
    Zmogus(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}

    /**
     * @brief Grynas virtualus destruktorius.
     *
     * Destruktorius yra virtualus, kad išvestinių klasių objektai būtų
     * korektiškai sunaikinami per bazinės klasės rodyklę.
     *
     * Nors destruktorius yra grynai virtualus, jis vis tiek turi turėti
     * apibrėžimą, kuris pateiktas žemiau kaip `inline`.
     */
    virtual ~Zmogus() = 0;

    /**
     * @brief Grąžina žmogaus vardą.
     *
     * @return Žmogaus vardas.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Grąžina žmogaus pavardę.
     *
     * @return Žmogaus pavardė.
     */
    virtual std::string getSurname() const = 0;
};

/**
 * @brief Gryno virtualaus destruktoriaus apibrėžimas.
 *
 * Grynas virtualus destruktorius privalo turėti apibrėžimą, nes jis vis tiek
 * iškviečiamas naikinant išvestinės klasės objektą.
 */
inline Zmogus::~Zmogus() {}

#endif