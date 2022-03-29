#ifndef JEU_H
#define JEU_H

#include <iostream>
#include "vec2.h"
#include "Personnage.h"
#include "Monstre.h"
#include "bonus.h"
#include "Plateforme.h"
#include <vector>

using namespace std;

class Jeu
{
    private:
        Personnage perso;
        bonus bonu;
        Monstre monstr[4];
        vector<Plateforme>  p;






    public:
        Jeu();
        
        const Personnage &getConstPersonnage() const;
        const Monstre &getConstMonstre() const; 
        ~Jeu();
        vector<Plateforme> getPlateforme() const;
        void actionsAutomatiques();
        bool actionClavier(const char touche);
        void RecommencerJeu();
        void finJeu();
        void update();
        void clear();

};

#endif