#include "JeuModeTXT.h"

JeuModeTXT::JeuModeTXT(){

}

JeuModeTXT::~JeuModeTXT(){
}

char cadre[15][21] = {
        "####################",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "####################"
    };

void updatePlateau(Jeu &jeu){
    for(int i=0;i<15;i++){
        for(int j=0;j<21;j++){
            if((jeu.getConstPersonnage().getPos().x==i)&&(jeu.getConstPersonnage().getPos().y==j)&&(jeu.getConstPersonnage().enVie==true)){
                cadre[i][j]='O';
            }
            for(int m=0;m<4;m++){
                if((jeu.getConstMonstre(m).getPos().x==i)&&(jeu.getConstMonstre(m).getPos().y==j)&&(jeu.getConstMonstre(m).enVie==true)){
                    if(jeu.getConstMonstre(m).getTailleM()==1) cadre[i][j]='M';
                    else cadre[i][j]='MM';
                }
            }
            for(int p=0;p<jeu.getPlateforme().size();p++){
                if((jeu.getPlateforme().at(p).getPos().x==i)&&(jeu.getPlateforme().at(p).getPos().y==j)&&(jeu.getPlateforme().at(p).estAfficheable()==true)){
                    if(jeu.getPlateforme().at(p).getTaille()==1) cadre[i][j]='***';
                }
            }
            for(int b=0;b<4;b++){
                if((jeu.getConstBonus(b).getPosBonus().x==i)&&(jeu.getConstBonus(b).getPosBonus().y==j)&&(jeu.getConstBonus(b).estPris==false)){
                    if(jeu.getConstBonus(b).getNomB()=="jetpack") cadre[i][j]='J';
                    if(jeu.getConstBonus(b).getNomB()=="hélice") cadre[i][j]='H';
                    if(jeu.getConstBonus(b).getNomB()=="ressort") cadre[i][j]='R';
                    if(jeu.getConstBonus(b).getNomB()=="boing") cadre[i][j]='B';
                }
            }

        }
    }
    char c=jeu.getCh();
    
}

void JeuModeTXT::affichageTXT(Jeu &jeu){    
    for(int i=0;i<15;i++){
        for(int j=0;j<21;j++){
            cout<<cadre[i][j];
        }
         cout<<endl;
    }
}   

void JeuModeTXT::boucleAffTXT(Jeu &jeu){
    updatePlateau(jeu);
    affichageTXT(jeu);
}