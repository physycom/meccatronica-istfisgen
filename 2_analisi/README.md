# Analisi degli errori

Questa cartella contiene un esempio di implementazione dell'analisi da effettuare nella risoluzione de [Esecizio 1 - Lezione 7](https://virtuale.unibo.it/mod/resource/view.php?id=352271). Sono presenti i sorgenti:
- [`analisi_errori.c`](analisi_errori.c) (linguaggio `C`)
- [`analisi_errori.cpp`](analisi_errori.cpp) (linguaggio `c++`)

## Compilazione ed esecuzione

Valgono le considerazioni che trovate [qui](1_erf/README.md).

## Output atteso
```
**** Original sample :
Ndata                        : 30
Mean                         : 5.25333
Variance                     : 0.117156
Standard deviation           : 0.34228
Corrected variance           : 0.121195
Corrected standard deviation : 0.348131

**** Chauvenet rule :
Data 0 value 5.5 t 0.708545 chauvenet 14.3582 OK
Data 1 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 2 value 5.5 t 0.708545 chauvenet 14.3582 OK
Data 3 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 4 value 5.5 t 0.708545 chauvenet 14.3582 OK
Data 5 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 6 value 5.1 t 0.440447 chauvenet 19.7884 OK
Data 7 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 8 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 9 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 10 value 5.6 t 0.995793 chauvenet 9.58052 OK
Data 11 value 5.1 t 0.440447 chauvenet 19.7884 OK
Data 12 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 13 value 5 t 0.727695 chauvenet 14.004 OK
Data 14 value 5.1 t 0.440447 chauvenet 19.7884 OK
Data 15 value 5 t 0.727695 chauvenet 14.004 OK
Data 16 value 5.5 t 0.708545 chauvenet 14.3582 OK
Data 17 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 18 value 5.4 t 0.421297 chauvenet 20.2061 OK
Data 19 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 20 value 5.7 t 1.28304 chauvenet 5.98433 OK
Data 21 value 5.1 t 0.440447 chauvenet 19.7884 OK
Data 22 value 5.5 t 0.708545 chauvenet 14.3582 OK
Data 23 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 24 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 25 value 5.2 t 0.153199 chauvenet 26.3472 OK
Data 26 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 27 value 5.7 t 1.28304 chauvenet 5.98433 OK
Data 28 value 5.3 t 0.134049 chauvenet 26.8009 OK
Data 29 value 3.7 t 4.46192 chauvenet 0.000243688 REJECTED

**** Filtered sample :
Ndata                        : 29
Mean                         : 5.3069
Variance                     : 0.0351249
Standard deviation           : 0.187416
Corrected variance           : 0.0363793
Corrected standard deviation : 0.190734
Total error                  : 0.106087
Best value                   : t_best = 5.31 +- 0.11
```