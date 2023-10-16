# Task 4 - Binary Tree (25p)

Scopul acestui task este de a va obisnui cu apeluri de functii si recursivitate in limbajul de asamblare.

---

In cadrul acestui task veti lucra cu un arbore binar, ale carui
noduri au urmatoarea structura:
```c
struct node {
    int value;
    struct node *left;
    struct node *right;
} __attribute__((packed));
```
---
---
## Exercitiul I
Primul exercitiu consta in parcurgerea unui arbore binar
de cautare in [_inordine_](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/) si de a stoca valorile din noduri.
```c
inorder_parc(struct node *node, int *array);
````
Functia primeste ca argumente:
1. node &nbsp; = radacina arborelui;
2. array&nbsp;&nbsp; = vectorul in care se vor stoca valorile nodurilor.

**ATENTIE**

1. Pentru a retine pozitia din vectorul **array** unde veti stoca
urmatorul element folositi variabila importata **array_idx_1**. Vectorul este **indexat de la 0**!  


**OBSERVATII**
1. Vectorul **array** este alocat in prealabil.
2. Variabila **array_idx_1** este setata pe 0 la fiecare test in prealabil.


## Exemplu
<img src=https://i.imgur.com/dOUWnlw.png width="300" height="200" align="center" title="Exemplu">  
  
  
### In acest exemplu vectorul **array** va contine elementele [5, 10, 15, 19, 20, 25, 30, 35].

---
---

## Exercitiul II
Al doilea exercitiu consta in parcurgerea unui arbore binar
de cautare in [_inordine_](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/) si de a stoca valorile din nodurile care nu respecta proprietatea de arbore binar de cautare.
```c
inorder_intruders(struct node *node, struct node *parent, int *array);
````
Functia primeste ca argumente:
1. node  &nbsp;&nbsp;&nbsp; = radacina arborelui;
2. parent&nbsp; = tatal/parintele nodului actual din arborele de cautare;
3. array &nbsp;&nbsp;&nbsp; = vectorul in care se vor stoca valorile nodurilor.  

Proprietatea care ne intereseaza este formata din cele doua inegalitati:
1. root->value > root->left->value, daca root->left exista;
2. root->value < root->right-> value, daca root->right exista.

**ATENTIE**

1. **Doar** in **frunze** pot aparea valori gresite;
1. Pentru a retine pozitia din vectorul **array** unde veti stoca
urmatorul element folositi variabila importata **array_idx_2**. Vectorul este **indexat de la 0**!  


**OBSERVATII**
1. Vectorul **array** este alocat in prealabil.
2. Variabila **array_idx_2** este setata pe 0 la fiecare test in prealabil.
3. Arborele **nu** trebuie modificat.


## Exemplu
<img src=https://i.imgur.com/YA8wzpx.png width="300" height="200" align="center" title="Exemplu">  
  
  
### In acest exemplu vectorul **array** va contine elementele [12, 40].

---
---

## Exercitiul III
Al treilea exercitiu consta in parcurgerea unui arbore binar
de cautare in [_inordine_](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/) si de a modifica valorile din nodurile care nu respecta proprietatea de arbore binar de cautare.
```c
inorder_fixing(struct node *node, struct node *parent);
````
Functia primeste ca argumente:
1. node  &nbsp;&nbsp;&nbsp; = radacina arborelui;
2. parent&nbsp; = tatal/parintele nodului actual din arborele de cautare;  

Proprietatea care ne intereseaza este formata din cele doua inegalitati:
1. root->value > root->left->value, daca root->left exista;
2. root->value < root->right-> value, daca root->right exista.  

Algoritmul dupa care vor fi modificate valorile gresite este urmatorul:  
1. Daca nodul actual este fiul stang, acesta va primi valoarea tatalui -1, altfel spus:  
 root->value = parent->value - 1;
2. Daca nodul actual este fiul drept, acesta va primi valoarea tatalui +1, altfel spus:  
 root->value = parent->value + 1.  

**ATENTIE**

1. **Doar** in **frunze** pot aparea valori gresite;


**OBSERVATII**
1. Valorile gresite **nu** trebuie salvate, doar modificate in arbore.


## Exemplu
<img src=https://i.imgur.com/YA8wzpx.png width="300" height="200" align="left" title="Exemplu">  
  
  
<img src=https://i.imgur.com/E5IFteR.png width="300" height="200" align="right" title="Exemplu">
&nbsp;
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  

     
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  &nbsp;&nbsp;===============================>
   
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  




---
---
## Folosire checker  
Checkerul poate fi folosit individual pentru fiecare exercitiu, nu inainte de a compila sursele folosind **make**:
1. **./checker 1**
1. **./checker 2**
1. **./checker 3**

Pentru a verifica toate exercitiile simultan folositi **./checker**.  
Veti primi feedback (**failed**\/**passed**) pentru fiecare test in parte, iar la final un punctaj provizoriu.  
