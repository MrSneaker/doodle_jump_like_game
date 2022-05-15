#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "vec2.h"

using namespace std;

class projectile
{
private:
    Vec2 p;
    Vec2 direction;

public:
    /*! \brief Booléen indiquant si oui ou non le projectile existe.*/
    bool existe;
    /*! \brief construit un projectile au coordonnées indiquées \param x, \param y et sa directions indiquées
                                                      en paramètres aussi \param dx, \param dy*/
    projectile(float x, float y, float dx, float dy);
    /*! \brief destructeur */
    ~projectile();
    /*! \brief met à jour la position du projectile*/
    void Update(double dt);
    /*! \brief renvoie le vecteur de direction du projectile*/
    Vec2 getdir() const;
    /*! \brief renvoie le vecteur de position du projectile*/
    Vec2 getpos() const;
    /*! \brief Procédure de suppression d'un projectile*/
    void Suppr();
};

#endif