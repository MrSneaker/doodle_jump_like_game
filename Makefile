SDL2= `sdl2-config --cflags --libs` -lSDL2_image -lSDL2 -lSDL2_ttf -lSDL2_mixer
CCOPTIONS	= -Wall -ggdb
CC = g++ $(CCOPTIONS)

all: bin/test bin/affichageModeGRAPHIQUE

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

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Personnage.h src/Monstre.h src/bonus.h src/Plateforme.h src/Ecran.h
	$(CC) -c -o obj/Jeu.o src/Jeu.cpp 

obj/JeuModeTXT.o: src/JeuModeTXT.cpp src/JeuModeTXT.h src/Jeu.h
	$(CC) -c -o obj/JeuModeTXT.o src/JeuModeTXT.cpp

obj/JeuModeGRAPHIQUE.o: src/JeuModeGraphique.cpp src/JeuModeGraphique.h src/Jeu.h src/JeuModeTXT.h
	$(CC) -c -o obj/JeuModeGRAPHIQUE.o src/JeuModeGraphique.cpp $(SDL2)

obj/Ecran.o: src/Ecran.cpp src/Ecran.h src/Plateforme.h src/Monstre.h src/bonus.h
	$(CC) -c -o obj/Ecran.o src/Ecran.cpp

obj/Menu.o: src/Menu.cpp src/Menu.h
	$(CC) -c -o obj/Menu.o src/Menu.cpp $(SDL2)

obj/mainTest.o: src/mainTest.cpp src/Personnage.h src/projectile.h src/Monstre.h src/bonus.h src/Plateforme.h src/Jeu.h src/Ecran.h
	$(CC) -c -o obj/mainTest.o src/mainTest.cpp

obj/mainAffichageModeGRAPHIQUE.o: src/mainAffichageModeGRAPHIQUE.cpp src/Personnage.h src/projectile.h src/Monstre.h src/bonus.h src/Plateforme.h src/Jeu.h src/JeuModeGraphique.h src/Ecran.h src/Menu.h src/JeuModeTXT.h
	$(CC) -c -o obj/mainAffichageModeGRAPHIQUE.o src/mainAffichageModeGRAPHIQUE.cpp $(SDL2)

bin/test: obj/Personnage.o obj/projectile.o obj/mainTest.o obj/Monstre.o obj/bonus.o obj/Plateforme.o obj/Jeu.o obj/Ecran.o
	$(CC) -o bin/test obj/mainTest.o obj/Personnage.o obj/projectile.o obj/Monstre.o obj/bonus.o obj/Plateforme.o obj/Jeu.o obj/Ecran.o

bin/affichageModeGRAPHIQUE: obj/mainAffichageModeGRAPHIQUE.o obj/Personnage.o obj/projectile.o obj/mainTest.o obj/Monstre.o obj/bonus.o obj/Plateforme.o obj/Jeu.o obj/JeuModeGRAPHIQUE.o obj/JeuModeTXT.o obj/Ecran.o obj/Menu.o
	$(CC) -o bin/affichageModeGRAPHIQUE obj/mainAffichageModeGRAPHIQUE.o obj/Personnage.o obj/projectile.o obj/Monstre.o obj/bonus.o obj/Plateforme.o obj/Jeu.o obj/JeuModeGRAPHIQUE.o obj/JeuModeTXT.o obj/Ecran.o obj/Menu.o $(SDL2)



clean: 
	rm obj/*.o
	rm bin/*