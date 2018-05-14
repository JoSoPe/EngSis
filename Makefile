delete:
	\rm -f *.db
dades:
	python3 dades.py 
lite:
	sqlite3 lecturasensor.db
octave:
	octave
.PHONY:

clean:
	\rm -f *~ .#*
