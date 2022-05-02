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
    txt.InitCam();
    txt.boucleAffTXT(jeu,dt);
    cout << "partie terminée.." << endl;
    return 0;
}