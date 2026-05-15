#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include "Zmogus.h"
#include "Vector.h"
#include "StudManAPI.h"

/**
 * @file Studentas.h
 * @brief Studentą aprašanti klasė, paveldinti bazinę @ref Zmogus klasę.
 *
 * Šiame faile aprašoma @ref Studentas klasė, kuri saugo studento vardą,
 * pavardę, egzamino pažymį, namų darbų pažymius ir galutinį pažymį.
 * Taip pat aprašomi įvesties, išvesties, kopijavimo ir perkėlimo operatoriai.
 */

/**
 * @class Studentas
 * @brief Saugo vieno studento duomenis ir leidžia apskaičiuoti galutinį pažymį.
 *
 * Klasė paveldi abstrakčią bazinę klasę @ref Zmogus. Ji realizuoja vardo ir
 * pavardės gavimo metodus, saugo pažymių informaciją ir pateikia metodus
 * studento duomenims keisti bei galutiniam pažymiui apskaičiuoti.
 */
class STUDMAN_API Studentas : public Zmogus {
private:
    /** @brief Studento egzamino pažymys. */
    int examGrade_;

    /** @brief Studento namų darbų pažymių sąrašas. */
    Vector<int> homeworkGrades_;

    /** @brief Studento galutinis pažymys. */
    double finalGrade_;
public:
    public:
    /**
     * @brief Nurodo, ar destruktorius turi spausdinti informacinį pranešimą.
     */
    static bool arSpausdintiDestruktoriu;

    /**
     * @brief Numatytasis konstruktorius.
     *
     * Sukuria tuščią studentą su nuliniu egzamino ir galutiniu pažymiu.
     */
    Studentas() : Zmogus(), examGrade_(0), finalGrade_(0) {}

    /**
     * @brief Konstruktorius su visais pagrindiniais studento duomenimis.
     * @param name Studento vardas.
     * @param surname Studento pavardė.
     * @param examGrade Egzamino pažymys.
     * @param homeworkGrades Namų darbų pažymių vektorius.
     * @param finalGrade Galutinis pažymys.
     */
    Studentas(const std::string& name,
              const std::string& surname,
              int examGrade,
              const Vector<int>& homeworkGrades,
              double finalGrade)
        : Zmogus(name, surname),
          examGrade_(examGrade),
          homeworkGrades_(homeworkGrades),
          finalGrade_(finalGrade) {}

    /**
     * @brief Sukuria studentą iš tekstinės eilutės.
     *
     * Konstruktorius naudojamas nuskaitant studentų duomenis iš failo.
     *
     * @param eilute Simbolių eilutė su studento duomenimis.
     * @param namuDarbuKiekis Namų darbų pažymių kiekis eilutėje.
     */
    Studentas(const char* eilute, std::size_t namuDarbuKiekis);

    /**
     * @brief Sukuria studentą pagal generavimo nustatymus.
     * @param generuotiPazymius Nurodo, ar pažymiai turi būti sugeneruoti automatiškai.
     * @param ndKiekis Namų darbų pažymių kiekis.
     */
    Studentas(bool generuotiPazymius, int ndKiekis);
    /**
     * @brief Destruktorius.
     *
     * Jei @ref arSpausdintiDestruktoriu reikšmė yra `true`, gali būti spausdinamas
     * informacinis pranešimas apie objekto sunaikinimą.
     */
    ~Studentas();

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kitas studento objektas, iš kurio kopijuojami duomenys.
     */
    Studentas(const Studentas& other);

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @param other Kitas studento objektas, iš kurio kopijuojami duomenys.
     * @return Nuoroda į esamą objektą.
     */
    Studentas& operator=(const Studentas& other);

    /**
     * @brief Perkėlimo konstruktorius.
     * @param other Kitas studento objektas, iš kurio perkeliami duomenys.
     */
    Studentas(Studentas&& other) noexcept;

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     * @param other Kitas studento objektas, iš kurio perkeliami duomenys.
     * @return Nuoroda į esamą objektą.
     */
    Studentas& operator=(Studentas&& other) noexcept;

    /**
     * @brief Grąžina studento vardą.
     * @return Studento vardas.
     */
    inline std::string getName() const { return name_; }

    /**
     * @brief Grąžina studento pavardę.
     * @return Studento pavardė.
     */
    inline std::string getSurname() const { return surname_; }
    /**
     * @brief Grąžina studento galutinį pažymį.
     * @return Galutinis pažymys.
     */
    inline double getFinalGrade() const { return finalGrade_; }

    /**
     * @brief Grąžina studento egzamino pažymį.
     * @return Egzamino pažymys.
     */
    inline int getExamGrade() const { return examGrade_; }

    /**
     * @brief Grąžina studento namų darbų pažymių sąrašą.
     * @return Konstantinė nuoroda į namų darbų pažymių vektorių.
     */
    inline const Vector<int>& getHomeworkGrades() const { return homeworkGrades_; }

    /**
     * @brief Apskaičiuoja studento galutinį pažymį pagal pasirinktą metodą.
     *
     * Metodas paprastai nurodo, ar galutinis pažymys skaičiuojamas pagal
     * namų darbų vidurkį, ar pagal medianą.
     *
     * @param method Skaičiavimo metodo simbolis.
     * @return Apskaičiuotas galutinis pažymys.
     */
    double calculateFinalGrade(char method) const;

    /**
     * @brief Nustato studento vardą.
     * @param name Naujas vardas.
     */
    void setName(const std::string& name) { name_ = name; }

    /**
     * @brief Nustato studento pavardę.
     * @param surname Nauja pavardė.
     */
    void setSurname(const std::string& surname) { surname_ = surname; }

    /**
     * @brief Nustato egzamino pažymį.
     * @param examGrade Naujas egzamino pažymys.
     */
    void setExamGrade(int examGrade) { examGrade_ = examGrade; }
/**
     * @brief Nustato galutinį pažymį.
     * @param finalGrade Naujas galutinis pažymys.
     */
    void setFinalGrade(double finalGrade) { finalGrade_ = finalGrade; }

    /**
     * @brief Nustato visą namų darbų pažymių sąrašą.
     * @param homeworkGrades Naujas namų darbų pažymių vektorius.
     */
    void setHomeworkGrades(const Vector<int>& homeworkGrades) {homeworkGrades_ = homeworkGrades;}

    /**
     * @brief Prideda vieną namų darbo pažymį.
     * @param grade Pridedamas pažymys.
     */
    void addHomeworkGrade(int grade) {homeworkGrades_.push_back(grade);}

    /**
     * @brief Išvalo visus namų darbų pažymius.
     */
    void clearHomeworkGrades() {homeworkGrades_.clear();}

    /**
     * @brief Rezervuoja vietą namų darbų pažymių vektoriuje.
     * @param n Rezervuojamas elementų kiekis.
     */
    void reserveHomeworkGrades(std::size_t n) {homeworkGrades_.reserve(n);}

    /**
     * @brief Išveda studento duomenis į srautą.
     * @param os Išvesties srautas.
     * @param s Studentas, kurio duomenys išvedami.
     * @return Išvesties srautas.
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);

    /**
     * @brief Nuskaito studento duomenis iš įvesties srauto.
     * @param is Įvesties srautas.
     * @param s Studentas, į kurį įrašomi duomenys.
     * @return Įvesties srautas.
     */
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

STUDMAN_API std::ostream& operator<<(std::ostream& os, const Studentas& s);
STUDMAN_API std::istream& operator>>(std::istream& is, Studentas& s);

/**
 * @struct StudentasLentelei
 * @brief Pagalbinė struktūra studento išvedimui lentelės formatu.
 *
 * Struktūra saugo konstantinę nuorodą į studentą ir naudojama specializuotam
 * išvedimo operatoriui.
 */
struct STUDMAN_API StudentasLentelei {
    /** @brief Studentas, kuris bus išvedamas lentelės formatu. */
    const Studentas& s;
};

/**
 * @brief Išveda studentą lentelės formatu.
 * @param os Išvesties srautas.
 * @param s Pagalbinė struktūra su studento nuoroda.
 * @return Išvesties srautas.
 */
STUDMAN_API std::ostream& operator<<(std::ostream& os, const StudentasLentelei& s);

#endif