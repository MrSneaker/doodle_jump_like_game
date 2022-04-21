#include "Jeu.h"
#include "JeuModeTXT.h"

using namespace std;

double dt = 1.0 / 60.0;

int main(void)
{
    time_t t;
    srand((unsigned)time(&t));
    Jeu jeu;
    JeuModeTXT txt;
    bool ok = jeu.getConstPersonnage().enVie;
    jeu.InitPersonnage();
    jeu.InitPlat();
    jeu.InitBonus();
    jeu.InitMonstre();
    txt.InitCam();
    txt.updatePlateau(jeu);
    txt.affichageTXT(jeu, dt);
    std::chrono::high_resolution_clock timer;
    do
    {
        auto start = timer.now();
        jeu.update(dt);
        txt.boucleAffTXT(jeu, dt);
        ok = jeu.getConstPersonnage().enVie;
        auto stop = timer.now();
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
        //cout<<"pos perso x cadre: "<<txt.convertPos(jeu.getConstPersonnage().getPos()).x;
        cout<<"pos perso y : "<<txt.convertPos(jeu.getConstPersonnage().getPos()).y;
        cout<<"pos perso jeu y : "<<jeu.getConstPersonnage().getPos().y;
        //cout<<"pos cam x : "<<txt.cam.x;
    } while (ok);
    cout << "partie terminée.." << endl;
    return 0;
}