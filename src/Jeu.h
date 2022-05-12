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
    float tps = 0;        // temps bonus
    float tpsSaut = 0;    // temps saut
    float camX = 0;       // clone logique de la caméra des affichages,  permettant la condition de mort.
    const int NB_BONUS = 5;
    const int NB_MONSTRE = 4;
    Personnage perso;     /*! \brief Personnage controlé par le joueur*/
    bonus bonu[5];        /*! \brief Tableau statique de bonus de taille NB_BONUS*/
    Monstre monstr[4];    /*! \brief Tableau statique de monstre de taille NB_MONSTRE*/
    vector<Plateforme> p; /*! \brief Tableau dynamique de plateforme*/
    vector<Ecran> e;      /*! \brief Tableau dynamique d'écran*/

public:
    Jeu(); /*! \brief constructeur du jeu, appel la procédure Init() pour initialiser l'entièreté de ses composantes.*/
    ~Jeu();
    bool Ptombe;  /*! \brief Booléen vrai si le personnage tombe, faux sinon, vrai par défaut.*/
    bool Psaute;  /*! \brief Booléen vrai si le personnage saute, faux sinon, faux par défaut.*/
    bool Pdroite; /*! \brief Booléen vrai si le personnage va à droite, faux sinon, faux par défaut.*/
    bool Pgauche; /*! \brief Booléen vrai si le personnage va à gauche, faux sinon, faux par défaut.*/
    bool Ptire;   /*! \brief Booléen vrai si le personnage tir, faux sinon, faux par défaut.*/
    bool PcollPl;
    bool Mtouche1;
    bool Mtouche2;
    int score;
    const Personnage &getConstPersonnage() const;     /*! \brief Renvoie une référence au personnage et ses caractéristiques pour l'affichage texte et SDL*/
    const Monstre &getConstMonstre(int i) const;      /*! \brief Renvoie une référence au monstre numéro \param i et ses caractéristiques pour l'affichage texte et SDL*/
    const bonus &getConstBonus(int i) const;          /*! \brief Renvoie une référence au bonus numéro \param i et ses caractéristiques pour l'affichage texte et SDL*/
    const vector<Plateforme> &getPlateforme() const;  /*! \brief Renvoie une référence au tableau dynamique de plateforme et ses caractéristiques pour l'affichage texte et SDL */
    void actionsAutomatiques(double dt);              /*! \brief Procédure gérant les déplacements automatiques des éléments du jeu (monstres et plateformes) en fonction de la vitesse de mise à jour \param dt*/
    bool actionClavier(const char touche, double dt); /*! \brief Gère les actions clavier du joueur en fonction d'un char \param touche et de la vitesse de mise à jour \param dt. Renvoie faux si on presse 'q', vrai sinon. */
    void RecommencerJeu();                            /*! \brief */
    void finJeu();                                    /*! \brief */
    void update(double dt);                           /*! \brief Met à jour tous les éléments par rapport au intéractions entre eux, en fonction de la vitesse de mise à jour \param dt.*/
    void InitPersonnage();                            /*! \brief Initialise la position du personnage au milieu de l'écran, sa vitesse à 1 et la position vertical logique de la caméra.*/
    void InitMonstre();                               /*! \brief Inialise de façon aléatoire la taille, la résistance, et si le monstre bouge ou non.*/
    void InitBonus();                                 /*! \brief Initialise les bonus (leurs noms et leurs vitesse)*/
    void InitEc();                                    /*! \brief Initialise les 3 premiers écrans du jeu*/
    void Init();                                      /*! \brief Initialise tous les éléments composant le jeu*/
    void updateEcran(double dt);                      /*! \brief Supprime l'écran passé et en créé un nouveau ensuite. */
    Ecran locEc();                                    /*! \brief renvoie l'écran dans lequel se situe la caméra.*/
};

#endif