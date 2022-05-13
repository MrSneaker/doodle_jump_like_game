#ifndef __JEUMODEGRAPHIQUE_H__
#define __JEUMODEGRAPHIQUE_H__

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include "JeuModeTXT.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>

class JeuModeGRAPHIQUE
{
private:
    Jeu jeu;
    SDL_Window *window;     /*fenetre SDL */
    SDL_Renderer *renderer; /*render SDL */
    SDL_Texture *textureBackground;
    SDL_Texture *texturePersF;
    SDL_Texture *texturePersD;
    SDL_Texture *texturePersG;
    SDL_Texture *texturePersS;
    SDL_Texture *texturePersJ[2];
    SDL_Texture *texturePersH[2];
    SDL_Texture *texturePersB[2];
    SDL_Texture *texturePlat[2];
    SDL_Texture *textureMonstre[4];
    SDL_Texture *textureBonus[6];
    SDL_Texture *projTex;
    TTF_Font *font;
    SDL_Color font_color;
    SDL_Surface* scoreSurf;
    SDL_Texture * score;
    Mix_Music *saut;
    Mix_Music *helico;
    Mix_Music *jetpack;
    Mix_Music *tir;
    Mix_Music *Mmeurt;
    Mix_Music *ressort;
    Mix_Music *Pmort;
    bool withSound;
    const int NB_BONUS = 5;
    const int NB_MONSTRE = 4;
    float tpsJ = 0;
    float tpsH = 0;
    float tpsB = 0;
    float tpsSonMort = 0;

public:
    JeuModeGRAPHIQUE();
    ~JeuModeGRAPHIQUE();
    JeuModeTXT txt;
    Vec2 cam;
    Vec2 convertPos(Vec2 pos);
    void InitCam();
    void InitTexture();
    void initSon();
    void initFont();
    void affichageInitGRAPHIQUE();                /*! \brief affichage de SDL2*/
    void affichageGRAPHIQUE(Jeu &jeu, double dt); /*! \brief affiche l'image dans la fenetre SDL2*/
    void boucleAffGRAPHIQUE(Jeu &jeu, double dt); /*! \brief rafraichissement de l'image*/
    void affDetruireGRAPHIQUE();                  /*! \brief Détruit l'affichage*/
};

#endif