#include "JeuModeTXT.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

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


char cadreClear[15][21] = {
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

void termClear()  // efface le terminal
{
    system("clear");
}

void termInit()      // configure la saisie : ne pas afficher les caracteres tapes
{

    struct termios ttystate;
    bool state = true;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void JeuModeTXT::updatePlateau(Jeu &jeu){
    for(int i=0;i<15;i++){
        for(int j=0;j<21;j++){
            if((int(jeu.getConstPersonnage().getPos().x)==i)&&(int(jeu.getConstPersonnage().getPos().y)==j)&&(jeu.getConstPersonnage().enVie==true)){
                cadre[i][j]='O';
            }
            for(int m=0;m<4;m++){
                if((int(jeu.getConstMonstre(m).getPos().x)==i)&&(int(jeu.getConstMonstre(m).getPos().y)==j)&&(jeu.getConstMonstre(m).enVie==true)){
                    if(jeu.getConstMonstre(m).getTailleM()==1) cadre[i][j]='M';
                    else cadre[i][j]='MM';
                }
            }
            for(int p=0;p<jeu.getPlateforme().size();p++){
                if((jeu.getPlateforme().at(p).getPos().x==i)&&(jeu.getPlateforme().at(p).getPos().y==j)&&(jeu.getPlateforme().at(p).estAfficheable()==true)){
                    if(jeu.getPlateforme().at(p).getTaille()==1) {
                        cadre[i][j]='_';
                    }
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


}

void clear () {
    for(int i=0;i<15;++i)
        for(int j=0;j<21;++j)
            cadre[i][j]=cadreClear[i][j];
}

void JeuModeTXT::affichageTXT(Jeu &jeu, double dt){    
    termClear();
    for(int i=0;i<15;i++){
        for(int j=0;j<21;j++){
            cout<<cadre[i][j];
        }
         cout<<endl;
    }
}   




void JeuModeTXT::boucleAffTXT(Jeu &jeu,double dt){
    updatePlateau(jeu);
    affichageTXT(jeu, dt);
    usleep(100000);
    int c=jeu.getCh();
    switch(c){
        case 'g':
            jeu.actionClavier('g',dt);
            break;
        case 'd':
            jeu.actionClavier('d', dt);
            break;
        case 'r':
            jeu.actionClavier('r', dt);
            break;
    }
    clear();
    //cout<<ok;
    //cout<<jeu.getPlateforme().size();
}