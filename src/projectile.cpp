#include "projectile.h"
#include <iostream>

projectile::projectile(float x, float y,float dx,float dy){
    p.x=x;
    p.y=y;
    direction.x=dx;
    direction.y=dy;
    existe=true;
    cout<<"proj existe ? :"<<existe<<endl;
}

projectile::~projectile(){

}

void projectile::Update(){
        p.x+=direction.x;
        p.y+=direction.y;
}

void projectile::Suppr(){
    existe=false;
}

Vec2 projectile::getdir() const{
    return direction;
}

Vec2 projectile::getpos() const{
    return p;
}