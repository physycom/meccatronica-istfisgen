# `erf` tutorial

Questa cartella contiene un esempio di come utilizzare la funzione [`erf`](https://en.cppreference.com/w/cpp/numeric/math/erf) per calcolare le probabilità associate alla [distribuzione normale (o gaussiana)](https://en.wikipedia.org/wiki/Normal_distribution). Sono presenti i sorgenti:
- [`erf_tutorial.c`](erf_tutorial.c) (linguaggio `C`)
- [`erf_tutorial.cpp`](erf_tutorial.cpp) (linguaggio `c++`)

## Compilazione ed esecuzione

### Online
Sono disponibili siti che offrono compilazione/esecuzione da browser, ad esempio [rextester.com](https://rextester.com/l/c_online_compiler_gcc) o [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler).

### Locale
Entrare nel merito delle specifiche _toolchain_ ([make](https://www.gnu.org/software/make/), [nmake](https://docs.microsoft.com/it-it/cpp/build/reference/running-nmake?view=msvc-160), [ninja](https://ninja-build.org/), [cmake](https://cmake.org/), [msbuild](https://docs.microsoft.com/it-it/visualstudio/msbuild/msbuild?view=vs-2019)), proprie dei vari sistemi operativi o _portable_ che siano, esula dagli scopi di questo tutorial. Pertanto ci limitiamo a riportare per comodità le linee di comando rilevanti per i compilatori più diffusi

- [GCC](https://gcc.gnu.org/) (OS di riferimento : Linux/MacOS)

Per il `c++`
```
$ g++ -std=c++11 erf_tutorial.cpp -o erf_tutorial
$ ./erf_tutorial
```
Per il `C`
```
$ gcc erf_tutorial.c -o erf_tutorialc -lm
$ ./erf_tutorialc
```

È presente inoltre un esempio di [makefile](makefile) da usare lanciando
```
$ make all
```

- [MSVC](https://visualstudio.microsoft.com/it/vs/features/cplusplus/) (OS di riferimento : Windows)

Per il `c++`
```
> cl .\erf_tutorial.cpp
> ./erf_tutorial.exe
```
Per il `C`
```
> cl .\erf_tutorial.c -o erf_tutorialc.exe
> ./erf_tutorialc.exe
```


## Output atteso
```
std::erf tutorial
P( 4.6 < x < 6 ) = 0.682689
P( 3.9 < x < 6.7 ) = 0.9545
P( 3.2 < x < 7.4 ) = 0.9973
P( 6 < x < 6.7 ) = 0.135905
P( 3.9 < x < 4.6 ) = 0.135905
P( 5.3 < x < inf ) = 0.5
P( -inf < x < inf ) = 1
```


## Considerazioni analitiche

La funzione `std::erf`, denotata <img src="https://render.githubusercontent.com/render/math?math=\text{erf}(x)"> in seguito, viene definita dallo standard come

<img src="https://render.githubusercontent.com/render/math?math=\text{erf}(x) = \frac{2}{\sqrt{\pi}}\int_0^x e^{-t^2} dx">

mentre il calcolo della probabilità associata ad una distribuzione normale, di media <img src="https://render.githubusercontent.com/render/math?math=\mu"> e deviazione standard <img src="https://render.githubusercontent.com/render/math?math=\sigma">, viene effettuato tramite

<img src="https://render.githubusercontent.com/render/math?math=\text{P}(a < x < b) = \frac{1}{\sqrt{2\pi \sigma^2}}\int_a^b e^{-\frac{(x - \mu)^2}{2 \sigma^2}} dt">

Occorre quindi riscrivere l'espressione precedente in termini di <img src="https://render.githubusercontent.com/render/math?math=\text{erf}(x)">. Il confronto tra i due integrali suggerisce di operare il cambio di variabili


<img src="https://render.githubusercontent.com/render/math?math=y = \frac{x - \mu}{\sqrt{2 \sigma^2}}">

in base al quale

<img src="https://render.githubusercontent.com/render/math?math=dy = \sqrt{2 \sigma^2} dx">

<img src="https://render.githubusercontent.com/render/math?math=x = a \rightarrow y_a = \frac{a - \mu}{\sqrt{2 \sigma^2}}">

<img src="https://render.githubusercontent.com/render/math?math=x = b \rightarrow y_b = \frac{b - \mu}{\sqrt{2 \sigma^2}}">

quindi

<img src="https://render.githubusercontent.com/render/math?math=\text{P}(a < x < b) = \frac{1}{\sqrt{\pi}} \int_{y_a}^{y_b} e^{-y^2} dy = \frac{1}{\sqrt{\pi}} [ \int_{0}^{y_b} e^{-y^2} dy - \int_{0}^{y_a} e^{-y^2} dy ] =">

<img src="https://render.githubusercontent.com/render/math?math==\frac{1}{2} [ \frac{2}{\sqrt{\pi}} \int_{0}^{y_b} e^{-y^2} dy - \frac{2}{\sqrt{\pi}} \int_{0}^{y_a} e^{-y^2} dy ] = \frac{1}{2} [ \text{erf}(y_b) - \text{erf}(y_a) ]">

