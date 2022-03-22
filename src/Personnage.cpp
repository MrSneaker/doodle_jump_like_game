#include "Personnage.h"
#include <assert.h>
#include <iostream>

using namespace std;

Personnage::Personnage(){
    position.x=0;
    position.y=0;
    projectile=NULL;
    direction={0,0};
    vitesse=1;
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

float Personnage::getVit() const{
    return vitesse;
}

void Personnage::setVit(float v){
    vitesse=v;
}

void Personnage::deplacerD(){
    direction={1*vitesse,0};
    position.x=position.x+direction.at(0);
}

void Personnage::deplacerG(){
    direction={-1*vitesse,0};
    position.x=position.x+direction.at(0);
}

void Personnage::saut(){
    direction={0,1*vitesse};
    position.y=position.y+direction.at(1);
}

void Personnage::tombe(){
    direction={0,-1*vitesse};
    position.y=position.y+direction.at(1);
}

const string& Personnage::getNom() const{
    return nom;
}

void Personnage::setNom(const string nomP){
    nom = nomP;
}


