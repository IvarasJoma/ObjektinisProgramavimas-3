#ifndef PROGRAMOSVALDIKLIS_H
#define PROGRAMOSVALDIKLIS_H

class IvestiesServisas;
class IsvestiesServisas;
class FailuServisas;
class StudentuGeneratorius;
class BenchmarkService;
class StatiniaiDuomenys;

class ProgramosValdiklis {
private:
    IvestiesServisas& ivestis_;
    IsvestiesServisas& isvestis_;
    FailuServisas& failai_;
    StudentuGeneratorius& generatorius_;
    BenchmarkService& benchmarkai_;
    StatiniaiDuomenys& statiniaiDuomenys_;

public:
    ProgramosValdiklis(
        IvestiesServisas& ivestis,
        IsvestiesServisas& isvestis,
        FailuServisas& failai,
        StudentuGeneratorius& generatorius,
        BenchmarkService& benchmarkai,
        StatiniaiDuomenys& statiniaiDuomenys
    );
    void paleisti();

private:
    void vykdytiPasirinkima(int pasirinkimas);
    void vykdytiStudentuIvedima(bool generuotiPazymius);
    void vykdytiPilnaGeneravima();
    void vykdytiNuskaitymaIsFailo();
    void vykdytiIrasymaIFaila();
    void vykdytiIvedimoTestavima();
    void vykdytiIsvedimoTestavima();
    void vykdytiDuomenuApdorojimoTestavima();
    void vykdytiNulintajaKonteineriuTestavimoStrategija();
    void vykdytiPirmajaKonteineriuTestavimoStrategija();
    void vykdytiAntrajaKonteineriuTestavimoStrategija();
    void vykdytiTreciajaKonteineriuTestavimoStrategija();
};

#endif