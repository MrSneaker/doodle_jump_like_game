#include "Jeu.h"

#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

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





int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

char Jeu::getCh() { // lire un caractere si une touche a ete pressee
    char touche=0;
    if (kbhit()){
		touche = fgetc(stdin);
	}
        
    return touche;
}

bool Jeu::actionClavier (const char touche) {
	bool ok=true;
	switch(touche) {
		case 'g' :
				perso.deplacerG();
				break;
				ok = true;
		case 'd' :
				perso.deplacerD();
				break;
				ok = true;
		case 'r' :
				perso.creerProj();
				break;
				ok = true;
		case 'q' :
				return ok = false;
				break;
		
                }
				return ok;
}

/*void Jeu::actionsAutomatiques () {
	for(int i=0;i<4;i++){
		monstr[i].bougeAuto();
	}
	
	 if(actionClavier()==false)
	{
		//pasfleche;
		//vitesse.x -=0,01;
		
	}
	

}*/


void Jeu::InitPersonnage()
{
   perso.setPos(10,7);
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
	   monstr[i].setTailleM(rand()%2);
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
	for(int i=0;i<p.size();i++){
		if((perso.getPos().x==p.at(i).getPos().x)&&(perso.getPos().y==p.at(i).getPos().y)){
			perso.saut();
		}
	}
	for(int i=0;i<4;i++){
		if((perso.getPos().x==monstr[i].getPos().x)&&(perso.getPos().y==monstr[i].getPos().y)&&(monstr[i].enVie==true)){
			perso.tombe();
			perso.enVie=false;
		}
		if(perso.getNombreProj()!=0){
			for(int j=0;j<perso.getNombreProj();j++){
				if((perso.getProjectile(j).getpos().x==monstr[i].getPos().x)&&(perso.getProjectile(j).getpos().y==monstr[i].getPos().y)){
					monstr[i].descRes();
					if(monstr[i].getResistance()==0){
						monstr[i].enVie=false;
					}
					perso.detruitProj(j);
				}
			}
		}
	}
	for(int i=0;i<4;i++){
		if((perso.getPos().x==bonu[i].getPosBonus().x)&&(perso.getPos().y==bonu[i].getPosBonus().y)){
			if(bonu[i].getNomB()=="jetpack") perso.setVit(3);
			else if(bonu[i].getNomB()=="hélice") perso.setVit(2);
			else if(bonu[i].getNomB()=="ressort") perso.setVit(1.5);
			else if(bonu[i].getNomB()=="boing") perso.setVit(1.5);
			bonu[i].estPris=true;
		}
	}
		
	
}















