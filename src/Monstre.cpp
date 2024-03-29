#include "Monstre.h"
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Monstre::Monstre()
{
    position.x = 0;
    position.y = 0;
    resistance = 0;
    direction.x = 0;
    direction.y = 0;
    taille.x = 0;
    taille.y = 0;
    vitesse = 1;
    enVie = false;
}

Monstre::~Monstre()
{
}

Vec2 Monstre::getPos() const
{
    return position;
}

void Monstre::setPos(float x, float y)
{
    position.x = x;
    position.y = y;
}

Vec2 Monstre::getDirM() const
{
    return direction;
}

void Monstre::setDirM(float x, float y)
{
    direction.x = x;
    direction.y = y;
}

int Monstre::getTypeM() const
{
    return TypeM;
}

void Monstre::setTypeM(int n)
{
    TypeM = n;
}

void Monstre::Update(double dt)
{
    position.y += direction.y * dt;
    position.x += direction.x * dt;
}

float Monstre::getVitM() const
{
    return vitesse;
}

void Monstre::setVitM(float v)
{
    vitesse = v;
}

Vec2 Monstre::getTailleM() const
{
    return taille;
}

void Monstre::setTailleM(float tx, float ty)
{
    taille.x = tx;
    taille.y = ty;
}

int Monstre::getResistance()
{
    return resistance;
}

void Monstre::setResistance(int r)
{
    resistance = r;
}

void Monstre::bougeAuto(double dt)
{
    if (enVie == true)
    {
        if (position.y > 11.5)
        {
            direction.y = -1;
            Update(dt);
        }
        else if (position.y < 0.5)
        {
            direction.y = 1;
            Update(dt);
        }
        else
            Update(dt);
    }
}

void Monstre::descRes()
{
    resistance--;
}

void Monstre::testRegression()
{
    cout<<"test de regression monstre : "<<endl;
    Monstre m1;
    double dt = 0.1;
    assert(m1.position.x == 0);
    assert(m1.position.y == 0);
    assert(m1.direction.x == 0);
    assert(m1.direction.y == 0);
    assert(m1.vitesse == 1);
    assert(m1.resistance == 0);
    assert(m1.taille.x == 0);
    assert(m1.taille.y == 0);
    assert(m1.enVie == false);
    m1.setPos(10, 10);
    assert(m1.position.x == m1.getPos().x);
    assert(m1.position.y == m1.getPos().y);
    cout << "pos x : " << m1.getPos().x << endl;
    cout << "pos y : " << m1.getPos().y << endl;
    m1.setVitM(2);
    m1.setDirM(0,1);
    m1.Update(dt);
    m1.setResistance(2);
    m1.setTailleM(2, 2);
    assert(m1.taille.x == 2);
    assert(m1.taille.x == 2);
    assert(m1.vitesse == 2);
    assert(m1.resistance == 2);
    assert(m1.position.x == m1.getPos().x);
    assert(m1.position.y == m1.getPos().y);
    assert(m1.direction.y == 1);
    cout << "direction en x monstre : " << m1.getDirM().x << endl;
    cout << "direction en y monstre : " << m1.getDirM().y << endl;
    cout << "pos x monstre : " << m1.getPos().x << endl;
    cout << "pos y monstre : " << m1.getPos().y << endl;
    cout << "vitesse monstre : " << m1.getVitM() << endl;
    cout << "resistance monstre : " << m1.getResistance() << endl;
    cout << "taille monstre x: " << m1.getTailleM().x << endl;
    cout << "taille monstre y: " << m1.getTailleM().y << endl;
    cout<<endl;
}