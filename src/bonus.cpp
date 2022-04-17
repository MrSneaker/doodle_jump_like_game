#include "bonus.h"
#include <assert.h>
#include <iostream>

bonus::bonus()
{
    position.x = 0;
    position.y = 100;
    duree = 0;
    vitesse = 0;
    taille.x = 0;
    taille.y = 0;
    nomBonus = "b0";
    estPris == true;
}

bonus::~bonus()
{
}

Vec2 bonus::getPosBonus() const
{
    return position;
}

void bonus::setPosBonus(float x, float y)
{
    position.x = x;
    position.y = y;
}

Vec2 bonus::getTailleB() const
{
    return taille;
}

void bonus::setTailleB(float x, float y)
{
    taille.x = x;
    taille.y = y;
}

float bonus::getVitB() const
{
    return vitesse;
}

void bonus::setVitB(float v)
{
    vitesse = v;
}

string bonus::getNomB() const
{
    return nomBonus;
}

void bonus::setNomB(const string nombonus)
{
    nomBonus = nombonus;
}

float bonus::getDuree() const
{
    return duree;
}

void bonus::setDuree(float d)
{
    duree = d;
}

void bonus::testRegression()
{
    bonus p1;
    assert(p1.position.x == 0);
    assert(p1.position.y == 0);
    assert(p1.vitesse == 0);
    assert(duree == 0);
    assert(p1.nomBonus == "b0");
    p1.setNomB("testBonus");
    assert(p1.nomBonus == "testBonus");
    cout << "nom bonus: " << p1.getNomB() << endl;
    p1.setPosBonus(10, 10);
    assert(p1.position.x == 10);
    assert(p1.position.y == 10);
    cout << "pos x : " << p1.getPosBonus().x << endl;
    cout << "pos y : " << p1.getPosBonus().y << endl;
    p1.setVitB(2);
    assert(p1.vitesse == 2);
    cout << "vitesse : " << p1.getVitB() << endl;
    p1.setDuree(4.34);
    assert(p1.duree == float(4.34));
    cout << "duree bonus : " << p1.getDuree() << endl;
}