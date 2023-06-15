# MatrixParserEvaluator

Implementirati klasu Mastrica koja čuva matricu proizvoljnih dimenzija. Potrebno je preklopiti 
operatore < < i > >, pri čemu prvi operator ispisuje matricu na ekran, a drugi omogućava unos 
objekata tipa Matrica sa tastature. Format za unošenje matrice formata 2 × 3 sa tastature je 
[1 2 3; 4 5 6]. Međutim, potrebno je podržati unos i složenijih izraza, kao npr. [1 2; 3 4]^3 ∗ (4 ∗
[1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^𝑇) − [1 3; 7 2]^ − 1 ∗ [7 8 1; 1 2 3] ∗ 𝐼3. Ukoliko izraz nije validan iz 
nekog razloga (npr. ne slažu se dimenzije matrica), treba baciti izuzetak. Također, imlementirati 
funkciju koja računa determinantu matrice (ukoliko se radi o kvadratnoj matrici). Za množenje je 
potrebno imlementirati brzi algoritam koji koristi strategiju podijeli pa vladaj.
