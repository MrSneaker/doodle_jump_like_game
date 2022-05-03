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
const int DIMX = 300;
const int DIMY = 600;

// ============= CLASS JEUMODEGRAPHIQUE =============== //

JeuModeGRAPHIQUE::JeuModeGRAPHIQUE()
{
    cam.x = 0;
    cam.y = 0;
    texture = NULL;
}

JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE()
{
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
    // if (newPos.x >= 0 && newPos.x <= DIMX && newPos.y >=0 && newPos.y <= DIMY)
    return newPos;
}

void JeuModeGRAPHIQUE::InitCam()
{
    cam.x = convertPos(jeu.getConstPersonnage().getPos()).x + DIMX / 2;
    cam.y = convertPos(jeu.getConstPersonnage().getPos()).y + DIMY / 2;
}

void JeuModeGRAPHIQUE::affichageInitGRAPHIQUE()
{
    Jeu jeu;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Initialisation de l'écriture
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Foodle_Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DIMX, DIMY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        withSound = false;
    }
    else withSound = true;

    // Initialisation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        cout<<"erreur lors de la création du rendu "<<endl;
        SDL_Quit();
        exit(1);
    }
}

void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu, double dt)
{
   
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 200, 240, 255, 255);
    SDL_RenderClear(renderer);
    const Personnage &perso = jeu.getConstPersonnage();
    const Monstre &mon = jeu.getConstMonstre(dt);
    const bonus &bon = jeu.getConstBonus(dt);
    SDL_Rect rectPers;
    rectPers.x = convertPos(perso.getPos()).y;
    rectPers.y = convertPos(perso.getPos()).x;
    rectPers.h = perso.getTaille().x;
    rectPers.w = perso.getTaille().y;
    texture = IMG_LoadTexture(renderer, "/home/mateo/COURS/LIFAP4/FoodleJump/projet-lifap4/data/foodle.png");
    if(texture==NULL)
    {
        cout<<"texture non défini, erreur";
        SDL_Quit();
        exit(1);
    }
        
    SDL_RenderCopy(renderer, texture, NULL, &rectPers);
    /*SDL_FRect rectMon;
    rectMon.x = mon.getPos().x;
    rectMon.y = mon.getPos().y;*/
    SDL_RenderPresent(renderer);
}

void JeuModeGRAPHIQUE::boucleAffGRAPHIQUE(Jeu &jeu, double dt)
{
    SDL_Event events;
    affichageInitGRAPHIQUE();
    //SDL_Delay(1000);
    bool quit = false;
    while (!quit)
    {
        jeu.update(dt);
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true;
            else if (events.type == SDL_KEYDOWN)
            {
                bool seDeplace = false;
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    seDeplace = jeu.actionClavier('r', dt); // lance un proj
                    break;
                case SDL_SCANCODE_LEFT:
                    seDeplace = jeu.actionClavier('g', dt); // se deplace a gauche
                    break;
                case SDL_SCANCODE_RIGHT:
                    seDeplace = jeu.actionClavier('d', dt); // se deplace a droite
                    break;
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }
        affichageGRAPHIQUE(jeu,dt);
    }
    affDetruireGRAPHIQUE();
}

void JeuModeGRAPHIQUE::affDetruireGRAPHIQUE()
{
    if (withSound) Mix_Quit();
    //TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
