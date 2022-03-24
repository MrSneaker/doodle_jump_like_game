CCOPTIONS	= -Wall -ggdb
CC = g++ $(CCOPTIONS)

all: bin/test

obj/projectile.o: src/projectile.cpp src/projectile.h
	$(CC) -c -o obj/projectile.o src/projectile.cpp 

obj/Personnage.o: src/Personnage.cpp src/Personnage.h src/projectile.h
	$(CC) -c -o obj/Personnage.o src/Personnage.cpp 

obj/mainTest.o: src/mainTest.cpp src/Personnage.h src/projectile.h
	$(CC) -c -o obj/mainTest.o src/mainTest.cpp

bin/test: obj/Personnage.o obj/projectile.o obj/mainTest.o
	$(CC) -o bin/test obj/mainTest.o obj/Personnage.o obj/projectile.o

clean: 
	rm obj/*.o
	rm bin/*