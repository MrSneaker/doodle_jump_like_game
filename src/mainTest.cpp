#include "Personnage.h"
#include "Monstre.h"
#include "projectile.h"
#include "vec2.h"
#include "bonus.h"
#include "Plateforme.h"
#include <iostream>

using namespace std;

int main(void)
{
    Personnage p;
    Monstre m;
    bonus b;
    Plateforme pl;
    p.testRegression();
    m.testRegression();
    b.testRegression();
    pl.testRegression();
}
