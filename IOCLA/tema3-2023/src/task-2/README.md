# Task 2 - Pwd (25p)

Pentru acest task trebuie implementata o functie ce va primii ca parametrii o matrice de caractere in care se vor afla numele a `n` foldere pe care se da comanda cd din linux in ordinea in care acestea apar, numarul de foldere
(aka nr de linii din matrice) si output care va contine path-ul rezultat.

Se vor implementa si "." (folder curent) si ".." (folder anterior), de asemenea
denumirea unui folder nu contine spatii.

Comportamentul ".." este asemanator cu cel din linux, astfel ca iesirea din
foldere se face atata timp cat are unde.

Pentru gestionarea sirurilor de caractere este obligatoriu folosirea stack-ului.

```c
void pwd(char **directories, int n, char *output)
```

Exemplu:

n = 5

directories =

```
home
folder1
.
folder2
..
folder3
```

```
output = /home/folder1/folder3
```

Comportamentul este urmatorul:

Se va adauga /home, apoi se va adauga /folder1, deci: /home/folder1

Se va gasi "." care se refera la folderul curent, deci ramane:/home/folder1

Dupa se adauga folder2, deci /home/folder1/folder2.

Se va gasi .., care se refera la folderul anterior, deci va iesi din cel curent rezultand: /home/folder1

Apoi este adugat folder3, si rezultatul final este: /home/folder1/folder3
