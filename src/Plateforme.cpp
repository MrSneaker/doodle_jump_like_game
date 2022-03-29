#include "Plateforme.h"

Plateforme::Plateforme(){
    pos.x=pos.y=0;
    dir.x=dir.y=0;
    taille=0;
    res=-1;
}

Plateforme::~Plateforme(){
}

Vec2 Plateforme::getPos() const {
    return pos;
}

void Plateforme::setPos(Vec2 p){
    pos=p;
}

Vec2 Plateforme::getDir() const{
    return dir;
}

float Plateforme::getTaille() const{
    return taille;
}

void Plateforme::setTaille(float x){
    taille=x;
}

int Plateforme::getRes() const{
    return res;
}

void Plateforme::setRes(int n){
    res=n;
}

void Plateforme::deplacerD(){
    dir.x=1;
    pos.x+=dir.x;
}

void Plateforme::deplacerG(){
    dir.x=-1;
    pos.x+=dir.x;
}

void Plateforme::monter(){
    dir.y=1;
    pos.y+=dir.y;
}

void Plateforme::descendre(){
    dir.y=-1;
    pos.y+=dir.y;
}