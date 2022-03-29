#include "Jeu.h"

#include <assert.h>
#include <iostream>

using namespace std;

Jeu::Jeu(){


}


Jeu::~Jeu(){

}


Personnage& Jeu::getPersonnage () {
    return perso; 
}


const Personnage& Jeu::getConstPersonnage() const {
return perso;
}

const Monstre& Jeu::getConstMonstre() const{
return monstr;
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
    monstr.bougeAuto();
}














