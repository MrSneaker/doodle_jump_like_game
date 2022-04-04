#include "Jeu.h"



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

bool Jeu::actionClavier (const char touche, double dt) {
	bool ok=true;
	switch(touche) {
		case 'g' :
				perso.deplacerG(dt);
				cout<<perso.getPos().y;
				break;
				ok = true;
		case 'd' :
				perso.deplacerD(dt);
				cout<<perso.getPos().y;
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
   perso.setPos(8,8);
   perso.setVit(1);
}

void Jeu::InitMonstre()
{
   int i;
   time_t t;
   srand((unsigned) time(&t));
   for (i=0;i<4;i++)
   {
	   monstr[i].setVitM(0);
	   monstr[i].setTailleM(rand()%2);
	   monstr[i].setResistance(1);
	   monstr[i].enVie=true;
   }
}


void Jeu::InitBonus()
{
	int i;
	int j = 0;
   time_t t;
   srand((unsigned) time(&t));
   for (i=0;i<4;i++)
   {
		   	
			bonu[i].setDuree(5);
			if(rand()%100>90) bonu[i].setNomB("jetpack");
			if(rand()%100>60) bonu[i].setNomB("hélice");
			if(rand()%100>25) bonu[i].setNomB("ressort");
			if(rand()%100>75) bonu[i].setNomB("boing");
			bonu[i].estPris=false;
	}

}


void Jeu::InitPlat(){
	int i;
	time_t t;
	Plateforme p0(perso.getPos().x+1,perso.getPos().y,0,0,1,-1);
	p.emplace(p.begin(),p0);
	srand((unsigned)time(&t));
	for(i=1;i<12;i++){
		Plateforme tmp;
		tmp.setPos(rand()%14,rand()%19);
		if(rand()%100<=70) tmp.setRes(-1);
		else tmp.setRes(1); 
		tmp.setTaille(1);
		for(int j=0;j<4;j++){
			if(rand()%100>90){
				bonu[j].setPosBonus(tmp.getPos().x-1,tmp.getPos().y);
			}
			else if(rand()%100>60){
				monstr[j].setPos(tmp.getPos().x-1,tmp.getPos().y);
			}
		}
		p.emplace(p.begin()+i,tmp);
	}
	
}



void Jeu::RecommencerJeu(){

}

void Jeu::update(double dt){
	for(int i=0;i<p.size();i++){
		if((int(perso.getPos().x)==p.at(i).getPos().x)&&(int(perso.getPos().y)==p.at(i).getPos().y)){
			while(int(perso.getPos().x)!=p.at(i).getPos().x-3){
				perso.saut(dt);
			}
		}
		else perso.tombe(dt);
	}
	for(int i=0;i<4;i++){
		if((int(perso.getPos().x)==monstr[i].getPos().x)&&(int(perso.getPos().y)==monstr[i].getPos().y)&&(monstr[i].enVie==true)){
			perso.tombe(dt);
			perso.enVie=false;
		}
		if(perso.getNombreProj()!=0){
			for(int j=0;j<perso.getNombreProj();j++){
				while (perso.getProjectile(j).existe){
					perso.getProjectile(j).Update();
					if((perso.getProjectile(j).getpos().x==monstr[i].getPos().x)&&(perso.getProjectile(j).getpos().y==monstr[i].getPos().y)){
						monstr[i].descRes();
						if(monstr[i].getResistance()==0){
						monstr[i].enVie=false;
						}
						perso.detruitProj(j);
					}
					if(perso.getProjectile(j).getpos().y>=20){
						perso.detruitProj(j);
						cout<<"lol";
					}
					//cout<<perso.getProjectile(j).getpos().x; 
				}
				
			}
		}
	}
	for(int i=0;i<4;i++){
		if((int(perso.getPos().x)==bonu[i].getPosBonus().x)&&(int(perso.getPos().y)==bonu[i].getPosBonus().y)){
			std::chrono::high_resolution_clock timer;
			double tps=0;
			while(tps==bonu[i].getDuree()){
				auto start = timer.now();
				if(bonu[i].getNomB()=="jetpack") perso.setVit(3);
				else if(bonu[i].getNomB()=="hélice") perso.setVit(2);
				else if(bonu[i].getNomB()=="ressort") perso.setVit(1.5);
				else if(bonu[i].getNomB()=="boing") perso.setVit(1.5);
				auto stop = timer.now();
				tps+= std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
				cout<<tps;
			}
			bonu[i].estPris=true;
			perso.setVit(1);
		}
	}
	if(perso.getPos().x>=16) perso.enVie=false;	
	
}















