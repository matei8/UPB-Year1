
# Cerinta 1 & 2

Pentru cerinta 1 si 2 am citit datele despre imaginea data ca input intr-o varibaila de type TImage care contine un
pointer spre fiser, numele fisierului, dar si dimensiunea acestuia. Imaginea in sine a fost cititta intr-o matrice in
care fiecare element este de type TPixel si retine 3 valori RGB. 

Dupa ce a fost creata matricea cu toti pixelii imaginii date ca input, datele din aceasta vor fi transpuse intr-un arbore
cuatrenar. Functia care face asta se numeste **getCompressionTree** si este recursiva. La fiecare apelare a functiei se 
verifica valoarea mean din submatricea de coordonate (x, y) si dimensiune size. 

Matricea se imparte diferit pentru apelarea fiecarui fiu al nodului curent astfel:
* **arbore->fiu1** se vor lua coordonatele _x, y si size / 2_ (se imparte dimensiunea curenta la doi pentru a putea avea submatrici patratice)
* **arbore->fiu2** se vor lua coordonatele _x, y + size / 2_, citind submatricea din dreapta submatricei antcedente
* **arbore->fiu3** se vor lua coordonatele _x + size / 2, y + size / 2_, citind submatricea de sub matricea citita in arbore->fiu2
* **arbore->fiu4** se vor lua coordonatele _x + size / 2, y_, citind submatricea din stanga matricei citite in arbore->fiu3

De asemenea, **inainte de citirea matricelor, se calculeaza valoarea mean**, pentru a determina daca este nevoie de
impartirea matricei curente in submatrici.

**_Numarul  de niveluri_** se face calculand maximul recursiv dintre numarul de niveluri de pe fiecare ramura.

**_Numarul frunzelor_** se calculeaza tot recursiv, atunci cand se ajunge la un nod de type frunza se incrementeaza un index.
Latura patratului cel mai mare care nu a fost divizat se calculeaza gasind nodul cel mai de sus din arbore, facand
inversul de la calcularea numarului de niveluri, de data aceasta calculand minimul de niveluri.

**_La cerinta doi_** am parcurs arborele pe level o coada de type TQueue, iar cand intalneam un nod de type 1 scriam in fisier
1 si valorile RGB corespunzatoare frunzei, iar cand era un nod intern afisam numai 0 si introduceam fii in coada pentru
a-i prelucra in ordine.

# Cerinta 3

**_La cerinta trei_** am facut inversul de la cerinta doi. Acum, daca citeam din fisier valoarea 0 stiam ca acesta este un nod
intern si introduceam in coada urmatorul nod pentru a-l verifica. La verificare, daca acesta se adeverea a fi un nod
frunza citeam urmatoarele valori care erau RGB si il adaugam ca fiu in arbore. Acest lucru a fost implementat tot
recursiv, pentru a putea adauga corect restull fiilor nodului.

#### REZULTATE CHECKER LOCAL:

    Cerinta 1 : 20
    Cerinta 2 : 30.0
    Cerinta 3 : 30.0
    Total     : 80.0
    Bonus     : 0
    Felicitari! Ai punctajul maxim: 80p! :)
