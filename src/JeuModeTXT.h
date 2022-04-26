#ifndef __JEUMODETXT_H__
#define __JEUMODETXT_H__

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
    JeuModeTXT();
    ~JeuModeTXT();
    void InitCam();
    Vec2 convertPos(Vec2 pos);
    void updatePlateau(Jeu &jeu);
    void affichageTXT(Jeu &jeu, double dt);
    void boucleAffTXT(Jeu &jeu, double dt);
    void affDetruireTXT(Jeu &jeu);
};

#endif
