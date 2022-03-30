#include "Monstre.h"
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Monstre::Monstre(){
    position.x=0;
    position.y=0;
    resistance=0;
    direction.x=0;
    direction.y=0;
    vitesse=1;
    enVie=true;
    
}

Monstre::~Monstre(){    
}

Vec2 Monstre::getPos() const{
    return position;
}

void Monstre::setPos(float x, float y){
    position.x=x;
    position.y=y;
}

Vec2 Monstre::getDirM() const{
    return direction;
}

void Monstre::deplacerD(){
    direction.x=1*vitesse;
    position.x=position.x+direction.x;
}

void Monstre::deplacerG(){
    direction.x=-1*vitesse;
    position.x=position.x+direction.x;
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

void Monstre::testRegression(){
    Monstre m1;
    assert(m1.position.x==0);
    assert(m1.position.y==0);
    assert(m1.direction.x==0);
    assert(m1.direction.y==0);
    assert(m1.vitesse==1);
    assert(m1.resistance==0);
    assert(m1.taille==0);
    assert(m1.enVie==true);
    m1.setPos(10,10);
    assert(m1.position.x=10);
    assert(m1.position.y==10);
    cout<<"pos x : "<<m1.getPos().x<<endl;
    cout<<"pos y : "<<m1.getPos().y<<endl;
    m1.setVitM(2);
    m1.deplacerD();
    m1.deplacerD();
    m1.deplacerG();
    m1.setResistance(2);
    m1.setTailleM(2);
    assert(m1.taille==2);
    assert(m1.vitesse==2);
    assert(m1.resistance==2);
    assert(m1.position.x==12);
    assert(m1.position.y==10);
    assert(m1.direction.x==-2);
    cout<<"direction en x monstre : "<<m1.getDirM().x<<endl;
    cout<<"direction en y monstre : "<<m1.getDirM().y<<endl;
    cout<<"pos x monstre : "<<m1.getPos().x<<endl;
    cout<<"pos y monstre : "<<m1.getPos().y<<endl;
    cout<<"vitesse monstre : "<<m1.getVitM()<<endl;
    cout<<"resistance monstre : "<<m1.getResistance()<<endl;
    cout<<"taille monstre : "<<m1.getTailleM()<<endl;

}