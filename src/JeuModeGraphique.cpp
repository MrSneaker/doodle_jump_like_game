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
    projTex = NULL;
}

JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE()
{
}

Vec2 JeuModeGRAPHIQUE::convertPos(Vec2 pos)
{
    Vec2 newPos;
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

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
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
    texturePersG = IMG_LoadTexture(renderer, "data/helicoGIF.gif");
    texturePersD = IMG_LoadTexture(renderer, "data/persoDroite.png");
    texturePersF = IMG_LoadTexture(renderer, "data/persoFca.png");

    texturePlat[0] = IMG_LoadTexture(renderer, "data/plateforme1.png");
    texturePlat[1] = IMG_LoadTexture(renderer, "data/plateforme4.png");

    textureMonstre[0] = IMG_LoadTexture(renderer, "data/monstre1.png");
    textureMonstre[1] = IMG_LoadTexture(renderer, "data/monstre2.png");
    textureMonstre[2] = IMG_LoadTexture(renderer, "data/monstre3.png");
    textureMonstre[3] = IMG_LoadTexture(renderer, "data/monstre4.png");

    textureBonus[0] = IMG_LoadTexture(renderer, "data/bonus1.png");
    textureBonus[1] = IMG_LoadTexture(renderer, "data/bonus2.png");
    textureBonus[2] = IMG_LoadTexture(renderer, "data/bonus3.png");
    textureBonus[3] = IMG_LoadTexture(renderer, "data/bonus4.png");
    textureBonus[4] = IMG_LoadTexture(renderer, "data/bonus42.png");
    textureBonus[5] = IMG_LoadTexture(renderer, "data/hole.png");

    projTex = IMG_LoadTexture(renderer, "data/projectile.png");
}

void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu, double dt)
{
    float newcamY = convertPos(jeu.getConstPersonnage().getPos()).x;
    if (newcamY <= cam.y)
        cam.y = newcamY;
    SDL_RenderCopy(renderer, textureBackground, NULL, NULL);
    const Personnage &perso = jeu.getConstPersonnage();
    SDL_Rect rectPers;

    rectPers.x = convertPos(perso.getPos()).y;
    rectPers.y = convertPos(perso.getPos()).x - cam.y + DIMY / 2;
    rectPers.h = perso.getTaille().x * TAILLE_SPRITE;
    rectPers.w = perso.getTaille().y * TAILLE_SPRITE;
    if (jeu.Pdroite)
    {
        SDL_RenderCopy(renderer, texturePersD, NULL, &rectPers);
    }
    else if (jeu.Pgauche)
    {
        SDL_RenderCopy(renderer, texturePersG, NULL, &rectPers);
    }
    else
        SDL_RenderCopy(renderer, texturePersF, NULL, &rectPers);
    int nbPl = jeu.getPlateforme().size();
    for (int i = 0; i < nbPl; i++)
    {
        SDL_Rect rectPlat;
        const Plateforme &Pl = jeu.getPlateforme().at(i);
        rectPlat.x = convertPos(Pl.getPos()).y;
        rectPlat.y = convertPos(Pl.getPos()).x - cam.y + DIMY / 2;
        rectPlat.h = Pl.getTaille().x * TAILLE_SPRITE;
        rectPlat.w = Pl.getTaille().y * TAILLE_SPRITE;
        if (Pl.estAfficheable())
        {
            if (Pl.getRes() == -1)
            {
                SDL_RenderCopy(renderer, texturePlat[0], NULL, &rectPlat);
            }
            else if (Pl.getRes() == 1)
            {
                SDL_RenderCopy(renderer, texturePlat[1], NULL, &rectPlat);
            }
        }
    }
    for (int i = 0; i < NB_MONSTRE; i++)
    {
        const Monstre &mon = jeu.getConstMonstre(i);
        SDL_Rect rectM;
        float tailleY = mon.getTailleM().x;
        float tailleX = mon.getTailleM().y;
        rectM.x = convertPos(mon.getPos()).y;
        rectM.y = convertPos(mon.getPos()).x - cam.y + DIMY / 2;
        rectM.h = tailleY * TAILLE_SPRITE;
        rectM.w = tailleX * TAILLE_SPRITE;
        if (tailleX == 2 && tailleY == 1 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[0], NULL, &rectM);
        }
        else if (tailleX == 1 && tailleY == 1 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[1], NULL, &rectM);
        }
        else if (tailleX == 1 && tailleY == 1.5 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[2], NULL, &rectM);
        }
        else if (tailleX == 2 && tailleY > 0.5 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[3], NULL, &rectM);
        }
    }
    for (int i = 0; i < NB_BONUS; i++)
    {
        const bonus &bon = jeu.getConstBonus(i);
        SDL_Rect rectB;
        rectB.x = convertPos(bon.getPosBonus()).y;
        rectB.y = convertPos(bon.getPosBonus()).x - cam.y + DIMY / 2;
        rectB.h = bon.getTailleB().x * TAILLE_SPRITE;
        rectB.w = bon.getTailleB().y * TAILLE_SPRITE;
        if (bon.getNomB() == "h" && !bon.estPris)
        {
            SDL_RenderCopy(renderer, textureBonus[0], NULL, &rectB);
        }
        else if (bon.getNomB() == "j" && !bon.estPris)
        {
            SDL_RenderCopy(renderer, textureBonus[1], NULL, &rectB);
        }
        else if (bon.getNomB() == "b" && !bon.estPris)
        {
            SDL_RenderCopy(renderer, textureBonus[2], NULL, &rectB);
        }
        else if (bon.getNomB() == "r")
        {
            if (bon.estPris)
                SDL_RenderCopy(renderer, textureBonus[4], NULL, &rectB);
            else
                SDL_RenderCopy(renderer, textureBonus[3], NULL, &rectB);
        }
        else if (bon.getNomB() == "t")
        {
            SDL_RenderCopy(renderer, textureBonus[5], NULL, &rectB);
        }
    }
    for (int i = 0; i < perso.getNombreProj(); i++)
    {
        const projectile &proj = perso.getProjectileAff(i);
        SDL_Rect rectProj;
        if (proj.existe)
        {
            rectProj.x = convertPos(proj.getpos()).y;
            rectProj.y = convertPos(proj.getpos()).x - cam.y + DIMY / 2;
            rectProj.h = 0.5 * TAILLE_SPRITE;
            rectProj.w = 0.5 * TAILLE_SPRITE;
            SDL_RenderCopy(renderer, projTex, NULL, &rectProj);
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
        SDL_Delay(30);
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
                case SDL_SCANCODE_SPACE:
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
    for (int i = 0; i < NB_BONUS; i++)
    {
        SDL_DestroyTexture(textureBonus[i]);
    }
    for (int i = 0; i < NB_MONSTRE; i++)
    {
        SDL_DestroyTexture(textureMonstre[i]);
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
