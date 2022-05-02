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
    bool existe;
    projectile(float x, float y, float dx, float dy); /*! \brief construit un projectile au coordonnées indiquées \param x, \param y et sa directions indiquées
                                                      en paramètres aussi \param dx, \param dy*/
    ~projectile();                                    /*! \brief destructeur */
    void Update(double dt);                           /*! \brief met à jour la position du projectile*/
    Vec2 getdir() const;                              /*! \brief renvoie le vecteur de direction du projectile*/
    Vec2 getpos() const;                              /*! \brief renvoie le vecteur de position du projectile*/
    void Suppr();                                     /*! \brief Procédure de suppression d'un projectile*/
};

#endif