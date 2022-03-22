#include "Monstre.h"
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

Monstre::Monstre(){
    position.x=0;
    position.y=0;
    resistance=0;
    direction={0,0};
    vitesse=0;
    
}

Monstre::~Monstre(){
    position.x=0;
    position.y=0;
    direction={0,0};
    resistance=0;
    vitesse=0;
    
}

pos Monstre::getPos() const{
    return position;
}

void Monstre::setPos(pos p){
    position=p;
}

vector<float> Monstre::getDirM() const{
    return direction;
}


float Monstre::getVitM() const{
    return vitesse;
}

void Monstre::setVitM(float v){
    vitesse=v;
}

float Monstre::getTailleM() const{
    return taille;
}

void Monstre::setTailleM(float t){
    taille=t;
}

int Monstre::getResistance(){
    return resistance;
}

void Monstre::setResistance(int r){
    resistance=r;
}
