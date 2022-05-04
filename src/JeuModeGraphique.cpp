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
    texturePersD = NULL;
    texturePersG = NULL;
    texturePersF = NULL;
    textureBackground = NULL;
    texturePlat[0] = NULL;
    texturePlat[1] = NULL;
    for (int i = 0; i < NB_BONUS; i++)
    {
        textureBonus[i] = NULL;
    }
    for (int i = 0; i < NB_MONSTRE; i++)
    {
        textureMonstre[i] = NULL;
    }
}

JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE()
{
}

char bordure[15][30];
char bordureClean[15][30];

Vec2 JeuModeGRAPHIQUE::convertPos(Vec2 pos)
{
    Vec2 newPos;
    double scaleX = 100 / DIMY;
    double scaleY = 12 / DIMX;
    newPos.x = (DIMY * pos.x) / 100;
    newPos.y = (DIMX * pos.y) / 12;
    return newPos;
}

void JeuModeGRAPHIQUE::InitCam()
{
    cam.x = 0;
    cam.y = convertPos(jeu.getConstPersonnage().getPos()).x - DIMX / 2;
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
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        // SDL_Quit();exit(1);
        withSound = false;
    }
    else
        withSound = true;

    // Initialisation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "erreur lors de la création du rendu " << endl;
        SDL_Quit();
        exit(1);
    }
}

void JeuModeGRAPHIQUE::InitTexture()
{
    textureBackground = IMG_LoadTexture(renderer, "data/background.png");
    texturePersG = IMG_LoadTexture(renderer, "data/persoGauche.png");
    texturePersD = IMG_LoadTexture(renderer, "data/persoDroite.png");
    texturePersF = IMG_LoadTexture(renderer, "data/persoFace.png");
    texturePlat[0] = IMG_LoadTexture(renderer, "data/plateforme1.png");
    texturePlat[1] = IMG_LoadTexture(renderer, "data/plateforme4.png");
}

void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu, double dt)
{
    float newcamY = convertPos(jeu.getConstPersonnage().getPos()).x;
    if (newcamY <= cam.y)
        cam.y = newcamY;
    SDL_RenderCopy(renderer, textureBackground, NULL, NULL);
    const Personnage &perso = jeu.getConstPersonnage();
    const Monstre &mon = jeu.getConstMonstre(dt);
    const bonus &bon = jeu.getConstBonus(dt);
    SDL_Rect rectPers;

    rectPers.x = convertPos(perso.getPos()).y;
    rectPers.y = convertPos(perso.getPos()).x - cam.y + DIMY / 2;
    rectPers.h = perso.getTaille().x * TAILLE_SPRITE;
    rectPers.w = perso.getTaille().y * TAILLE_SPRITE;

    SDL_RenderCopy(renderer, texturePersD, NULL, &rectPers);
    int nbPl = jeu.getPlateforme().size();
    for (int i = 0; i < nbPl; i++)
    {
        SDL_Rect rectPlat;
        const Plateforme &Pl = jeu.getPlateforme().at(i);
        rectPlat.x = convertPos(Pl.getPos()).y;
        rectPlat.y = convertPos(Pl.getPos()).x - cam.y + DIMY / 2;
        rectPlat.h = Pl.getTaille().x * TAILLE_SPRITE;
        rectPlat.w = Pl.getTaille().y * TAILLE_SPRITE;
        if (Pl.getRes() == -1)
        {
            SDL_RenderCopy(renderer, texturePlat[0], NULL, &rectPlat);
        }
        else if (Pl.getRes() == 1)
        {
            SDL_RenderCopy(renderer, texturePlat[1], NULL, &rectPlat);
        }
    }

    SDL_RenderPresent(renderer);
}

void JeuModeGRAPHIQUE::boucleAffGRAPHIQUE(Jeu &jeu, double dt)
{
    SDL_Event events;
    affichageInitGRAPHIQUE();
    InitTexture();
    std::chrono::high_resolution_clock timer;
    bool quit = false;
    while (!quit)
    {
        auto start = timer.now();
        SDL_Delay(10);
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
                case SDL_SCANCODE_A:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }
        affichageGRAPHIQUE(jeu, dt);
        auto stop = timer.now();
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
        if (jeu.getConstPersonnage().enVie == false)
        {
            quit = true;
        }
    }
    affDetruireGRAPHIQUE();
}

void JeuModeGRAPHIQUE::affDetruireGRAPHIQUE()
{
    if (withSound)
        Mix_Quit();
    // TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texturePersD);
    SDL_DestroyTexture(textureBackground);
    SDL_DestroyTexture(texturePersF);
    SDL_DestroyTexture(texturePersG);
    SDL_DestroyTexture(texturePlat[0]);
    SDL_DestroyTexture(texturePlat[1]);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
