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
    int debutEcran; /*! \brief Entier désignant la position à laquelle débute l'écran.*/
    int finEcran;   /*! \brief Entie désignant la position à laquelle fini l'écran.*/
    int nbPlEc;     /*! \brief Entier désignant le nombre de plateformes dans l'écran.*/
    int NB_MONSTRE = 4;
    int NB_BONUS = 4;

public:
    Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p, bonus b[4], Monstre m[4]); /*! \brief constructeur permettant de construire un écran à partir de sa position de début et de fin ( \param posDebut, \param posFin), ainsi qu'à son nombre de plateformes \param nbPlat, en prenant en paramètres tous les éléments du jeu nécessaire à la construction (tableau dynamique de plateforme passé en référence  \param p, tableau statique de taille NB_BONUS \param b, tableau statique de taille NB_MONSTRE \param m). */
    int getDebutEc() const;                                                                       /*! \brief Renvoie un entier désignant le début de l'écran.*/
    int getFinEc() const;                                                                         /*! \brief Renvoie un entier désignant la fin de l'écran.*/
    void detruireEc(vector<Plateforme> &p, bonus b[4], Monstre m[4], int nbPl);                   /*! \brief Procédure de destruction des éléments constituant l'écran à partir des paramètres \param p un tableau dynamique passé en référence, deux tableau statique de tailles NB_BONUS et NB_MONSTRE \param b et \param m*/
    int getNbPlEc() const;                                                                        /*! \brief Renvoie le nombre de plateformes de l'écran.*/
    ~Ecran();
};

#endif