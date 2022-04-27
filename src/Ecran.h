#ifndef __ECRAN_H__
#define __ECRAN_H__

using namespace std;

#include "Plateforme.h"
#include "bonus.h"
#include "Monstre.h"
#include <iostream>

class Ecran
{
private:
    int debutEcran;
    int finEcran;
    int nbPlEc;

public:
    Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p, bonus b[4], Monstre m[4]);
    int getDebutEc() const;
    int getFinEc() const;
    void detruireEc(vector<Plateforme> &p, bonus b[4], Monstre m[4],int nbPl);
    int getNbPlEc() const;
    ~Ecran();
};

#endif