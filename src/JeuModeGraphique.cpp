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


    //Creation des rectangles pour plateformes, perso, monstres et bonus
    SDL_Rect perso; //carré jaune
    SDL_Rect plateformes; //bleu pour l'instant
    SDL_Rect monstres; //carre rouge
    SDL_Rect bonus; //carre vert
   
}


void JeuModeGRAPHIQUE::updatePlateau(Jeu &jeu)
{

    float newcamX = convertPos(jeu.getConstPersonnage().getPos()).x;
    //cout << "newcamX : " << newcamX;
    if (newcamX <= cam.x)
        cam.x = newcamX;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if ((int(convertPos(jeu.getConstPersonnage().getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstPersonnage().getPos()).y) == j) && (jeu.getConstPersonnage().enVie == true))
            {
                
            }
            for (int m = 0; m < 4; m++)
            {
                if ((int(convertPos(jeu.getConstMonstre(m).getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstMonstre(m).getPos()).y) == j) && (jeu.getConstMonstre(m).enVie == true) && ((int(convertPos(jeu.getConstMonstre(m).getPos()).x) > 0)))
                {
                    if (jeu.getConstMonstre(m).getTailleM().y == 1)
                    {
                        bordure[i][j] = ;
                        bordure[i - 1][j] = 'm';
                        bordure[i - 1][j + 1] = 'm';
                        bordure[i][j + 1] = 'm';
                    }
                    else
                        bordure[i][j] = 'M';
                }
            }
            for (long unsigned int p = 0; p < jeu.getPlateforme().size(); p++)
            {
                if ((int(convertPos(jeu.getPlateforme().at(p).getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getPlateforme().at(p).getPos()).y) == j) && (jeu.getPlateforme().at(p).estAfficheable() == true) && (int(convertPos(jeu.getPlateforme().at(p).getPos()).x) > 0))
                {
                    if (jeu.getPlateforme().at(p).getTaille().y == 2)
                    {
                        bordure[i][j] = '_';
                        bordure[i][j + 1] = '_';
                        bordure[i][j + 2] = '_';
                        bordure[i][j + 3] = '_';
                        // cout<<"pos conv plat x: "<<convertPos(jeu.getPlateforme().at(p).getPos()).x;
                        // cout<<"pos conv plat y: "<<convertPos(jeu.getPlateforme().at(p).getPos()).y;
                    }
                }
            }
            for (int pr = 0; pr < jeu.getConstPersonnage().getNombreProj(); pr++)
            {
                Vec2 pospr = convertPos(jeu.getConstPersonnage().getProjectileAff(pr).getpos());
                if ((int(pospr.x - cam.x + DIMX / 2) == i) && (int(pospr.y) == j) && (jeu.getConstPersonnage().getProjectileAff(pr).existe) && ((int(pospr.x) > 0)))
                {
                    bordure[i][j] = '.';
                }
            }
            for (int b = 0; b < 4; b++)
            {
                if ((int(convertPos(jeu.getConstBonus(b).getPosBonus()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstBonus(b).getPosBonus()).y) == j) && (jeu.getConstBonus(b).estPris == false) && ((int(convertPos(jeu.getConstBonus(b).getPosBonus()).x) > 0)))
                {
                    if (jeu.getConstBonus(b).getNomB() == "j")
                    {
                        bordure[i][j] = 'j';
                        bordure[i - 1][j] = 'j';
                        bordure[i - 1][j + 1] = 'j';
                        bordure[i][j + 1] = 'j';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "h")
                    {
                        bordure[i][j] = 'h';
                        bordure[i - 1][j] = 'h';
                        bordure[i - 1][j + 1] = 'h';
                        bordure[i][j + 1] = 'h';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "r")
                    {
                        bordure[i][j] = 'r';
                        bordure[i - 1][j] = 'r';
                        bordure[i - 1][j + 1] = 'r';
                        bordure[i][j + 1] = 'r';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "b")
                    {
                        bordure[i][j] = 'b';
                        bordure[i - 1][j] = 'b';
                        bordure[i - 1][j + 1] = 'b';
                        bordure[i][j + 1] = 'b';
                    }
                }
            }
        }
    }
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
    Vec2
    
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






