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
            if((jeu.getConstPersonnage().getPos().x==i)&&(jeu.getConstPersonnage().getPos().y==j)){
                cadre[i][j]='O';
            }
            else if((jeu.getConstMonstre().getPos().x==i)&&(jeu.getConstMonstre().getPos().y==j)){
                if(jeu.getConstMonstre().getTailleM()==1) cadre[i][j]='M';
                else cadre[i][j]='MM';
            }
            if(/*plateforme*/){

            }
            if(/*Bonus*/){

            }

        }
    }

}

void JeuModeTXT::affichageTXT(Jeu &jeu){


    
    for(int i=0;i<15;i++){
        for(int j=0;j<21;j++){
            cout<<cadre[i][j];
        }
         cout<<endl;
    }


}   