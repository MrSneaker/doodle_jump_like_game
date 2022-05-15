#include "JeuModeTXT.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

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

    // donne l'état du terminal.
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state)
    {
        // mode canonique sur off.
        ttystate.c_lflag &= ~ICANON;
        // minimum d'input lu.
        ttystate.c_cc[VMIN] = 1;
    }
    else
    {
        // mode canonique sur on.
        ttystate.c_lflag |= ICANON;
    }
    // initialise les attributs du terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

Vec2 JeuModeTXT::convertPos(Vec2 pos)
{
    Vec2 newPos; // position tampon.
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
    float newcamX = convertPos(jeu.getConstPersonnage().getPos()).x; // la caméra est mise à jour par rapport à la hauteur du personnage.
    if (newcamX <= cam.x)                                            // si la nouvelle position de la caméra est au dessus de l'ancienne, newCamX est affecté à cam.x.
        cam.x = newcamX;
    for (int i = 0; i < DIMX; i++) // sur toute la hauteur (dans le terminal X est l'ordonnée, c'est pour cela que la classe "Jeu" a été pensé avec X comme ordonnée).
    {
        for (int j = 0; j < DIMY; j++) // et sur toute la largeur..
        {
            int persoX = int(convertPos(jeu.getConstPersonnage().getPos()).x - cam.x + DIMX / 2); // on prend la position du personnage (décalé de cam.x + DIMX/2 en ordonnée pour le défilement, comme tous les objets).
            int persoY = int(convertPos(jeu.getConstPersonnage().getPos()).y);
            if ((persoX == i) && (persoY == j) && (jeu.getConstPersonnage().enVie == true)) // si la position du personnage correspond à une position écran et qu'il est vivant, on l'affiche.
            {
                cadre[i][j] = 'l';
                cadre[i - 1][j] = 'o';
                cadre[i - 1][j + 1] = 'o';
                cadre[i][j + 1] = 'l';
            }
            for (int m = 0; m < NB_MONSTRE; m++) // on boucle sur les monstres et on applique le même principe.
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
            for (long unsigned int p = 0; p < jeu.getPlateforme().size(); p++) // même principe que le reste.
            {
                int plX = int(convertPos(jeu.getPlateforme().at(p).getPos()).x - cam.x + DIMX / 2);
                int plY = int(convertPos(jeu.getPlateforme().at(p).getPos()).y);
                if ((plX == i) && (plY == j) && (jeu.getPlateforme().at(p).estAfficheable() == true)) // on affiche si elle est affichable et que la position correspond.
                {
                    if (jeu.getPlateforme().at(p).getRes() == -1) // on fait un affichage différent selon les propriétées (ici la resistance).
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
            for (int pr = 0; pr < jeu.getConstPersonnage().getNombreProj(); pr++) // même chose pour les projectiles..
            {
                Vec2 pospr = convertPos(jeu.getConstPersonnage().getProjectileAff(pr).getpos());
                bool prExiste = jeu.getConstPersonnage().getProjectileAff(pr).existe;
                if ((int(pospr.x - cam.x + DIMX / 2) == i) && (int(pospr.y) == j) && (prExiste))
                {
                    cadre[i][j] = '.';
                }
            }
            for (int b = 0; b < NB_BONUS; b++) //.. et même chose pour les bonus.
            {
                int bonusX = int(convertPos(jeu.getConstBonus(b).getPosBonus()).x - cam.x + DIMX / 2);
                int bonusY = int(convertPos(jeu.getConstBonus(b).getPosBonus()).y);
                if ((bonusX == i) && (bonusY == j) && (jeu.getConstBonus(b).estPris == false))
                {
                    if (jeu.getConstBonus(b).getNomB() == "j") // on affiche une lettre différente par bonus.
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

void JeuModeTXT::affDetruireTXT() // la destruction est faite en faisant un blanc de tout l'écran.
{
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 30; ++j)
            cadre[i][j] = cadreClear[i][j]; // on utilise cadreClear qui est exactement le cadre mais qu'on ne modifie jamais.
}

int kbhit() // fonction indiquant si une touche à été tapé. retourne 0 si aucune valeur lu, valeur non nulle sinon.
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
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
    termClear();                 // on efface le terminal.
    for (int i = 0; i < 15; i++) // on affiche le cadre de jeu.
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
    jeu.update(dt);                           // on update le jeu.
    updatePlateau(jeu);                       // on update le cadre de jeu.
    bool ok = jeu.getConstPersonnage().enVie; // tant que notre personnage est en vie on peut jouer.
    std::chrono::high_resolution_clock timer; // on initialise une clock pour mesurer le delta dt, la vitesse de rafraichissement du jeu.
    do
    {
        auto start = timer.now();                                                             // point de départ de la mesure de dt.
        usleep(100000);                                                                       // ici c'est la boucle d'affichage du jeu, on met un délai de 100000 microsecondes entre chaque boucle.
        jeu.update(dt);                                                                       // update du jeu.
        updatePlateau(jeu);                                                                   // update de l'affichage.
        affichageTXT(jeu);                                                                    // affichage à l'écran.
        auto stop = timer.now();                                                              // fin de la mesure de dt.
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count(); // on assigne à dt sa nouvelle valeur.
        ok = jeu.getConstPersonnage().enVie;                                                  // on regarde si le personnage est toujours en vie.
        int c = getCh();                                                                      // on prend en compte les entrées clavier.
        switch (c)
        {
        case 'g': // personnage va à gauche.
            jeu.actionClavier('d', dt);
            break;
        case 'd': // personnage va à droite.
            jeu.actionClavier('g', dt);
            break;
        case 'r': // personnage tir.
            jeu.actionClavier('r', dt);
            break;
        case 'q': // quitter le jeu.
            ok = jeu.actionClavier('q', dt);
        }
        affDetruireTXT(); // on détruit l'affichage pour raffraichir.
    } while (ok);
}
