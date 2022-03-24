#include "bonus.h"


bonus::bonus(/* args */)
{
    p.x=0;
    p.y=0;
    duree=0;
    vitesse=0;
}

bonus::~bonus()
{
    p.x=0;
    p.y=0;
    duree=0;
    vitesse=0;
}

Vec2 bonus::getPosBonus() const{
    return p;
}

void bonus::setPosBonus(float x, float y){
    p.x=x;
    p.y=y;
}

float bonus::getVitB() const{
    return vitesse;
}

void bonus::setVitB(float v){
    vitesse=v;
}

const string& bonus::getNomB() const{
    return nomBonus;
}

void bonus::setNomB(const string nombonus){
    nomBonus = nombonus;
}

float bonus::getDuree() const{
    return duree;
}

void bonus::setDuree(float d){
    duree=d;
}
