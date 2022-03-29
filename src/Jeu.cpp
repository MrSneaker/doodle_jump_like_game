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

const Monstre& Jeu::getConstMonstre() const{
	return monstr[4];
}


vector<Plateforme> Jeu::getPlateforme() const{
	return p;
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
	monstr[4].bougeAuto();
	 if(actionClavier==false)
	{
		pasfleche;
		vitesse.x -=0,01;
		
	}
	

}

void Jeu::RecommencerJeu(){

}

void Jeu::update(){

}















