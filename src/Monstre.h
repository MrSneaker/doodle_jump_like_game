#ifndef __MONSTRE_H__
#define __MONSTRE_H__

#include <vector>
#include <string>
#include "vec2.h"

using namespace std;

class Monstre
{
private:
    Vec2 position;  /*!  structure contenant la position en coordonnées x,y*/
    Vec2 direction; /*!  le vecteur de direction des monstres*/
    float vitesse;  /*!  la vitesse du monstre à l'écran*/
    Vec2 taille;    /*!  la taille du monstre*/
    int TypeM;      /*!  entier représentant le monstre voulu */
    int resistance; /*!  résistance du monstre, combien de projectiles pour le tuer*/

public:
    /*! \brief  le monstre est en vie ou pas*/
    bool enVie;
    /*! \brief constructeur, position de base : 0,0; direction, vitesse à 0, type de monstre à 0, enVie à true */
    Monstre();
    /*! \brief supprimes les projectiles, tout à 0(pos x,y; direction; vitesse), nom à NULL, enVie à NULL */
    ~Monstre();
    /*! \brief renvoie la position du monstre en x et y*/
    Vec2 getPos() const;
    /*! \brief met à jour la position du monstre selon une position en paramètre \param x, \param y*/
    void setPos(float x, float y);
    /*! \brief renvoie le type de monstre (taille,couleur,forme)*/
    int getTypeM() const;
    /*! \brief met a jour le type de monstre*/
    void setTypeM(int n);
    /*! \brief renvoie la direction du monstre*/
    Vec2 getDirM() const;
    /*! \brief met à jour la direction par rapport au paramètres \param x, \param y donnés*/
    void setDirM(float x, float y);
    /*! \brief gère le mouvement du monstre en fonction d'un paramètre \param dt*/
    void Update(double dt);
    /*! \brief renvoie la vitesse du monstre */
    float getVitM() const;
    /*! \brief met à jour la vitesse du monstre selon un parametre \param v*/
    void setVitM(float v);
    /*! \brief renvoie la taille du pixel du monstre*/
    Vec2 getTailleM() const;
    /*! \brief met a jour la taille du monstre par rapport aux paramètres \param tx, \param ty.*/
    void setTailleM(float tx, float ty);
    /*! \brief renvoie la resistance du monstre*/
    int getResistance();
    /*! \brief permet aux monstres de se déplacer tout seul selon la vitesse de raffraichissement \param dt.*/
    void bougeAuto(double dt);
    /*! \brief  met a jour la resistance du monstre par rapport à l'entier en paramètre \param r.*/
    void setResistance(int r);
    /*! \brief test toutes les fonctions de la classe Monstre*/
    void testRegression();
    /*! \brief décrémente la res de 1*/
    void descRes();
};

#endif