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
    JeuModeTXT();
    ~JeuModeTXT();
    void updatePlateau(Jeu &jeu);
    void affichageTXT(Jeu &jeu);
    void boucleAffTXT();
};




#endif