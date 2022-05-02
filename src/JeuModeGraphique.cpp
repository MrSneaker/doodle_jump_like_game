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
    JeuModeTXT txt;
}



JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE(){  
}


char bordure[15][30];
char bordureClean[15][30];

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


    //Creation des rectangles pour plateformes, perso, monstres et bonus
    SDL_Rect perso; //carré jaune
    SDL_Rect plateformes; //bleu pour l'instant
    SDL_Rect monstres; //carre rouge
    SDL_Rect bonus; //carre vert
   
}


void JeuModeGRAPHIQUE::updatePlateau(Jeu &jeu)
{

//a l'aide
    
}


void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu, double dt) {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rect;
    int x,y;
	const Personnage& perso = jeu.getConstPersonnage();
	const Monstre& mon = jeu.getConstMonstre(dt);
    const bonus& bon = jeu.getConstBonus(dt);
    Vec2 a;
    
}



void JeuModeGRAPHIQUE::boucleAffGRAPHIQUE(Jeu &jeu, double dt)
{
    SDL_Event events;
    updatePlateau(jeu);
    affichageGRAPHIQUE(jeu, dt);
    SDL_Delay(1000);
    bool quit=false;
    while (!quit){
        while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;
			else if (events.type == SDL_KEYDOWN) {              
                bool seDeplace = false;
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					seDeplace = jeu.actionClavier('r', dt);    //lance un proj
					break;
				case SDL_SCANCODE_LEFT:
					seDeplace = jeu.actionClavier('g', dt); //se deplace a gauche
					break;
				case SDL_SCANCODE_RIGHT:
					seDeplace = jeu.actionClavier('d', dt); //se deplace a droite
					break;
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
				default: break;
				}
    }}}

    
}



   
void JeuModeGRAPHIQUE::affDetruireGRAPHIQUE(Jeu &jeu){
 
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}






