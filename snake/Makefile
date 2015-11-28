OFILES = projet.o\
				 deplacement.o\
				 affichage.o	 controleClavier.o\
				 init.o

FILES_IN_ARCHIVE = Makefile\
									 projet.c\
									 constantes.h\
									 deplacement.c\
									 deplacement.h\
									 controleClavier.c\
									 controleClavier.h\
									 init.c\
									 init.h\
									 affichage.c\
									 affichage.h


but : projet 

deplacement.o : deplacement.h init.h 

affichage.o : affichage.h

init.o : init.h
 
controleClavier.o : controleClavier.h

projet.o : deplacement.o affichage.o controleClavier.o init.o


projet : $(OFILES)
	cp projet.c saves/projet`date +%^b%d_%Hh%Mm%Ss`.c
	$(CC) $(CFLAGS) $(OFILES) -lgraph -o projet
	cp projet /tmp
	chmod +x /tmp/projet images/*
	/tmp/projet

archive-all :
	rm projet.tar.gz
	make clean
	tar cvzf projet.tar.gz `ls` 

archive :
	tar cvzf projet.tar.gz $(FILES_IN_ARCHIVE)

run :
	/tmp/projet

clean :
	-rm -f $(OFILES) projet

force :
	make clean
	make


.PHONY : but clean run force archive archive-all

