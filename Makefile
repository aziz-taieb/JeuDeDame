all: main cli serv

fonctions.o: fonctions.c fonctions.h
	gcc -c fonctions.c

main: main.o fonctions.o
	gcc -o main main.o fonctions.o -Wall -pedantic -lm

cli: client_dame.o fonctions.o
	gcc -o cli client_dame.o fonctions.o -Wall -pedantic -lm

serv: serveur_dame.o fonctions.o
	gcc -o serv serveur_dame.o fonctions.o -Wall -pedantic -lm

clean:
	rm -f *.o main cli serv
