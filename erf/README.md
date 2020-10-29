# `std::erf` tutorial

Questa cartella contiene un semplice esempio in `c++` di come utilizzare la funzione [`std::erf`](https://en.cppreference.com/w/cpp/numeric/math/erf) per calcolare le probabilità associate alla [distribuzione normale (o gaussiana)](https://en.wikipedia.org/wiki/Normal_distribution)

## Compilazione ed esecuzione

Entrare nel merito delle specifiche _toolchain_ ([make](https://www.gnu.org/software/make/), [nmake](https://docs.microsoft.com/it-it/cpp/build/reference/running-nmake?view=msvc-160), [ninja](https://ninja-build.org/), [cmake](https://cmake.org/), [msbuild](https://docs.microsoft.com/it-it/visualstudio/msbuild/msbuild?view=vs-2019)), proprie dei vari sistemi operativi o _portable_ che siano, esula dagli scopi di questo tutorial. Pertanto ci limitiamo a riportare per comodità le linee di comando rilevanti per i compilatori più diffusi

- [GCC](https://gcc.gnu.org/) (OS di riferimento : Linux/MacOS)
```
$ g++ -std=c++11 erf_tutorial.cpp -o erf_tutorial
$ ./erf_tutorial
```
per il quale è presente un esempio di [makefile](makefile)

- [MSVC](https://visualstudio.microsoft.com/it/vs/features/cplusplus/) (OS di riferimento : Windows)
```
> cl .\erf_tutorial.cpp
> ./erf_tutorial.exe
```

## Considerazioni analitiche

La funzione `std::erf`, denotata $\text{erf}(x)$ in seguito, viene definita dallo standard come

$\text{erf}(x) = \frac{2}{\sqrt{\pi}}\int_0^x e^{-t^2} dt$

mentre il calcolo della probabilità associata ad una distribuzione normale, di media $\mu$ e deviazione standard $\sigma$, viene effettuato tramite

$\text{P}(a < x < b) = \frac{1}{\sqrt{2\pi \sigma^2}}\int_a^b e^{-\frac{(x - \mu)^2}{2 \sigma^2}} dt$

Occorre quindi riscrivere l'espressione precedente in termini di $\text{erf}(x)$. Il confronto tra i due integrali suggerisce di operare il cambio di variabili

$y = \frac{x - \mu}{\sqrt{2 \sigma^2}}$

in base al quale

$dy = \sqrt{2 \sigma^2} dx$

$x = a -> y_a = \frac{a - \mu}{\sqrt{2 \sigma^2}}$

$y_b = \frac{b - \mu}{\sqrt{2 \sigma^2}}$

quindi

$\text{P}(a < x < b) = \frac{1}{\sqrt{\pi}} \int_{y_a}^{y_b} e^{-y^2} dy = \frac{1}{\sqrt{\pi}} [ \int_{0}^{y_b} e^{-y^2} dy - \int_{0}^{y_a} e^{-y^2} dy ] =$

$=\frac{1}{2} [ \frac{2}{\sqrt{\pi}} \int_{0}^{y_b} e^{-y^2} dy - \frac{2}{\sqrt{\pi}} \int_{0}^{y_a} e^{-y^2} dy ] = \frac{1}{2} [ \text{erf}(y_b) - \text{erf}(y_a) ]$

