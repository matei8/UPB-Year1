# Task Bonus - Instructiuni speciale: RDRAND / RDSEED, RDTSC

## RDRAND si RDSEED

Procesoarele din familia x86 pot avea (majoritatea au) suport pentru generarea de numere aleatorii.
Numerele aleatorii sunt foarte importante, mai ales in securitate, iar generarea unor numere aleatorii care nu pot fi ghicite a fost si este un subiect relevant in Computer Science.
Inainte de aparitia acestor instructiuni, numerele aleatoare erau generate din software, bazandu-se pe entropia din sistem.
Entropia este cantitatea de informatie aleatoare (nu poate fi determinata matematic usor) din mediu.
La entropie contribuie chestii precum temperatura sistemului, frecventa procesorului la un moment dat, adrese din cache unde se fac scrieri, etc.

`RDRAND` si `RDSEED` ascund tot procesul de a determina entopia si a o folosi pentru a obtine un numar in spatele unei instructiuni de procesor.
Diferenta dintre cele 2 este cat de sigur poate fi programatorul ca acel numar aleator nu poate fi ghicit.
`RDRAND` garanteaza ca un atacator cu resurse finite nu poate ghici numarul (adica efortul depus pentru a afla numarul este extrem de mare).
`RDSEED` garanteaza ca un atacator cu resurse infinite nu poate ghici numarul.
Pe langa aceste garantii, instructiunile difera si prin durata lor de executie.
`RDSEED` dureaza mai mult si are sanse mai mari decat `RDRAND` sa intoarca un numar valid.

## RDTSC

Sistemele au intodeauna nevoie sa poata determina cat timp a trecut intre 2 evenimente.
Totusi, procesoarele din sisteme nu au notiunea de "secunda" incorporata.
Ele stiu, in schimb, numarul de cicluri de ceas de cand au fost resetate ultima oara si frecventa unui ciclu de ceas.
Acel numar de cicluri de ceas este retinut intr-un registru intern al procesorului, (Time-Stamp Counter - TSC) si poate fi citit folosind instructiunea `RDTSC`.

## Cerinta

1) Folosind instructiunile de mai sus, implementati functia `get_rand` din fisierul `bonus_timegate.asm`, care intoarce un numar aleatoriu pe 32 de biti.
Aceasta functie trebuie sa nu poata fi inspectata folosind GDB (nu trebuie sa se poata folosi GDB pentru a afla numarul aleatoriu).
In caz ca este detectat GDB-ul, functia va intoarce 0. (5p)
Pentru a putea testa automat implementarea, introduceti in cod label-ul **rdrand_here:**, fix inainte de instructiunea **rdrand** / **rdseed**.

2) Implementati un program care foloseste functia `get_rand`, pentru a obtine un secret, pe baza numarului aleatoriu generat si a unui sir constant de caractere.
Acesta poate fi un numar, un sir de caractere, etc.
Secretul trebuie sa fie generat in urma unor operatii complexe, fara a fi vizibile usor sirul constant sau numarul aleatoriu din secret. (minim 5p) 

## Precizari suplimentare
 * HINT: In assembly, instructiunile au un numar fix de cicluri de ceas, iar executia catorva instructiuni nu va varia foarte mult, ca cicluri de ceas folosite.
 Instrumentarea folosind GDB aduce un overhead semnificativ ca numar de cicluri de ceas.
 * In cazul instructiunilor `RDRAND` si `RDSEED`, validitatea numarului trebuie verificata in cod.
 In caz contrar, punctele nu vor fi acordate.
 * La cerinta a 2-a se pot da mai multe puncte, daca implementarea este inedita.
 * Cerinta a 2-a, fiind una de creativitate, nu va putea fi verificata automat.
 Verificarea se va face manual, de catre corector.
 De aceea, va trebui sa descrieti intr-un README implementarea.

## Referinte
 * [RDRAND si RDSEED](https://www.intel.com/content/dam/develop/external/us/en/documents/drng-software-implementation-guide-2-1-185467.pdf)
 * [RDTSC, pagina 547](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-2b-manual.pdf)
