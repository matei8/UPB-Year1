# Task Bonus - Floating Point

## Teorie

Toate procesoarele moderne au un set de instructiuni speciale, care stiu sa faca calcule in virgula mobila.
Aceste calcule sunt realizate de o componenta a procesorului, numita **Floating Point Unit** (FPU).
Instructiunile floating-point nu folosesc registre, ci doar o stiva speciala, separata de stiva normala a programului, si memoria.
Toate instructiunile de floating point actioneaza asupra varfului stivei speciale, notata `SP(0)`, impreuna cu o locatie din memorie sau elementul urmator din stiva, `SP(1)`.

O functie care intoarce o valoare float va pune acea valoare in varful stivei floating-point, pe 32 de biti.
Pe 64 de biti, valoare va fi pusa in `xmm0` (registru vectorial).

## Cerinta

Sa se scrie functia `do_math`, care primeste 3 parametri de tip float, **x**, **y** si **z** si intoarce rezultatul calculului `x * sqrt(2) + y * sin(z * PI * 1 / e)`, folosind Assembly pe 32 de biti.

## Punctare

Acest task valoreaza 15 puncte.

## Precizari

**PI** si **e** nu pot fi declarate ca variabile de voi.
Ele trebuie sa fie aflate / folosite doar prin instructiunile puse la dispozitie de FPU.

## Referinte

[https://docs.oracle.com/cd/E18752_01/html/817-5477/eoizy.html](Instructiunile FPU)
