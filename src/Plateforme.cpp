#include "Plateforme.h"
#include <assert.h>
#include <iostream>

Plateforme::Plateforme()
{
    pos.x = 0;
    pos.y = 0;
    dir.x = 0;
    dir.y = 0;
    taille.x = 0;
    taille.y = 0;
    res = 0;
}

Plateforme::Plateforme(float posx, float posy, float dirx, float diry, float tx, float ty, int resist)
{
    pos.x = posx;
    pos.y = posy;
    dir.x = dirx;
    dir.y = diry;
    taille.x = tx;
    taille.y = ty;
    res = resist;
}

Plateforme::~Plateforme()
{
}

const Vec2& Plateforme::getPos() const
{
    return pos;
}

void Plateforme::setPos(float x, float y)
{
    pos.x = x;
    if (pos.x == 0)
        pos.x = 1;
    pos.y = y;
    if (pos.y == 0)
        pos.y = 1 + taille.y;
}

Vec2 Plateforme::getDir() const
{
    return dir;
}

void Plateforme::setDir(float x, float y)
{
    dir.x = x;
    dir.y = y;
}

Vec2 Plateforme::getTaille() const
{
    return taille;
}

void Plateforme::setTaille(float x, float y)
{
    taille.x = x;
    taille.y = y;
}

int Plateforme::getRes() const
{
    return res;
}

void Plateforme::setRes(int n)
{
    res = n;
}

void Plateforme::Update(double dt)
{
    pos.x += dir.x * dt;
    pos.y += dir.y * dt;
}

float Plateforme::getVitM() const
{
    return vitesse;
}

void Plateforme::setVitM(float v)
{
    vitesse = v;
}

bool Plateforme::estAfficheable() const
{
    if (res != -1)
    {
        if ((res == 0))
        {
            return false;
        }
        else
            return true;
    }
    else
        return true;
}

void Plateforme::descRes()
{
    if (res != -1)
    {
        res--;
    }
}

void Plateforme::bougeAuto(double dt)
{
    if (estAfficheable())
    {
        if ((dir.y > 0) || (dir.y < 0))
        {
            if (pos.y > 11.5)
            {
                dir.y = -1;
                Update(dt);
            }
            else if (pos.y <= 0.5)
            {
                dir.y = 1;
                Update(dt);
            }
            else
                Update(dt);
        }
        else if ((dir.x > 0) || (dir.x < 0))
        {
            if (pos.x < posXbase)
            {
                dir.x = 4;
                Update(dt);
            }
            else if (pos.x > posXbase + 20)
            {
                dir.x = -4;
                Update(dt);
            }
            else
                Update(dt);
        }
    }
}

void Plateforme::testRegression()
{
    cout<<"test de regression Plateforme : "<<endl;
    Plateforme p1(0, 0, 0, 0, 0, 0, 0);
    assert(p1.pos.x == 0);
    assert(p1.pos.y == 0);
    assert(p1.dir.x == 0);
    assert(p1.dir.y == 0);
    assert(p1.res == 0);
    assert(p1.taille.x == 0);
    assert(p1.taille.y == 0);
    p1.setPos(10, 10);
    assert(p1.pos.x == 10);
    assert(p1.pos.y == 10);
    cout << "pos x : " << p1.getPos().x << endl;
    cout << "pos y : " << p1.getPos().y << endl;
    p1.setDir(-1, 0);
    assert(p1.dir.x == -1);
    assert(p1.dir.y == 0);
    p1.Update(1.0 / 60.0);
    assert(p1.pos.x == p1.getPos().x);
    assert(p1.pos.y == p1.getPos().y);
    cout << "dir en x: " << p1.getDir().x << endl;
    cout << "dir en y: " << p1.getDir().y << endl;
    cout << "pos x : " << p1.getPos().x << endl;
    cout << "pos y : " << p1.getPos().y << endl;
    p1.setRes(1);
    assert(p1.res == 1);
    cout << "res palteforme : " << p1.getRes() << endl;
    p1.descRes();
    assert(p1.res == 0);
    cout << "res palteforme apres descRes : " << p1.getRes() << endl;
    p1.setTaille(2,2);
    assert(p1.taille.x == 2);
    assert(p1.taille.y == 2);
    cout << "taille plateforme x: " << p1.getTaille().x << endl;
    cout << "taille plateforme y: " << p1.getTaille().y << endl;
    cout<<endl;
}