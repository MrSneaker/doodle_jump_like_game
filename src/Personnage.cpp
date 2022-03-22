#include "Personnage.h"
#include <assert.h>

using namespace std;

Personnage::Personnage(){
    position.x=0;
    position.y=0;
    projectile=NULL;
    direction={0,0};
    vitesse=0;
    nom="p0";
    enVie=true;
}

Personnage::~Personnage(){
    if(projectile!=NULL){
        delete[] projectile;
    }
    position.x=0;
    position.y=0;
    direction={0,0};
    vitesse=0;
    nom="p0";
}

pos Personnage::getPos() const{
    return position;
}

void Personnage::setPos(pos p){
    position=p;
}

vector<float> Personnage::getDir() const{
    return direction;
}

void Personnage::setDir(vector<float> d){
    direction=d;
}


