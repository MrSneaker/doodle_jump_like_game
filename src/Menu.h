#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

class Menu {
    private:
        SDL_Surface *screen=NULL;
        SDL_Surface *text =NULL;
        SDL_Event event;
        bool run=true;




    public:
        Menu();
        ~Menu();
        int afficherMenu(SDL_Surface *screen, TTF_Font *font);
};


#endif