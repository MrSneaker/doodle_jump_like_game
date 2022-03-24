#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "vec2.h"

using namespace std;

class projectile
{
private:
    Vec2 p;
    Vec2 direction;
    bool existe;

public:
    projectile(float x,float y, float dx, float dy);/*! \brief construit un projectile au coordonnées indiquées \param x, \param y et sa directions indiquées 
                                                    en paramètres aussi \param dx, \param dy*/
    ~projectile();/*! \brief destructeur */
    void Update();/*! \brief met à jour la position du projectile*/
    Vec2 getdir() const;
    Vec2 getpos() const;
    void Suppr();
};




#endif