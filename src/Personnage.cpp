#include "Personnage.h"
#include <assert.h>
#include <iostream>

using namespace std;

Personnage::Personnage(){
    position.x=0;
    position.y=0;
    projectile={};
    direction={0,0};
    vitesse=1;
    nom="p0";
    enVie=true;
}

Personnage::~Personnage(){
    if(projectile.size()!=0){
        projectile.clear();
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

void Personnage::setPos(float x, float y){
    position.x=x;
    position.y=y;
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
    direction.at(0)=1*vitesse;
    position.x=position.x+direction.at(0);
}

void Personnage::deplacerG(){
    direction.at(0)=-1*vitesse;
    position.x=position.x+direction.at(0);
}

void Personnage::saut(){
    direction.at(1)=1*vitesse;
    position.y=position.y+direction.at(1);
}

void Personnage::tombe(){
    direction.at(1)=-1*vitesse;
    position.y=position.y+direction.at(1);
}

const string& Personnage::getNom() const{
    return nom;
}

void Personnage::setNom(const string nomP){
    nom = nomP;
}

void Personnage::creerProj(){
    vector<float> a = {} ;
    projectile.push_back(a);
}

void Personnage::detruitProj(){
    projectile.erase(projectile.end()-1);
}

vector<float> Personnage::getProjectile(int n) const{
    return projectile.at(n);
}

void Personnage::testRegression(){
    Personnage p1;
    assert(p1.position.x==0);
    assert(p1.position.y==0);
    assert(p1.projectile.size()==0);
    assert(p1.direction.at(0)==0);
    assert(p1.direction.at(1)==0);
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
    assert(p1.direction.at(0)==-2);
    assert(p1.direction.at(1)==-2);
    cout<<"direction en x: "<<p1.getDir().at(0)<<endl;
    cout<<"direction en y: "<<p1.getDir().at(1)<<endl;
    cout<<"pos x : "<<p1.getPos().x<<endl;
    cout<<"pos y : "<<p1.getPos().y<<endl;
    cout<<"vitesse : "<<p1.getVit()<<endl;
    for(int i=0;i<3;i++){
        p1.creerProj();
        assert(p1.projectile.size()==i+1);
    }
    for(int i=0;i<3;i++){
        p1.projectile.at(i)={0+float(i),10};
        assert(p1.projectile.at(i).at(0)==0+float(i));
        assert(p1.projectile.at(i).at(1)==10);
        cout<<"projectile "<<i<<" en x: "<<p1.getProjectile(i).at(0)<<endl;
        cout<<"projectile "<<i<<" en y: "<<p1.getProjectile(i).at(1)<<endl;
    }
    for(int i=0;i<3;i++){
        p1.detruitProj();
        assert(p1.projectile.size()==3-(i+1));
    }
    


}

