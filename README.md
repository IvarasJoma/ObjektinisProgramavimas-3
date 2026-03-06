# ObjektinisProgramavimas
VU ISI objektinio programavimo projektas

## Programos veikimo laiko analizė

Programos veikimo laikas buvo matuojamas naudojant skirtingo dydžio duomenų failus. 
Testavimas atliktas su trimis duomenų rinkiniais: **10 000**, **100 000** ir **1 000 000** studentų įrašų.
Kiekvienas testas vykdytas 3 kartus, pateikiamas vidutinis rezultatas.

| Studentų kiekis | Nuskaitymas (s) | Skaičiavimas (s) | Rikiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|-----------------|-----------------|------------------|----------------|---------------|--------------------|
| 10 000          | 0.0038          | 0.0025           | 0.00056        | 0.0065        | 0.0134             |
| 100 000         | 0.0287          | 0.0162           | 0.00276        | 0.0381        | 0.0858             |
| 1 000 000       | 0.1124          | 0.0545           | 0.0250         | 0.3087        | 0.5006             |