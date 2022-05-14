#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "JeuModeGraphique.h"
#include "JeuModeTXT.h"

using namespace std;

class Menu
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Color font_color;
    SDL_Event event;
    SDL_Texture * background;
    SDL_Texture * bouton[3];
    SDL_Texture * titre;
    SDL_Rect boutonJouer;
    SDL_Rect boutonJouer2;
    SDL_Rect boutonQuitter;
    SDL_Surface * titreSurf;
    bool withSound;
    const int DIMX = 300;
    const int DIMY = 600;

public:
    Menu();
    ~Menu();
    void affichageInitMenu();
    void initFont();
    void initTexture();
    void initSon();
    void afficherMenu();
    void jouerSDL(Jeu jeu ,JeuModeGRAPHIQUE sl, double dt);
    void jouerTXT(Jeu jeu,JeuModeTXT txt, double dt);
    void boucleMenu(double dt);
    void afficheDetruireMenu();
};

#endif