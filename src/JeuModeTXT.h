#ifndef __JEUMODETXT_H__
#define __JEUMODETXT_H__

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include <iostream>

class JeuModeTXT
{
private:
    Jeu jeu;  /*! \brief Moteur du jeu contenant tous ses éléments.*/
    Vec2 cam; /*! \brief Caméra suivant le personnage, centrée en X (axe des ordonnées ici)*/
    char cadre[15][30] = {
        "#############################",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#############################"}; /*! \brief Cadre d'affichage du jeu*/

    const char cadreClear[15][30] = {
        "#############################",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#                           #",
        "#############################"}; /*! \brief Cadre permettant le raffraichissement du jeu.*/
    const int NB_BONUS = 5;
    const int NB_MONSTRE = 4;
    const int DIMX = 15;
    const int DIMY = 30;

public:
    JeuModeTXT();                           /*! \brief Constructeur du jeu TXT,initialise la position de la caméra à 0.*/
    ~JeuModeTXT();                          /*! \brief Destructeur du jeu TXT.*/
    void InitCam();                         /*! \brief Initialise la caméra sur la position du personnage + DIMX/2 (la moitié de la taille de l'écran en ordonnées).*/
    Vec2 convertPos(Vec2 pos);              /*! \brief Convertie une position logique (i.e venant du moteur de jeu Jeu.cpp) en une position d'affichage à partir d'un vecteur de position en paramètre \param pos.*/
    void updatePlateau(Jeu &jeu);           /*! \brief Met le plateau à jour en fonction d'un jeu en paramètre passé par référence \param jeu.*/
    void affichageTXT(Jeu &jeu);            /*! \brief Affiche le jeu \param jeu passé en référence en effaçant le terminal.  */
    void boucleAffTXT(Jeu &jeu, double dt); /*! \brief Boucle d'affichage du jeu en paramètre \param jeu passé en référence, réalisant l'update et l'affichage de ce dernier tant que le joueur n'a pas quitté ou perdu. Cela en fonction de la vitesse de mise à jour en paramètre \param dt.*/
    void affDetruireTXT();                  /*! \brief Efface le cadre de jeu en utilisant un cadre vide.*/
};

#endif
