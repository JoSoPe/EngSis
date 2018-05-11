delete:
	\rm -f *.db

dump:
	python dades.py 
dades:
	emacs sensor.txt &

.PHONY:

clean:
	\rm -f *~ .#*
