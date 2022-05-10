#include "JeuModeGraphique.h"
#include "Menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

double dt = 1.0 / 60.0;

using namespace std;

int main(int argc, char** argv)
{
    time_t t;
    srand((unsigned)time(&t));
    Jeu jeu;
    JeuModeGRAPHIQUE sl;
    Menu menu();
    sl.InitCam();
    sl.boucleAffGRAPHIQUE(jeu, dt);
    return 0;
}