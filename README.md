# Magic Tape Operations

## Descriere
Acest proiect implementează o simulare a operațiilor pe o "bandă magică", folosind structuri de date precum cozi și stive. Banda permite execuția mai multor operații de tip UPDATE, QUERY, UNDO, REDO și EXECUTE. Operațiile sunt citite de la tastatură și stocate într-o coadă, pentru a fi executate ulterior. 

Ceința completă poate fi văzută în fișierul `Magic_Tape.pdf`

Proiectul este realizat în limbajul C și manipulează datele printr-o structură dublu înlănțuită, cu santinelă.

## Funcționalități și Logică
1. **Citirea operațiilor**: Programul citește de la tastatură numărul de operații care urmează să fie executate și le stochează. Fiecare operație este verificată folosind funcția `strstr()` pentru a determina tipul acesteia (ex. UPDATE, EXECUTE).
   
2. **UPDATE**: Dacă operația este de tip UPDATE, aceasta este adăugată într-o coadă pentru a fi executată mai târziu. Operațiile UPDATE nu sunt executate imediat, ci sunt puse în așteptare.

3. **EXECUTE**: Atunci când se întâlnește o comandă de tip EXECUTE, se extrage prima operație din coadă folosind `front()`, se verifică din nou tipul acesteia și se execută operația pe bandă. După execuție, comanda este eliminată din coadă.

4. **UNDO/REDO**: În funcție de operația executată, programul poate adăuga în stiva de `undo` folosind funcția `push()`. Dacă se efectuează modificări care nu mai permit anularea sau refacerea operațiilor, stivele de `undo` și `redo` sunt golite pentru a preveni execuții greșite.

Această structură modulară asigură execuția eficientă a operațiilor și permite revenirea la stările anterioare ale benzii prin stivele de undo/redo.
