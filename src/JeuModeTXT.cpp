#include "JeuModeTXT.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

const int DIMX = 15;
const int DIMY = 30;

JeuModeTXT::JeuModeTXT()
{
    cam.x = 0;
    cam.y = 0;
}

JeuModeTXT::~JeuModeTXT()
{
}

char cadre[15][30] = {
    "#############################",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#############################"};

char cadreClear[15][30] = {
    "#############################",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#############################"};

void termClear() // efface le terminal
{
    system("clear");
}

void termInit() // configure la saisie : ne pas afficher les caracteres tapes
{

    struct termios ttystate;
    bool state = true;

    // get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state)
    {
        // turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        // minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else
    {
        // turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    // set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

Vec2 JeuModeTXT::convertPos(Vec2 pos)
{
    Vec2 newPos;
    double scaleX = 100 / DIMX;
    // double scaleY = 12 / DIMY;
    newPos.x = ((pos.x - cam.x) / scaleX + DIMX / 2);
    newPos.y = (DIMY * pos.y) / 12;
    //if (newPos.x >= 0 && newPos.x <= DIMX && newPos.y >=0 && newPos.y <= DIMY)
        return newPos;
}

void JeuModeTXT::InitCam()
{
    cam.x = convertPos(jeu.getConstPersonnage().getPos()).x + DIMX / 2;
    cam.y = convertPos(jeu.getConstPersonnage().getPos()).y + DIMY / 2;
}

void JeuModeTXT::updatePlateau(Jeu &jeu)
{
    float newcamX = convertPos(jeu.getConstPersonnage().getPos()).x;
    cout << "newcamX : " << newcamX;
    if (newcamX <= cam.x)
        cam.x = newcamX;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if ((int(convertPos(jeu.getConstPersonnage().getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstPersonnage().getPos()).y) == j) && (jeu.getConstPersonnage().enVie == true))
            {
                cadre[i][j] = 'l';
                cadre[i - 1][j] = 'o';
                cadre[i - 1][j + 1] = 'o';
                cadre[i][j + 1] = 'l';
            }
            for (int m = 0; m < 4; m++)
            {
                if ((int(convertPos(jeu.getConstMonstre(m).getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstMonstre(m).getPos()).y) == j) && (jeu.getConstMonstre(m).enVie == true) && ((int(convertPos(jeu.getConstMonstre(m).getPos()).x) > 0)))
                {
                    if (jeu.getConstMonstre(m).getTailleM().y == 1)
                    {
                        cadre[i][j] = 'M';
                        cadre[i - 1][j] = 'm';
                        cadre[i - 1][j + 1] = 'm';
                        cadre[i][j + 1] = 'm';
                    }
                    else
                        cadre[i][j] = 'M';
                }
            }
            for (long unsigned int p = 0; p < jeu.getPlateforme().size(); p++)
            {
                if ((int(convertPos(jeu.getPlateforme().at(p).getPos()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getPlateforme().at(p).getPos()).y) == j) && (jeu.getPlateforme().at(p).estAfficheable() == true) && (int(convertPos(jeu.getPlateforme().at(p).getPos()).x) > 0))
                {
                    if (jeu.getPlateforme().at(p).getTaille().y == 2)
                    {
                        cadre[i][j] = '_';
                        cadre[i][j + 1] = '_';
                        cadre[i][j + 2] = '_';
                        cadre[i][j + 3] = '_';
                        // cout<<"pos conv plat x: "<<convertPos(jeu.getPlateforme().at(p).getPos()).x;
                        // cout<<"pos conv plat y: "<<convertPos(jeu.getPlateforme().at(p).getPos()).y;
                    }
                }
            }
            for (int pr = 0; pr < jeu.getConstPersonnage().getNombreProj(); pr++)
            {
                Vec2 pospr = convertPos(jeu.getConstPersonnage().getProjectileAff(pr).getpos());
                if ((int(pospr.x - cam.x + DIMX / 2) == i) && (int(pospr.y) == j) && (jeu.getConstPersonnage().getProjectileAff(pr).existe) && ((int(pospr.x) > 0)))
                {
                    cadre[i][j] = '.';
                }
            }
            for (int b = 0; b < 4; b++)
            {
                if ((int(convertPos(jeu.getConstBonus(b).getPosBonus()).x - cam.x + DIMX / 2) == i) && (int(convertPos(jeu.getConstBonus(b).getPosBonus()).y) == j) && (jeu.getConstBonus(b).estPris == false) && ((int(convertPos(jeu.getConstBonus(b).getPosBonus()).x) > 0)))
                {
                    if (jeu.getConstBonus(b).getNomB() == "j")
                    {
                        cadre[i][j] = 'j';
                        cadre[i - 1][j] = 'j';
                        cadre[i - 1][j + 1] = 'j';
                        cadre[i][j + 1] = 'j';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "h")
                    {
                        cadre[i][j] = 'h';
                        cadre[i - 1][j] = 'h';
                        cadre[i - 1][j + 1] = 'h';
                        cadre[i][j + 1] = 'h';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "r")
                    {
                        cadre[i][j] = 'r';
                        cadre[i - 1][j] = 'r';
                        cadre[i - 1][j + 1] = 'r';
                        cadre[i][j + 1] = 'r';
                    }

                    if (jeu.getConstBonus(b).getNomB() == "b")
                    {
                        cadre[i][j] = 'b';
                        cadre[i - 1][j] = 'b';
                        cadre[i - 1][j + 1] = 'b';
                        cadre[i][j + 1] = 'b';
                    }
                }
            }
        }
    }
}

void clear()
{
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 30; ++j)
            cadre[i][j] = cadreClear[i][j];
}

void JeuModeTXT::affichageTXT(Jeu &jeu, double dt)
{
    termClear();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            cout << cadre[i][j];
        }
        cout << endl;
    }
}

void JeuModeTXT::boucleAffTXT(Jeu &jeu, double dt)
{
    updatePlateau(jeu);
    affichageTXT(jeu, dt);
    usleep(100000);
    int c = jeu.getCh();
    switch (c)
    {
    case 'g':
        jeu.actionClavier('g', dt);
        break;
    case 'd':
        jeu.actionClavier('d', dt);
        break;
    case 'r':
        jeu.actionClavier('r', dt);
        break;
    }
    clear();
    // cout<<ok;
    // cout<<jeu.getPlateforme().size();
}