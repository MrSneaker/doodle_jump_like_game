#ifndef __MONSTRE_H__
#define __MONSTRE_H__

#include <vector>
#include <string>
#include "vec2.h"

using namespace std;

class Monstre
{
    private:
        Vec2 position; /*! \brief structure contenant la position en coordonnées x,y*/
        Vec2 direction; /*! \brief le vecteur de direction des monstres*/
        float vitesse; /*! \brief la vitesse du monstre à l'écran*/
        float taille; /*! \brief la taille du monstre*/
        char TypeM[4]; /*! \brief tableau contenant 4 monstres différents */
        int resistance; /*! \brief résistance du monstre, combien de projectiles pour le tuer*/

    public:
        
        bool enVie; /*! \brief  le monstre est en vie ou pas*/
        Monstre(); /*! \brief position de base : 0,0; direction, vitesse à 0, type de monstre à 0, enVie à true */
        ~Monstre(); /*! \brief supprimes les projectiles, tout à 0(pos x,y; direction; vitesse), nom à NULL, enVie à NULL */
        Vec2 getPos() const; /*! \brief renvoie la position du monstre en x et y*/
        void setPos(float x, float y); /*! \brief met à jour la position du monstre selon une position en paramètre \param p*/
        int getTypeM(); /*! \brief renvoie le type de monstre (taille,couleur,forme)*/
        void setTypeM(); /*! \brief met a jour le type de monstre*/
        Vec2 getDirM() const; /*! \brief renvoie la direction du monstre*/
        void deplacerD();/*! \brief déplace le monstre à droite et modifie sa position x de +1*/
        void deplacerG();/*! \brief déplace le monstre à gauche et modifie sa position x de -1*/
        float getVitM() const; /*! \brief renvoie la vitesse du monstre */
        void setVitM(float v); /*! \brief met à jour la vitesse du monstre selon un parametre \param v*/
        float getTailleM() const;  /*! \brief renvoie la taille du pixel du monstre*/
        void setTailleM(float t); /*! \brief met a jour la taille du pixel du monstre*/
        int getResistance(); /*! \brief renvoie la resistance du monstree*/
        void setResistance(int r); /*! \brief  met a jour la resistance du monstre(s'il s'est pris un projectile par exemple*/
        void testRegression(); /*! \brief test toutes les fonctions de la classe Personnage*/

};


#endif