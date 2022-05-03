#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

class Menu {
    private:
        SDL_Renderer *rendu;
        int texture, x, y;
        SDL_Texture **T_Menu;
        SDL_Rect cursor;




    public:
        Menu(SDL_Renderer * rendu_);
        void affichage();
        SDL_Texture * Load(const char* chemin);
        void option();
};


#endif
