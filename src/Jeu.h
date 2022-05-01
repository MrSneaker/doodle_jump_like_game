#ifndef JEU_H
#define JEU_H

#include <iostream>
#include "vec2.h"
#include "Personnage.h"
#include "Monstre.h"
#include "bonus.h"
#include "Ecran.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include <chrono>

using namespace std;

class Jeu
{
private:
    Personnage perso;
    bonus bonu[4];     // pareil que monstre, dans l'idée
    Monstre monstr[4]; // fais une fonction initMonstre qui créée les différent types de monstre
    vector<Plateforme> p;
    vector<Ecran> e;
    

public:
    Jeu();
    ~Jeu();
    const Personnage &getConstPersonnage() const;
    const Monstre &getConstMonstre(int i) const;
    const bonus &getConstBonus(int i) const;
    char getCh();
    const vector<Plateforme> &getPlateforme() const;
    void actionsAutomatiques(double dt);
    bool actionClavier(const char touche, double dt);
    void RecommencerJeu();
    void finJeu();
    void update(double dt);
    void InitPersonnage();
    void InitMonstre();
    void InitBonus();
    void InitPlat();
    void updateEcran(double dt);
    Ecran locEc();/*! \brief renvoie l'écran dans lequel se situe la caméra.*/
};

#endif