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
    projectile(float x,float y);/*! \brief construit un projectile au coordonnées indiquées \param x, \param y*/
    ~projectile();/*! \brief destructeur */
    void Update();/*! \brief met à jour la position du projectile*/
};




#endif