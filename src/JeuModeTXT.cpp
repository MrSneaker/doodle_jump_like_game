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
    newPos.x = (DIMX * pos.x) / 100;
    newPos.y = (DIMY * pos.y) / 12;
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
    if (newcamX <= cam.x)
        cam.x = newcamX;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            int persoX = int(convertPos(jeu.getConstPersonnage().getPos()).x - cam.x + DIMX / 2);
            int persoY = int(convertPos(jeu.getConstPersonnage().getPos()).y);
            if ((persoX == i) && (persoY == j) && (jeu.getConstPersonnage().enVie == true))
            {
                cadre[i][j] = 'l';
                cadre[i - 1][j] = 'o';
                cadre[i - 1][j + 1] = 'o';
                cadre[i][j + 1] = 'l';
            }
            for (int m = 0; m < NB_MONSTRE; m++)
            {
                int monstreX = int(convertPos(jeu.getConstMonstre(m).getPos()).x - cam.x + DIMX / 2);
                int monstreY = int(convertPos(jeu.getConstMonstre(m).getPos()).y);
                if ((monstreX == i) && (monstreY == j) && (jeu.getConstMonstre(m).enVie == true))
                {
                    if (jeu.getConstMonstre(m).getTailleM().y == 1)
                    {
                        cadre[i][j] = 'm';
                        cadre[i - 1][j] = 'm';
                        cadre[i - 1][j + 1] = 'm';
                        cadre[i][j + 1] = 'm';
                    }
                    else if (jeu.getConstMonstre(m).getTailleM().y > 1)
                    {
                        cadre[i][j] = 'm';
                        cadre[i - 1][j] = 'm';
                        cadre[i - 1][j + 1] = 'm';
                        cadre[i][j + 1] = 'm';
                        cadre[i - 1][j + 2] = 'm';
                        cadre[i][j + 2] = 'm';
                    }
                }
            }
            for (long unsigned int p = 0; p < jeu.getPlateforme().size(); p++)
            {
                int plX = int(convertPos(jeu.getPlateforme().at(p).getPos()).x - cam.x + DIMX / 2);
                int plY = int(convertPos(jeu.getPlateforme().at(p).getPos()).y);
                if ((plX == i) && (plY == j) && (jeu.getPlateforme().at(p).estAfficheable() == true))
                {
                    if (jeu.getPlateforme().at(p).getRes() == -1)
                    {
                        cadre[i][j] = '_';
                        cadre[i][j + 1] = '_';
                        cadre[i][j + 2] = '_';
                        cadre[i][j + 3] = '_';
                    }
                    if (jeu.getPlateforme().at(p).getRes() == 1)
                    {
                        cadre[i][j] = '*';
                        cadre[i][j + 1] = '*';
                        cadre[i][j + 2] = '*';
                        cadre[i][j + 3] = '*';
                    }
                }
            }
            for (int pr = 0; pr < jeu.getConstPersonnage().getNombreProj(); pr++)
            {
                Vec2 pospr = convertPos(jeu.getConstPersonnage().getProjectileAff(pr).getpos());
                bool prExiste = jeu.getConstPersonnage().getProjectileAff(pr).existe;
                if ((int(pospr.x - cam.x + DIMX / 2) == i) && (int(pospr.y) == j) && (prExiste))
                {
                    cadre[i][j] = '.';
                }
            }
            for (int b = 0; b < NB_BONUS; b++)
            {
                int bonusX = int(convertPos(jeu.getConstBonus(b).getPosBonus()).x - cam.x + DIMX / 2);
                int bonusY = int(convertPos(jeu.getConstBonus(b).getPosBonus()).y);
                if ((bonusX == i) && (bonusY == j) && (jeu.getConstBonus(b).estPris == false))
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
                    if (jeu.getConstBonus(b).getNomB() == "t")
                    {
                        cadre[i][j] = 't';
                        cadre[i - 1][j] = 't';
                        cadre[i - 1][j + 1] = 't';
                        cadre[i][j + 1] = 't';
                    }
                }
            }
        }
    }
}

void JeuModeTXT::affDetruireTXT()
{
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 30; ++j)
            cadre[i][j] = cadreClear[i][j];
}

int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); // STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

char getCh()
{ // lire un caractere si une touche a ete pressee
    char touche = 0;
    if (kbhit())
    {
        touche = fgetc(stdin);
    }

    return touche;
}

void JeuModeTXT::affichageTXT(Jeu &jeu)
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
    jeu.update(dt);
    updatePlateau(jeu);
    bool ok = jeu.getConstPersonnage().enVie;
    std::chrono::high_resolution_clock timer;
    do
    {
        auto start = timer.now();
        usleep(100000);
        jeu.update(dt);
        updatePlateau(jeu);
        affichageTXT(jeu);
        auto stop = timer.now();
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
        ok = jeu.getConstPersonnage().enVie;
        int c = getCh();
        switch (c)
        {
        case 'g':
            jeu.actionClavier('d', dt);
            break;
        case 'd':
            jeu.actionClavier('g', dt);
            break;
        case 'r':
            jeu.actionClavier('r', dt);
            break;
        case 'q':
            ok = jeu.actionClavier('q', dt);
        }
        affDetruireTXT();
    } while (ok);
}
