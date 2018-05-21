# EngSis
Projecte d'enginyeria de sistemes

A dades.py hi ha el sistema de gestió de la base de dades, tant per afegir dades, com per crear la base de dades com per exportar-ne el contingut

A filtre.py hi han observacións sobre les dades y test de probes sobre possibles filtres.

El directori sensor_data, conté dades diverses sobre testos qeu ja estan dins de la base de dades.

La base de dades de tot el projecte és lecturasensor.db

Les dades per importar a la base de dades han d'estar en el document sensor.txt

Les dades exportades de la base de dades es guardaran en el document exported.txt
-----------------------------------------------------
Llibreria timer:
https://playground.arduino.cc/Code/Timer



------------------------------------------------------

Com executar els codis:


make delete /* Elimina les bases de dades	*/
make dades  /* Executa el codi de dades.py	*/
make lite   /* Obre la base de dades amb sqlite3*/
make clean  /* Elimina fitxers temporals	*/
make octave /* Obre l'octave en el directori actual */

--------------
Per obrir el document de dades exportat amb octave:
A=load("exported.txt")