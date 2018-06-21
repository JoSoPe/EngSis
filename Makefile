delete:
	\rm -f *.db
dades: #Per treballar amb la base de dades, ja sigui per importar exportar o grear la base de dades
	python3 dades.py 
lite:	#Per interactuar amb la base de dades a partir de sqlite3
	sqlite3 lecturasensor.db
octave:
	octave

.PHONY:

clean:
	\rm -f *~ .#*
