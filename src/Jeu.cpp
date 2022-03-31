#include "Jeu.h"

#include <assert.h>
#include <iostream>

using namespace std;

Jeu::Jeu(){
perso.~Personnage();
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
		//pasfleche;
		//vitesse.x -=0,01;
		
	}
	

}


void Jeu::InitPersonnage()
{
   perso.setPos(10.5,7.5);
   perso.setVit(1);
}

void Jeu::InitMonstre()
{
   int i;
   time_t t;
   srand((unsigned) time(&t));
   for (i=0;i<4;i++)
   {
	   monstr[i].setPos(rand()%100, rand()%100);
	   monstr[i].setVitM(0);
	   monstr[i].setTailleM(rand()%4);
	   monstr[i].setResistance(0);
	   monstr[i].enVie=true;
   }
}


void Jeu::InitBonus()
{
	int i;
   time_t t;
   srand((unsigned) time(&t));
   for (i=0;i<4;i++)
   {
	   bonu[i].setPosBonus(rand()%100, rand()%100);
	   bonu[i].setDuree(1);

   }

}




void Jeu::RecommencerJeu(){

}

void Jeu::update(){

}















