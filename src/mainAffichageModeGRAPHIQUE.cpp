#include "JeuModeGraphique.h"
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
    Jeu jeu;
    JeuModeGRAPHIQUE sl;
    bool ok = jeu.getConstPersonnage().enVie;
    jeu.InitPersonnage();
    jeu.InitEc();
    jeu.InitBonus();
    jeu.InitMonstre();
    sl.updatePlateau(jeu);
    sl.affichageGRAPHIQUE(jeu, dt);
    sl.InitCam();
    do{
    
    jeu.update(dt);
    sl.affichageGRAPHIQUE(jeu, dt);
    sl.boucleAffGRAPHIQUE(jeu, dt);

    } while (ok);
    return 0;
}