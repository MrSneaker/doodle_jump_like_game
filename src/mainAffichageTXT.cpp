#include "Jeu.h"
#include "JeuModeTXT.h"
#include <chrono>

using namespace std;

double dt = 1.0 / 60.0;

int main(void){
    bool ok=true;
    Jeu jeu;
    JeuModeTXT txt;
    jeu.InitPersonnage();
    jeu.InitPlat();
    jeu.InitBonus();
    //jeu.InitMonstre();
    txt.updatePlateau(jeu);
    txt.affichageTXT(jeu,dt);
    std::chrono::high_resolution_clock timer;
    do{
        //cout<< dt;
        auto start = timer.now();
        jeu.update(dt);
        txt.boucleAffTXT(jeu,ok,dt);
        auto stop = timer.now();
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
        //cout << dt ;
    }while(ok);

    return 0;
}