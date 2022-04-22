#include "JeuModeGraphique.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>


const int TAILLE_SPRITE = 32;
const int DIMX= 30; 
const int DIMY= 60;



// ============= CLASS JEUMODEGRAPHIQUE =============== //

JeuModeGRAPHIQUE::JeuModeGRAPHIQUE(){
    cam.x = 0;
    cam.y = 0;
}

JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE(){  
}

Vec2 JeuModeGRAPHIQUE::convertPos(Vec2 pos)
{
    Vec2 newPos;
    double scaleX = 100 / DIMX;
    // double scaleY = 12 / DIMY;
    newPos.x = ((pos.x - cam.x) / scaleX + DIMX / 2);
    newPos.y = (DIMY * pos.y) / 12;
    //if (newPos.x >= 0 && newPos.x <= DIMX && newPos.y >=0 && newPos.y <= DIMY)
        return newPos;
}

void JeuModeGRAPHIQUE::InitCam()
{
    cam.x = convertPos(jeu.getConstPersonnage().getPos()).x + DIMX / 2;
    cam.y = convertPos(jeu.getConstPersonnage().getPos()).y + DIMY / 2;
}

void termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void JeuModeGRAPHIQUE::affichageInitGRAPHIQUE(){
    
    int winx, winy;
    Jeu jeu;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Initialisation de l'écriture
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Foodle_Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winx*TAILLE_SPRITE, winy*TAILLE_SPRITE, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }


    //Initialisation du rendu
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
   
}

void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu) {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Rect plateformes;


	int x,y;
	const Personnage& perso = jeu.getConstPersonnage();


    // Afficher les sprites des plateformes et des projectiles
	for (x=0;x<perso.getTaille();++x)
		for (y=0;y<perso.getTaille();++y)
			if (

}
   







