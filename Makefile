CCOPTIONS	= -Wall -ggdb
CC = g++ $(CCOPTIONS)

all: bin/test

obj/Personnage.o: src/Personnage.cpp src/Personnage.h
	$(CC) -c -o obj/Personnage.o src/Personnage.cpp 

obj/mainTest.o: src/mainTest.cpp src/Personnage.h
	$(CC) -c -o obj/mainTest.o src/mainTest.cpp

bin/test: obj/Personnage.o obj/mainTest.o
	$(CC) -o bin/test obj/mainTest.o obj/Personnage.o 