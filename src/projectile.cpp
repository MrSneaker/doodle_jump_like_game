#include "projectile.h"
#include <iostream>

projectile::projectile(float x, float y, float dx, float dy)
{
    p.x = x;
    p.y = y;
    direction.x = dx;
    direction.y = dy;
    existe = true;
    cout << "proj existe ? :" << existe << endl;
}

projectile::~projectile()
{
}

void projectile::Update(double dt)
{
    p.x += direction.x * dt;
    p.y += direction.y * dt;
}

void projectile::Suppr()
{
    existe = false;
}

Vec2 projectile::getdir() const
{
    return direction;
}

Vec2 projectile::getpos() const
{
    return p;
}