CCOPTIONS	= -Wall -ggdb
CC = g++ $(CCOPTIONS)

all: bin/test

obj/Monstre.o: src/Monstre.cpp src/Monstre.h
	$(CC) -c -o obj/Monstre.o src/Monstre.cpp

obj/Plateforme.o: src/Plateforme.cpp src/Plateforme.h
	$(CC) -c -o obj/Plateforme.o src/Plateforme.cpp

obj/bonus.o: src/bonus.cpp src/bonus.h
	$(CC) -c -o obj/bonus.o src/bonus.cpp

obj/projectile.o: src/projectile.cpp src/projectile.h
	$(CC) -c -o obj/projectile.o src/projectile.cpp 

obj/Personnage.o: src/Personnage.cpp src/Personnage.h src/projectile.h
	$(CC) -c -o obj/Personnage.o src/Personnage.cpp 

obj/mainTest.o: src/mainTest.cpp src/Personnage.h src/projectile.h src/Monstre.h src/bonus.h src/Plateforme.h
	$(CC) -c -o obj/mainTest.o src/mainTest.cpp

bin/test: obj/Personnage.o obj/projectile.o obj/mainTest.o obj/Monstre.o obj/bonus.o obj/Plateforme.o
	$(CC) -o bin/test obj/mainTest.o obj/Personnage.o obj/projectile.o obj/Monstre.o obj/bonus.o obj/Plateforme.o

clean: 
	rm obj/*.o
	rm bin/*