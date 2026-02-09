#include "struktura.h"

int main() {
    std::vector<Studentas> studentuSarasas;
    int pazymiuSkaicius;
    int studentuSkaicius;

    std::cout << "Iveskite studentų skaičių: ";
    std::cin >> studentuSkaicius;
    for (int i = 0; i < studentuSkaicius; i++){
        Studentas studentas;
        std::cout << "Iveskite studento vardą: ";
        std::cin >> studentas.Vardas;
        std::cout << "Iveskite studento pavardę: ";
        std::cin >> studentas.Pavarde;
        std::cout << "Iveskite studento namų darbų pažymių skaičių: ";
        std::cin >> pazymiuSkaicius;
        std::cout << "Iveskite studento namų darbų pažymius: ";
        for (int j = 0; j < pazymiuSkaicius; j++) {
            int ivedamasPazymys;
            std::cin >> ivedamasPazymys;
            studentas.namuDarbuTarpiniaiRezultatai.push_back(ivedamasPazymys);
        }
        std::cout << "Iveskite studento egzamino pažymį: ";
        std::cin >> studentas.egzaminoRezultatas;
        studentuSarasas.push_back(studentas);
    }
    return 0;
}