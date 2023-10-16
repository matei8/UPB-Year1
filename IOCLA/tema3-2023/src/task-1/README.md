# Task 1 - Reversing vowels (25p)

Scopul acestui task este sa folositi doar stiva, prin operatii push si pop,
pentru a lucra cu memoria.

---

Dupa sucesul de la Baku, Ferrari si-au dat seama ca mesajele criptate au 
functionat, iar Mercedes nu a avut nici o sansa impotriva lor. Dar din pacate
Red Bull si-au dat seama foarte rapid ce vor sa faca, asa ca dupa ce au trecut
calificarile, nu au mai avut nici o sansa impotriva echipei austriace.

Dar cei de la  Ferrari si-au dat seama ca nu pot sa ii intreaca la inteligenta 
pe cei de la Red Bull, asa ca s-au gandit la un mod cat mai simplu de a cripta 
un mesaj. Ei s-au gandit sa ia fiecare vocala din mesajul lor, si sa le afiseze
doar pe ele in ordine inversa. Asadar, atunci cand o sa vrea ei vreodata sa vorbeasc
despre Red Bull, tot ce va trebui sa faca e sa afiseze mesajul:

```c
rud bell    // "red bull" cu vocalele scrise in ordine inversa
```

Asa, Red Bull nu v-a stii niciodata ca vorbesc despre ei. Din pacate aceasta metoda
nu este la fel de eficienta daca vrem sa vorbim despre Mercedes, dar avem celalalt
mod de encriptare, asa ca ar trebui sa le iasa.

Pentru a implementa functia noastra, trebuie sa pornim de la string-ul primit ca
parametru, si sa facem toate modificarile in place. **Nu** aveti voie sa va definiti
un alt vector pentru a pastra o copie a string-ului sau pentru a stoca vocalele.

```c
void reverse_vowels(char *string);
```

## Exemple

Aceste string-ul vor contine doar litere mici ale alfabetului englez si whitespace

```
"hello" -> "holle"
"max verstappen" -> "mex varsteppan"
```

**Atentie!** Nu aveti voie sa folositi intructiunile din familia mov (mov, cmov,
stos, lods, etc), leave si enter. Toate operatiile de transfer din si in memorie
/ registre trebuie realizate folosind push si pop. Puteti folosi functii externe.

**Tips:** Pentru a rula checkerul fara a afisa diferentele, rulati cu `./checker -s`
