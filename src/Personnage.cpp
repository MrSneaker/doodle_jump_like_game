#include "Personnage.h"
#include <assert.h>
#include <iostream>

using namespace std;

Personnage::Personnage(){
    position.x=0;
    position.y=0;
    proj={};
    direction={0,0};
    vitesse=1;
    nom="p0";
    enVie=true;
}

Personnage::~Personnage(){
    if(proj.size()!=0){
        proj.clear();
    }
    position.x=0;
    position.y=0;
    direction={0,0};
    vitesse=0;
    nom="p0";
}

Vec2 Personnage::getPos() const{
    return position;
}

void Personnage::setPos(float x, float y){
    position.x=x;
    position.y=y;
}

Vec2 Personnage::getDir() const{
    return direction;
}

float Personnage::getVit() const{
    return vitesse;
}

void Personnage::setVit(float v){
    vitesse=v;
}

void Personnage::deplacerD(){
    direction.x=1*vitesse;
    position.x=position.x+direction.x;
}

void Personnage::deplacerG(){
    direction.x=-1*vitesse;
    position.x=position.x+direction.x;
}

void Personnage::saut(){
    direction.y=1*vitesse;
    position.y=position.y+direction.y;
}

void Personnage::tombe(){
    direction.y=-1*vitesse;
    position.y=position.y+direction.y;
}

const string& Personnage::getNom() const{
    return nom;
}

void Personnage::setNom(const string nomP){
    nom = nomP;
}

void Personnage::creerProj(){
    projectile a(position.x,position.y,0,10);
    proj.emplace(proj.end(),a);
    proj.back().Update();
}

void Personnage::detruitProj(int i){
    proj.at(i).Suppr();
    proj.erase(proj.begin()+i);
}

projectile Personnage::getProjectile(int n) const{
    return proj.at(n);
}

void Personnage::testRegression(){
    Personnage p1;
    assert(p1.position.x==0);
    assert(p1.position.y==0);
    assert(p1.proj.size()==0);
    assert(p1.direction.x==0);
    assert(p1.direction.y==0);
    assert(p1.vitesse==1);
    assert(p1.nom=="p0");
    assert(p1.enVie==true);
    p1.setNom("test");
    assert(p1.nom=="test");
    cout<<"nom : "<<p1.getNom()<<endl;
    p1.setPos(10,10);
    assert(p1.position.x=10);
    assert(p1.position.y==10);
    cout<<"pos x : "<<p1.getPos().x<<endl;
    cout<<"pos y : "<<p1.getPos().y<<endl;
    p1.deplacerD();
    p1.setVit(2);
    p1.deplacerD();
    p1.deplacerG();
    p1.saut();
    p1.saut();
    p1.tombe();
    assert(p1.vitesse==2);
    assert(p1.position.x==11);
    assert(p1.position.y==12);
    assert(p1.direction.x==-2);
    assert(p1.direction.y==-2);
    cout<<"direction en x: "<<p1.getDir().x<<endl;
    cout<<"direction en y: "<<p1.getDir().y<<endl;
    cout<<"pos x : "<<p1.getPos().x<<endl;
    cout<<"pos y : "<<p1.getPos().y<<endl;
    cout<<"vitesse : "<<p1.getVit()<<endl;
    p1.creerProj();
    p1.creerProj();
    p1.creerProj();
    assert(p1.proj.size()==3);
    for(int i=0;i<3;i++){
        assert(p1.proj.at(i).getdir().x==0);
        assert(p1.proj.at(i).getdir().y==10);
        cout<<"projectile direction "<<i<<" en x: "<<p1.getProjectile(i).getdir().x<<endl;
        cout<<"projectile direction "<<i<<" en y: "<<p1.getProjectile(i).getdir().y<<endl;
        cout<<"projectile "<<i<<" en x: "<<p1.getProjectile(i).getpos().x<<endl;
        cout<<"projectile "<<i<<" en y: "<<p1.getProjectile(i).getpos().y<<endl;
    }
    for(int i=3;i>0;i--){
        p1.detruitProj(i-1);
    }
    assert(p1.proj.size()==0);
    


}

