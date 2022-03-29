#include "Jeu.h"

#include <assert.h>
#include <iostream>

using namespace std;

Jeu::Jeu(){
	

}


Jeu::~Jeu(){

}




const Personnage& Jeu::getConstPersonnage() const {
	return perso;
}

const Monstre & Jeu::getConstMonstre(int i) const{
	return monstr[i];
}


vector<Plateforme> Jeu::getPlateforme() const{
	return p;
}

const bonus & Jeu::getConstBonus(int i) const{
	return bonu[i];
}

bool Jeu::actionClavier (const char touche) {
	switch(touche) {
		case 'g' :
				perso.deplacerG();
				break;
		case 'd' :
				perso.deplacerD();
				break;
		case 'z' :
				perso.creerProj();
				break;
		
                }
}

void Jeu::actionsAutomatiques () {
	for(int i=0;i<4;i++){
		monstr[i].bougeAuto();
	}
	
	 if(actionClavier()==false)
	{
		pasfleche;
		vitesse.x -=0,01;
		
	}
	

}

void Jeu::RecommencerJeu(){

}

void Jeu::update(){

}















