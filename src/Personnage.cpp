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

void Personnage::deplacerD(double dt){
    direction.y=1.25*(vitesse * dt);
    position.y=position.y+direction.y;
    if(position.y>6) position.y = 0;
}

void Personnage::deplacerG(double dt){
    direction.y=-1.25*(vitesse *dt);
    position.y=position.y+direction.y;
    if(position.y<0) position.y = 6;
}

void Personnage::saut(double dt){
    direction.x=-110*(vitesse * dt);
    position.x=position.x+direction.x;
    //if(position.x>8) position.x = 8;
}

void Personnage::tombe(double dt){
    direction.x=0.5*(vitesse * dt);
    position.x=position.x+direction.x;
}

const string& Personnage::getNom() const{
    return nom;
}

void Personnage::setNom(const string nomP){
    nom = nomP;
}

void Personnage::creerProj(){
    projectile a(position.x,position.y,0,1);
    proj.emplace(proj.end(),a);
    proj.back().Update(1.0/60);
}

void Personnage::detruitProj(int i){
    proj.at(i).Suppr();
    proj.erase(proj.begin()+i);
}

projectile Personnage::getProjectile(int n) const{
    return proj.at(n);
}

int Personnage::getNombreProj() const{
    return proj.size();
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
    assert(p1.position.x==10);
    assert(p1.position.y==10);
    cout<<"pos x : "<<p1.getPos().x<<endl;
    cout<<"pos y : "<<p1.getPos().y<<endl;
    p1.deplacerD(1.0 / 60.0);
    p1.setVit(2);
    p1.deplacerD(1.0/ 60.0);
    p1.deplacerG(1.0 / 60.0);
    p1.saut(1.0 / 60.0);
    p1.saut(1.0 / 60.0);
    p1.tombe(1.0 / 60.0);
    assert(p1.vitesse==2);
    assert(p1.position.x==p1.getPos().x);
    assert(p1.position.y==p1.getPos().y);
    assert(p1.direction.x==p1.getDir().x);
    assert(p1.direction.y==p1.getDir().y);
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
        assert(p1.proj.at(i).getdir().x==p1.getProjectile(i).getdir().x);
        assert(p1.proj.at(i).getdir().y==p1.getProjectile(i).getdir().y);
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

