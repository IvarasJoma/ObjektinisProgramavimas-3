#include <iostream>
#include <string>
#include <vector>

class Studentas {
    private:
        std::string Vardas, Pavarde;
        std::vector<int> namuDarbuTarpiniaiRezultatai;
        int egzaminoRezultatas = 0;
        double galutinisRezultatas = 0.0;
    public:
        Studentas() = default;
        Studentas(std::istream& ivestis);
        inline const std::string& gautiVarda() const { return Vardas; }
        inline const std::string& gautiPavarde() const { return Pavarde; }
        double apskaiciuotiGalutini (double (*) (std::vector<int>)) const;
        bool Studentas::nuskaitytiStudentaIsEilutes(const char* eilute, std::size_t namuDarbuKiekis);
};