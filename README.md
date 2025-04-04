Despre Organizarea unui Turneu:

Organizarea unui turneu implică mai multe etape esențiale, de la înregistrarea echipelor și a jucătorilor, până la programarea meciurilor și gestionarea rezultatelor. Pentru ca turneul să fie un succes, este necesară o gestionare atentă și eficientă a acestor aspecte.

Înregistrarea echipelor și jucătorilor: Primul pas este colectarea și stocarea informațiilor despre fiecare echipă și jucător. Fiecare echipă trebuie să aibă un nume, un punctaj și o listă de jucători, în timp ce fiecare jucător are un nume, prenume și un număr de puncte acumulate. Punctajul echipei este calculat astfel: media aritmetică a punctelor de experiență (points) corespunzătoare jucătorilor din echipa respectivă. La fiecare meci câștigat, punctajul de echipă va crește cu 1.

Se va citi conținutul fișierului "d.in". Se va crea o listă prin adăugarea elementelor la începutul listei. Aceasta se va face într-un timp constant (O(1)) pentru fiecare element adăugat. Eliminarea echipelor cu cel mai mic punctaj:
-se vor elimina echipele cu cel mai mic punctaj, iar în cazul în care două echipe au același punctaj, va fi eliminată prima echipă citită din listă. Acest proces de eliminare se va realiza până când în listă vor rămâne n echipe, unde n este puterea maximă a lui 2.

Programarea meciurilor:

Se creează o coadă unde vom pune meciurile dintre echipe (2 echipe consecutive formează un meci). Câștigătorii vor fi puși într-o stivă câștigătoare, iar cei care pierd, învinșii, într-o stivă pierzătoare. În cele două stive se vor baga echipele care au câștigat meciul anterior, respectiv cele care au pierdut. La finalul fiecărei runde, se vor șterge din stiva de învinși echipele care au pierdut. Din stiva câștigătoare, se vor extrage echipele și se va umple din nou coada de meciuri, formându-se meciuri între echipele consecutive. Acest proces se va repeta până când vor rămâne primele 8 echipe.

Crearea arborelui BST:

Se va crea un arbore binar de căutare, cu ajutorul celor 8 echipe salvate anterior. Acest arbore va fi ordonat după punctajul echipei, în ordine descrescătoare. Dacă două echipe au același punctaj, ordonarea se va face după nume, tot în ordine descrescătoare, urmând ca arborele să fie afișat, astfel încât echipele cu punctaj cel mai mic să fie pe nivelul cel mai de jos (se vor afișa ultimele).

Crearea arborelui AVL: 
Se va crea un arbore AVL, cu ajutorul celor 8 echipe salvate anterior. Acestea vor fi sortate tot după nume, respectiv punctaj, în ordine descrescătoare. Se vor afișa echipele de pe nivelul 2 al acestui arbore.
