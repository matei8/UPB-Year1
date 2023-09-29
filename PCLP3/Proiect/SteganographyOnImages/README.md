# SteganographyOnImages


Proiectul presupune ascunderea informații in imagini de tip .ppm si ulterior sa le
si decodificam, pentru a putea extrage mesajul ascuns din ele. Pentru a lucra cu 
imagini si a modifica valorile RGB ale pixelilor o sa folosim operatii pe biti, iar 
codarea informațiilor va trebui făcută astfel încât calitatea imaginii sa nu difere 
semnificativ, astfel integrând informațiile cat mai bine in datele imaginii. Metoda 
abordata pentru codificarea informațiilor va fi LSB (Least Significant Bit), astfel 
modificând cat mai puțin din calitatea imaginii originale.

Urmatorii pasi vor fi urmati:
    1. Alegem imaginea PPM și textul secret pe care dorim să îl
    ascundem în imagine.
    
    2. Convertim textul secret într-un șir de biți. De exemplu, textul
    secret "Hello!" poate fi convertit în șirul de biți 01001000 01100101
    01101100 01101100 01101111 00100001.
    
    3. Alegem pixelii din imagine pe care dorim să îi utilizăm pentru
    a ascunde textul secret(prin parcurgerea matricei de pixeli de la
    stanga la dreapta si de sus in jos).
    
    4. Pentru fiecare pixel selectat, modificăm cel mai puțin
    semnificativ bit al valorii RGB cu un bit din șirul de biți al textului
    secret, în ordine secvențială. De exemplu, dacă primul bit din textul
    secret este 0, vom modifica cel mai puțin semnificativ bit al valorii
    RGB a primului pixel selectat cu 0. Dacă al doilea bit din textul secret
    este 1, vom modifica cel mai puțin semnificativ bit al urmatoarei
    valori RGB a primului pixel selectat cu 1 si așa mai departe(se va
    modifica LSB al ultimei valori RGB a primului pixel si apoi se va trece
    la urmatorul pixel pana cand se va codifica tot textul).
    
    5. După ce am modificat cel mai puțin semnificativ bit al valorii
    RGB pentru toți pixelii selectați, vom obține o imagine modificată
    care conține textul secret ascuns.
    
    6. Pentru a extrage textul secret din imagine, trebuie doar să
    alegem din nou pixelii selectați și să extragem cel mai puțin
    
De asemenea, au fost implmentate si niste comenzi pentru utilizarea programului:
    - (-t) -> timestamp, se va afișa ora la care a fost modificat fișierul;
    - (-l) -> log file, se vor păstra timpul, data si numele fișierelor de input/output 
    care au fost modificate la timpul si data respective;
    - (-lc) -> log clear,se sterge continutul fisierului log
    - (-s) -> dimensiunea fișierelor de input si a celor de output;
    - (-h) -> se va afișa meniul de help cu o descriere a opțiunilor;
    - (-c) ->codeaza mesajul
    - (-d) ->decodeaza mesajul
