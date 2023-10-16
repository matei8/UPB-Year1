# Task Bonus - Apeluri de sistem

## Teorie

In general, orice interactiune cu I/O-ul (HDD, SSD, placa video) se poate face doar de catre sistemul de operare.
Dar in realizarea programelor, avem nevoie sa citim fisiere care se afla pe un disc, deci pot fi accesate doar de sistemul de operare.
De aceea exista apeluri de sistem, care sunt modalitatea prin care un utilizator obisnuit poate executa operatiuni privilegiate, cum ar fi citirea unui fisier de pe disc.
Printr-un apel de sistem, ii solicitam sistemului de operare sa execute o anumita operatiune si sa ne intoarca rezultatul ei.
In assembly, rezultatul apelului de sistem este pus in EAX.

Un apel de sistem presupune intreruperea sistemului de operare, folosind instructiunea speciala `int`.
`int` primeste ca parametru numarul intreruperii, care, in cazul apelurilor de sistem este 0x80.
Dupa ce primeste intreruperea, sistemul de operare se uita in registre, pentru a identifica ce fel de apel de sistem este.
Se uita in special in registrele EAX, EBX, ECX, EDX.
In EAX se afla numarul intreruperii. 
De exemplu, apelul de sistem `exit`, care termina executia unui program, foloseste valoarea 1 in EAX.

## Cerinta

Folosind apeluri de sistem, cititi continutul unui fisier text, dat ca argument functiei `replace_marco`, si inlocuiti fiecare aparitie a cuvantului "Marco" cu "Polo".
Scrieti noul continut intr-un nou fisier, dat, de asemenea, ca argument.

## Precizari
 * Task-ul va fi realizat in Assembly pe 32 de biti
 * Aveti nevoie de apelurile de sistem `sys_open`, `sys_read`, `sys_write`, `sys_close`.
 * Aceste apeluri de sistem exista si in C, sub forma unor functii cu acelasi nume (fara "sys_").
 * Atentie: aceste apeluri de sistem sunt specifice Linux. Alte sisteme de operare implementeaza alte apeluri de sistem
 * Nu aveti voie sa folositi functii externe (ex. `fgets`) pentru a deschide, inchide fisiere sau pentru a scrie sau a citi din fisiere
 * Nu e nevoie sa apelati `exit` la finalul functiei
 * Fisierele contin maxim 100 de caractere
 * In caz de eroare, apelurile de sistem din assembly intorc -ERRNO, unde ERRNO este un cod standard de eroare din Linux.


## Punctare

Task-ul valoreaza 10p.
Nu se vor acorda puncte daca citirea, scrierea, deschiderea si inchiderea fisierelor nu se face cu apeluri de sistem.

## Resurse utile

[Codurile ERRNO](https://www.thegeekstuff.com/2010/10/linux-error-codes/)
