# ipv4_lpm

Prosty projekt w C++ implementujacy wyszukiwanie **Longest Prefix Match (LPM)** dla IPv4.
Program przyjmuje tablice wpisow routingu w formacie `a.b.c.d/maska` i dla zadanego adresu IPv4 znajduje najlepsze dopasowanie (najdluzsza maske).

## Cel projektu

Celem projektu jest:
- parsowanie adresow IPv4 i masek,
- walidacja wpisow sieci,
- wyszukiwanie najlepszego wpisu routingu metoda LPM.

## Wejscie programu

Program oczekuje:
-  liczby adresow sieci (domyślnie 2), konfigurowalnych makrem `ROUTING_ADDRESSES` w formacie `a.b.c.d/maska`,
- 1 adresu hosta IPv4 do wyszukania.

### Przykladowe uruchomienie

#### Dla `ROUTING_ADDRESSES=2`

```powershell
.\dist\ipv4_lpm.exe 194.168.1.0/24 10.0.0.0/8 194.168.1.123
```

#### Dla `ROUTING_ADDRESSES=4`

```powershell
.\dist\ipv4_lpm.exe 10.0.0.0/8 10.1.0.0/16 10.1.2.0/24 192.168.0.0/16 10.1.2.99
```

## Konfigurowalna liczba parametrow

Liczba adresow routingu jest konfigurowana makrem `ROUTING_ADDRESSES` (domyslnie `2`) definiowanym w pliku main.cpp i moze byc zmieniona przed kompilacja.

## Przykladowa kompilacja (Windows, MinGW + CMake)

### Kompilacja

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/ProgramData/mingw64/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/ProgramData/mingw64/mingw64/bin/g++.exe
cmake --build build
```

## Wynik

Program wypisuje:
- `Best match found: a.b.c.d/maska` gdy znaleziono najlepsze dopasowanie,
- Przyczynę błędu gdy nie można znaleźć pasujacej trasy.
