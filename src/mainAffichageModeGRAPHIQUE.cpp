#include "JeuModeGraphique.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>



using namespace std;

int main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    if (0 != SDL_Init(SDL_INIT_VIDEO)) //initialisation SDL video
    {
        std::cout << "erreur" << SDL_GetError() << endl;
        goto Quit; //ca quitte dès qu'il y a une erreur
    }
    window = SDL_CreateWindow("SDLFenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    
    if(NULL == window)
    {
        goto Quit; //quitte s'il y a une erreur
    }

    SDL_Delay(3000);
    SDL_DestroyWindow(window);

    Quit:
        SDL_Quit(); //cela ferme la fenetre SDL
        return EXIT_SUCCESS;
}