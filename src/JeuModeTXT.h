#ifndef JEUMODETXT_H
#define JEUMODETXT_H

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include <iostream>

class JeuModeTXT
{
private:
    Jeu jeu;


public:
    Vec2 cam;
    char cadre[15][30], cadreClear[15][30];
    JeuModeTXT();
    ~JeuModeTXT();
    void InitCam();
    Vec2 convertPos(Vec2 pos);
    void updatePlateau(Jeu &jeu);
    void affichageTXT(Jeu &jeu, double dt);
    void boucleAffTXT(Jeu &jeu, double dt);
    void affDetruireTXT(Jeu &jeu);
    char retournercadre();
    char retournercadreClear();
    void clear();
};

#endif