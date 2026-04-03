<h2>Programos aprašymas</h2>
Programa yra skirta studentų (jų akademinių pasiekimų) duomenų įvedimui, apdorojimui ir išvedimui.
<h4><b> Programos funkcijos: </b> </h4>
<ol>
    <li>Įvesti visus studentų duomenis ranka</li>
    <li>Įvesti studentų vardus, pavardes, atsitiktine tvarka generuoti pažymius</li>
    <li>Atsitiktinai generuoti studentų vardus, pavardes ir pažymius</li>
    <li>Nuskaityti duomenis iš failo</li>
    <li>Generuoti pasirinktino ilgio failą su atsitiktinai sugeneruotais studentų duomenimis</li>
</ol>

<p>Idant būtų galima išmatuoti programos veikimo laiko priklausomybę nuo naudojamų konteinerių (<b>vector, list, deque</b>) skirstant studentus į pažangius ir nepažangius, buvo pasitelktos trys strategijos:</p>
<ol>
    <li> Bendro studentų konteinerio (<b>vector, list ir deque tipų</b>) išskaidymas į du naujai sukurtus to paties tipo konteinerius: pažangius ir nepažangius.</li>
    <li> Bendro studentų konteinerio (<b>vector, list ir deque</b>) išskaidymas panaudojant tik nepažangių mokinių konteinerį (jei studentas nepažangus, jis perkeliamas į naują konteinerį, iš senojo ištrinamas).</li>
    <li>Bendro studentų konteinerio (<b>vector, list ir deque</b>) išskaidant optimizuojant antrąją strategiją.</li>
</ol>

<h2>Naudojimosi instrukcija</h2>
<ol>
    <li>Parsisiųsti ir įsirašyti <a href="https://gnuwin32.sourceforge.net/packages/make.htm">make</a> programinį paketą (tik jei naudojate Windows OS).</li>
    <li>Atsidaryti savo OS terminalą</li>
    <li>Klonuoti programos repozitoriją</li>
    git clone https://github.com/IvarasJoma/ObjektinisProgramavimas.git
 <li>Terminale rašyti žemiau esančią komandą, norint paleisti programą
 <pre><code>make run</code></pre>
</ol>

<h2>Testavimo apžvalga</h2>

Testavimas buvo vykdytas šioje sisteminėje aplinkoje:

| Kompiuteris |  Macbook M3 Pro |
|---------------------|------|
| Procesorius | M3 Pro |
| Branduolių skaičius | 11 |
| Operatyvios atminties talpa | 18 GB LPDDR5-6400 |
| SSD talpa ir greitis | 512GB, 6200 MB/s Write, 4310 MB/s Read |

## Konteinerių našumo palyginimas

| Įrašų kiekis | Konteineris | Nuskaitymas (s) | Skaičiavimas (s) | Rikiavimas (s) | Skirstymas (s) | Bendras (s) |
| ------------ | ----------- | --------------- | ---------------- | -------------- | -------------- | ----------- |
| 10000000     | Vector      | 1.46158         | 0.81569         | 0.260966       | 0.135772       | 2.67401     |
| 10000000     | List        | 1.40333         | 0.842376         | 6.3936         | 1.12494        | 9.76424     |
| 10000000     | Deque       | 1.24412         | 0.769542         | 0.281077        | 0.0778298      | 2.37257        |
| 1000000      | Vector      | 0.142898        | 0.0756094        | 0.0258632      | 0.0129843     | 0.257355    |
| 1000000      | List        | 0.134814        | 0.0777371        | 0.304793       | 0.0994318       | 0.616776    |
| 1000000      | Deque       | 0.124166        | 0.0769192        | 0.0281017      | 0.00629896      | 0.235486    |
| 100000       | Vector      | 0.0224329       | 0.00941713        | 0.00296424     | 0.00087957    | 0.0356938   |
| 100000       | List        | 0.0136738       | 0.00784851       | 0.00896157      | 0.0016645     | 0.0321484   |
| 100000       | Deque       | 0.0127949        | 0.0077215       | 0.00275661     | 0.000633028    | 0.023906   |
| 10000        | Vector      | 0.00453481       | 0.0019966      | 0.000801319    | 0.000306847    | 0.00763957   |
| 10000        | List        | 0.00266796      | 0.00149164      | 0.00113862    | 0.000238917    | 0.00553714  |
| 10000        | Deque       | 0.00189549      | 0.00113997      | 0.000420417    | 7.90417e-05    | 0.00353492  |
| 1000         | Vector      | 0.000993028      | 0.000160139      | 6.36527e-05     | 1.68473e-05     | 0.00123367   |
| 1000         | List        | 0.000450695     | 0.000149583      | 6.34443e-05    | 3.52083e-05    | 0.000698931 |
| 1000         | Deque       | 0.000581     | 0.000214389      | 7.65277e-05    | 1.73057e-05    | 0.000889222 |

## Pirmos strategijos tyrimo rezultatai

| Įrašų kiekis | Konteineris | Bendras (s) |
| ------------ | ----------- | ----------- |
| 10000000     | Vector      | 3.14749     |
| 10000000     | List      | 10.1786     |
| 10000000     | Deque      | 2.94208     |
| 1000000     | Vector      | 0.294517     |
| 1000000     | List      | 0.640355     |
| 1000000     | Deque      | 0.272934     |
| 100000     | Vector      | 0.036173     |
| 100000     | List      | 0.0341028     |
| 100000     | Deque      | 0.0247597     |
| 10000     | Vector      | 0.00635689     |
| 10000     | List      | 0.00606537     |
| 10000     | Deque      | 0.00382706     |
| 1000     | Vector      | 0.00123278     |
| 1000     | List      | 0.00101369     |
| 1000     | Deque      | 0.000924639     |

## Antros strategijos tyrimo rezultatai

| Įrašų kiekis | Konteineris | Bendras (s) |
| ------------ | ----------- | ----------- |
| 10000000     | Vector      | 2.82279     |
| 10000000     | List      | 11.8649     |
| 10000000     | Deque      | 2.35069     |
| 1000000     | Vector      | 0.257035     |
| 1000000     | List      | 0.81136     |
| 1000000     | Deque      | 0.233478     |
| 100000     | Vector      | 0.0333414    |
| 100000     | List      | 0.0332578     |
| 100000     | Deque      | 0.0233894     |
| 10000     | Vector      | 0.006686     |
| 10000     | List      | 0.00513514     |
| 10000     | Deque      | 0.00340925     |
| 1000     | Vector      | 0.0009305     |
| 1000     | List      | 0.000728791     |
| 1000     | Deque      | 0.000778236     |

## Trečios strategijos tyrimo rezultatai

| Įrašų kiekis | Konteineris | Bendras (s) |
| ------------ | ----------- | ----------- |
| 10000000     | Vector      | 2.36889     |
| 10000000     | List      | 2.55432    |
| 10000000     | Deque      | 2.28066     |
| 1000000     | Vector      | 0.22829    |
| 1000000     | List      | 0.258182     |
| 1000000     | Deque      | 0.212768     |
| 100000     | Vector      | 0.0314771    |
| 100000     | List      | 0.0230683     |
| 100000     | Deque      | 0.0213107     |
| 10000     | Vector      | 0.00756633     |
| 10000     | List      | 0.00307204     |
| 10000     | Deque      | 0.00224785     |
| 1000     | Vector      | 0.0011071     |
| 1000     | List      | 0.000699736     |
| 1000     | Deque      | 0.000653847     |

## Struktūrų ir objektų spartos palyginimo rezultatai

| Versija | Optimizavimo flag'as | 100k (s) | 1M (s) | Failo dydis (KB) |
| ------- | -------------------- | -------- | ------ | ---------------- |
| struct  | O1                   | 0.0320068      |0.234589     | 318              |
| struct  | O2                   | 0.027526      | 0.228607   | 301              |
| struct  | O3                   | 0.0255881      | 0.221877    | 317              |
| class   | O1                   | 0.0347491     | 0.292031   | 214              |
| class   | O2                   | 0.0330411      | 0.290745    | 213              |
| class   | O3                   | 0.0322129      | 0.289138    | 228              |

<h2>Struktūrų ir objektų spartos palyginimo rezultatai</h2>
<p>Pateikti rezultatai rodo, kad šioje programoje struct realizacija buvo spartesnė už class visais testuotais optimizavimo lygiais – tiek su 100 tūkst., tiek su 1 mln. įrašų ji demonstravo mažesnį vykdymo laiką, o didžiausias našumas pasiektas naudojant O3 optimizaciją; tuo tarpu class versija taip pat pagerėjo didinant optimizaciją, tačiau išliko lėtesnė. Tai leidžia daryti išvadą, kad struct šiuo atveju yra efektyvesnis sprendimas laiko atžvilgiu, tikėtina dėl paprastesnės struktūros ir mažesnės abstrakcijos kainos, nors skirtumai nėra kritiniai, todėl praktikoje pasirinkimas turėtų priklausyti ir nuo kodo organizavimo bei aiškumo aspektų. Kita vertus, pastebėta, kad class realizacija generuoja mažesnio dydžio vykdomuosius failus (pvz., su O2: 213 KB prieš 301 KB), todėl ji gali būti palankesnė, kai svarbus programos kompaktiškumas.</p>


<h2>Programos testavimo nuotraukos</h2>
<img width="695" height="1259" alt="image" src="https://github.com/user-attachments/assets/2821790d-aef5-4263-aa79-571a808f9db3" />
<img width="695" height="1348" alt="image" src="https://github.com/user-attachments/assets/08e49c65-879d-47d0-9b17-cde5ab35d04b" />
<img width="695" height="1348" alt="image" src="https://github.com/user-attachments/assets/1604353b-4e80-429e-ab38-ababd5650b09" />

<h2>Išvados</h2>
<ol>
    <li>Konteinerių tyrime std::deque ir std::vector buvo greičiausi konteineriai.</li>
    <li>Studentų skaidymo į du naujus konteinerius veikė lėčiau nei perkėlimo ir ištrynimo strategija. </li>
</ol>
