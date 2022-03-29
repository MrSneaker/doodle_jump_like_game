#include "Plateforme.h"

Plateforme::Plateforme(float posx,float posy,float dirx,float diry,float t,int resist){
    pos.x=posx;
    pos.y=posy;
    dir.x=dirx;
    dir.y=diry;
    taille=t;
    res=resist;
}

Plateforme::~Plateforme(){
}

Vec2 Plateforme::getPos() const {
    return pos;
}

void Plateforme::setPos(float x,float y){
    pos.x=x;
    pos.y=y;
}

Vec2 Plateforme::getDir() const{
    return dir;
}

void Plateforme::setDir(float x,float y){
    dir.x=x;
    dir.y=y;
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

void Plateforme::Update(){
        pos.x+=dir.x;
        pos.y+=dir.y;
}


bool Plateforme::estAfficheable(){
    if(res!=-1){
        if(res==0){
            return false;
        }
        else return true;
    }
    else return true;
}

void Plateforme::descRes(){
    res--;
}