#include "ProgramosValdiklis.h"
#include "IvestiesServisas.h"
#include "IsvestiesServisas.h"
#include "FailuServisas.h"
#include "StudentuGeneratorius.h"
#include "BenchmarkService.h"
#include "ReferenceData.h"
#include "MenuDefinitions.h"

ProgramosValdiklis::ProgramosValdiklis(
    IvestiesServisas& ivestis,
    IsvestiesServisas& isvestis,
    FailuServisas& failai,
    StudentuGeneratorius& generatorius,
    BenchmarkService& benchmarkai,
    ReferenceData& referenceData
)
    : ivestis_(ivestis),
      isvestis_(isvestis),
      failai_(failai),
      generatorius_(generatorius),
      benchmarkai_(benchmarkai),
      referenceData_(referenceData) {}

void ProgramosValdiklis::paleisti() {
    int pasirinkimas = 0;
    while (ivestis_.nuskaitytiPagrindinioMeniuPasirinkima(PAGRINDINIS_MENIU, pasirinkimas)) {
        if (pasirinkimas == 13) return;
        vykdytiPasirinkima(pasirinkimas);
    }
}

void ProgramosValdiklis::vykdytiPasirinkima(int pasirinkimas) {
    switch (pasirinkimas) {
        case 1:
            vykdytiStudentuIvedima(false);
            break;
        case 2:
            vykdytiStudentuIvedima(true);
            break;
        case 3:
            vykdytiPilnaGeneravima();
            break;
        case 4:
            vykdytiNuskaitymaIsFailo();
            break;
        case 5:
            vykdytiIrasymaIFaila();
            break;
        case 6:
            vykdytiIvedimoTestavima();
            break;
        case 7:
            vykdytiIsvedimoTestavima();
            break;
        case 8:
            vykdytiDuomenuApdorojimoTestavima();
            break;
        case 9:
            vykdytiNulintajaKonteineriuTestavimoStrategija();
            break;
        case 10:
            vykdytiPirmajaKonteineriuTestavimoStrategija();
            break;
        case 11:
            vykdytiAntrajaKonteineriuTestavimoStrategija();
            break;
        case 12:
            vykdytiTreciajaKonteineriuTestavimoStrategija();
            break;
        default:
            break;
    }
}