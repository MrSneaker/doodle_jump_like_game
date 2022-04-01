#include "Jeu.h"
#include "JeuModeTXT.h"

using namespace std;

int main(void){
    bool ok=true;
    Jeu jeu;
    JeuModeTXT txt;
    jeu.InitPersonnage();
    jeu.InitPlat();
    jeu.InitBonus();
    //jeu.InitMonstre();
    txt.updatePlateau(jeu);
    txt.affichageTXT(jeu);
    do{
        jeu.update();
        txt.boucleAffTXT(jeu,ok);

    }while(ok);

    return 0;
}