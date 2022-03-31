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
        bonus bonu[4];//pareil que monstre, dans l'idée
        Monstre monstr[4];// fais une fonction initMonstre qui créée les différent types de monstre
        vector<Plateforme> p;


        



    public:
        Jeu();
        ~Jeu();
        const Personnage &getConstPersonnage() const;
        const Monstre & getConstMonstre(int i) const; 
        const bonus & getConstBonus(int i) const;
        char getCh();
        vector<Plateforme> getPlateforme() const;
        void actionsAutomatiques();
        bool actionClavier(const char touche);
        void RecommencerJeu();
        void finJeu();
        void update();
        void InitPersonnage();
        void InitMonstre();
        void InitBonus();
        void clear();

};

#endif