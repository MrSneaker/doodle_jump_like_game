#ifndef __PLATEFORME_H__
#define ___PLATEFORME_H__
#include "vec2.h"

using namespace std;


class Plateforme
{
private:
    Vec2 pos;
    Vec2 dir;
    float taille;
    int res;
public:
    Plateforme();/*! \brief pos à 0, dir à 0, taille à 0, res à NULL*/
    ~Plateforme();
    Vec2 getPos() const; /*! \brief renvoie la position de la plateforme*/
    void setPos(Vec2 p); /*! \brief modifie la position d'une plateforme à partir d'un vec2 \param p en paramètre*/
    Vec2 getDir() const; /*! \brief renvoie la direction de la plateforme*/
    float getTaille() const; /*! \brief renvoie la taille d'une plateforme*/
    void setTaille(float x); /*! \brief modifie la taille de la plateforme à partir d'un float \param n en paramètre*/
    int getRes() const; /*! \brief renvoie la resistance d'une plateforme*/
    void setRes(int n); /*! \brief modifie la resistance de la plateforme à partir d'un float \param n en paramètre*/
    void deplacerD(); /*! \brief déplace une palteforme à droite et modifie sa position en x de +1*/
    void deplacerG(); /*! \brief déplace une palteforme à gauche et modifie sa position en x de -1*/
    void monter(); /*! \brief déplace une palteforme vers le haut et modifie sa position en y de +1*/
    void descendre();/*! \brief déplace une palteforme vers le bas et modifie sa position en y de -1*/

};



#endif