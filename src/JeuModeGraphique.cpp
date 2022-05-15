#include "JeuModeGraphique.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

// ============= CLASS JEUMODEGRAPHIQUE =============== //

JeuModeGRAPHIQUE::JeuModeGRAPHIQUE() // toutes les textures sont initialisées à NULL.
{
    cam.x = 0;
    cam.y = 0;
    texturePersD = NULL;
    texturePersG = NULL;
    texturePersF = NULL;
    texturePersS = NULL;
    texturePersJ[0] = NULL;
    texturePersH[0] = NULL;
    texturePersJ[1] = NULL;
    texturePersH[1] = NULL;
    textureBackground = NULL;
    texturePlat[0] = NULL;
    texturePlat[1] = NULL;
    texturePersB[0] = NULL;
    texturePersB[1] = NULL;
    font = NULL;
    for (int i = 0; i < NB_BONUS; i++)
    {
        textureBonus[i] = NULL;
    }
    for (int i = 0; i < NB_MONSTRE; i++)
    {
        textureMonstre[i] = NULL;
    }
    projTex = NULL;
}

JeuModeGRAPHIQUE::~JeuModeGRAPHIQUE()
{
}

Vec2 JeuModeGRAPHIQUE::convertPos(Vec2 pos)
{
    Vec2 newPos;                     // on prend une position tampon..
    newPos.x = (DIMY * pos.x) / 100; // DIMY pour x car les axes du jeu sont inversées par rapport à ceux de la SDL (dans Jeu, ils sont adaptés au mode texte avec X en ordonnée et Y en abscisse.)
    newPos.y = (DIMX * pos.y) / 12;  // pour les même raison, DIMX pour y.
    return newPos;                   // ..qu'on renvoie apres convertion.
}

void JeuModeGRAPHIQUE::InitCam()
{
    cam.x = 0;
    cam.y = convertPos(jeu.getConstPersonnage().getPos()).x - DIMX / 2; // pour les même raisons qu'au dessus, cam.y = position logique du personnage en x.
}

void JeuModeGRAPHIQUE::affichageInitGRAPHIQUE()
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Initialisation de l'écriture
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Foodle_Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DIMX, DIMY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // initialisation de SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Initialisation de SDL_Mix.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        withSound = false;
    }
    else
        withSound = true;

    // Initialisation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "erreur lors de la création du rendu " << endl;
        SDL_Quit();
        exit(1);
    }
}

void JeuModeGRAPHIQUE::InitTexture() // chargement de toutes les textures depuis data/ .
{
    textureBackground = IMG_LoadTexture(renderer, "data/background.png");
    texturePersG = IMG_LoadTexture(renderer, "data/persoGauche.png");
    texturePersD = IMG_LoadTexture(renderer, "data/persoDroite.png");
    texturePersF = IMG_LoadTexture(renderer, "data/persoDroite.png");
    texturePersS = IMG_LoadTexture(renderer, "data/persoFace.png");
    texturePersH[0] = IMG_LoadTexture(renderer, "data/persoHelico.png");
    texturePersJ[0] = IMG_LoadTexture(renderer, "data/persoFuseeDroite.png");
    texturePersH[1] = IMG_LoadTexture(renderer, "data/persoHelicoG.png");
    texturePersJ[1] = IMG_LoadTexture(renderer, "data/persoFuseeGauche.png");
    texturePersB[0] = IMG_LoadTexture(renderer, "data/persoDroiteBoing.png");
    texturePersB[1] = IMG_LoadTexture(renderer, "data/persoGaucheBoing.png");

    texturePlat[0] = IMG_LoadTexture(renderer, "data/plateforme1.png");
    texturePlat[1] = IMG_LoadTexture(renderer, "data/plateforme4.png");

    textureMonstre[0] = IMG_LoadTexture(renderer, "data/monstre1.png");
    textureMonstre[1] = IMG_LoadTexture(renderer, "data/monstre2.png");
    textureMonstre[2] = IMG_LoadTexture(renderer, "data/monstre3.png");
    textureMonstre[3] = IMG_LoadTexture(renderer, "data/monstre4.png");

    textureBonus[0] = IMG_LoadTexture(renderer, "data/bonus1.png");
    textureBonus[1] = IMG_LoadTexture(renderer, "data/bonus2.png");
    textureBonus[2] = IMG_LoadTexture(renderer, "data/bonus3.png");
    textureBonus[3] = IMG_LoadTexture(renderer, "data/bonus4.png");
    textureBonus[4] = IMG_LoadTexture(renderer, "data/bonus42.png");
    textureBonus[5] = IMG_LoadTexture(renderer, "data/hole.png");

    projTex = IMG_LoadTexture(renderer, "data/projectile.png");
}

void JeuModeGRAPHIQUE::initSon() // chargement de tous les sons depuis data/ .
{
    saut = Mix_LoadMUS("data/jump.wav");
    helico = Mix_LoadMUS("data/helico.mp3");
    jetpack = Mix_LoadMUS("data/fusee.mp3");
    tir = Mix_LoadMUS("data/pucanje.mp3");
    Mmeurt = Mix_LoadMUS("data/monsterpogodak.mp3");
    ressort = Mix_LoadMUS("data/feder.mp3");
    Pmort = Mix_LoadMUS("data/pada.mp3");
}

void JeuModeGRAPHIQUE::initFont() // chargement de la police depuis data/ .
{
    font = TTF_OpenFont("data/PIXEAB__.TTF", 15);
    font_color = {0, 0, 0};
}

void JeuModeGRAPHIQUE::affichageGRAPHIQUE(Jeu &jeu, double dt) // affichage et mise à jour du rendu graphique.
{
    float newcamY = convertPos(jeu.getConstPersonnage().getPos()).x; // mise à jour de la caméra.
    if (newcamY <= cam.y)
        cam.y = newcamY;

    SDL_RenderCopy(renderer, textureBackground, NULL, NULL);         // affichage de l'arrière plan.
    string tmp = to_string(jeu.score);                               // conversion du score en string.
    const char *scoreString = tmp.c_str();                           // conversion du string contenant le score en chaine de caractères.
    scoreSurf = TTF_RenderText_Solid(font, scoreString, font_color); // création de la surface affichant le score en temps réel.
    SDL_Rect scoreRect;                                              // rectangle d'affichage du score.
    scoreRect.x = 0;
    scoreRect.y = 0;
    scoreRect.w = 100;
    scoreRect.h = 100;
    score = SDL_CreateTextureFromSurface(renderer, scoreSurf); // création de la texture d'affichage du score.
    SDL_FreeSurface(scoreSurf);                                // on libère la surface car elle est maintenant inutile.

    // la méthode qui suit est la même pour l'intégralité de l'affichage sur tous les objets.

    const Personnage &perso = jeu.getConstPersonnage(); // on récupère le personnage.
    SDL_Rect rectPers;                                  // on lui crée son rectangle d'affichage..
    rectPers.x = convertPos(perso.getPos()).y;
    rectPers.y = convertPos(perso.getPos()).x - cam.y + DIMY / 2; // on applique le décalage caméra sur l'axe des ordonnées.
    rectPers.h = perso.getTaille().x * TAILLE_SPRITE;
    rectPers.w = perso.getTaille().y * TAILLE_SPRITE;
    if (jeu.Pdroite && !perso.aPrisB) // si le personnage va à droite et n'a pas de bonus, on renvoie la texture correspondante.
    {
        SDL_RenderCopy(renderer, texturePersD, NULL, &rectPers);
    }
    else if (jeu.Pgauche && !perso.aPrisB) // si le personnage va à gauche et n'a pas de bonus, on renvoie la texture correspondante.
    {
        SDL_RenderCopy(renderer, texturePersG, NULL, &rectPers);
    }
    else if (jeu.Ptire && !perso.aPrisB) // si le personnage tir et n'a pas de bonus, on renvoie la texture correspondante.
    {
        SDL_RenderCopy(renderer, texturePersS, NULL, &rectPers);
    }
    else if (!perso.aPrisB) // si le personnage n'a pas de bonus et ne fait rien, on renvoie la texture correspondante.
        SDL_RenderCopy(renderer, texturePersF, NULL, &rectPers);
    int nbPl = jeu.getPlateforme().size(); // on prend le nombre de plateforme à afficher.
    for (int i = 0; i < nbPl; i++)         // pour l'intégraliter des plateformes..
    {
        SDL_Rect rectPlat; // même méthode que le personnage.
        const Plateforme &Pl = jeu.getPlateforme().at(i);
        rectPlat.x = convertPos(Pl.getPos()).y;
        rectPlat.y = convertPos(Pl.getPos()).x - cam.y + DIMY / 2;
        rectPlat.h = Pl.getTaille().x * TAILLE_SPRITE;
        rectPlat.w = Pl.getTaille().y * TAILLE_SPRITE;
        if (Pl.estAfficheable()) // si la plateforme est affichable..
        {
            if (Pl.getRes() == -1) //.. et si elle a une resistance de -1, on affiche cette texture..
            {
                SDL_RenderCopy(renderer, texturePlat[0], NULL, &rectPlat);
            }
            else if (Pl.getRes() == 1) // .. sinon si c'est 1 on affiche la deuxième.
            {
                SDL_RenderCopy(renderer, texturePlat[1], NULL, &rectPlat);
            }
        }
    }
    for (int i = 0; i < NB_MONSTRE; i++) // pour tous les monstres..
    {
        const Monstre &mon = jeu.getConstMonstre(i); // même méthode que le personnage.
        SDL_Rect rectM;
        float tailleY = mon.getTailleM().x;
        float tailleX = mon.getTailleM().y;
        rectM.x = convertPos(mon.getPos()).y;
        rectM.y = convertPos(mon.getPos()).x - cam.y + DIMY / 2;
        rectM.h = tailleY * TAILLE_SPRITE;
        rectM.w = tailleX * TAILLE_SPRITE;
        if (tailleX == 2 && tailleY == 1 && mon.enVie) // on affiche la texture correspondant à la bonne taille, c'est l'élément de différenciation.
        {
            SDL_RenderCopy(renderer, textureMonstre[0], NULL, &rectM);
        }
        else if (tailleX == 1 && tailleY == 1 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[1], NULL, &rectM);
        }
        else if (tailleX == 1 && tailleY == 1.5 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[2], NULL, &rectM);
        }
        else if (tailleX == 2 && tailleY > 0.5 && mon.enVie)
        {
            SDL_RenderCopy(renderer, textureMonstre[3], NULL, &rectM);
        }
        if (jeu.Mtouche1 || jeu.Mtouche2) // si on touche/tue un monstre..
        {
            Mix_PlayMusic(Mmeurt, 1); // .. on joue le son correspondant.
            jeu.Mtouche1 = false;     // on indique que le son à été joué.
            jeu.Mtouche2 = false;
        }
    }
    for (int i = 0; i < NB_BONUS; i++) // pour tous les bonus..
    {
        const bonus &bon = jeu.getConstBonus(i); // même méthode que le personnage.
        SDL_Rect rectB;
        rectB.x = convertPos(bon.getPosBonus()).y;
        rectB.y = convertPos(bon.getPosBonus()).x - cam.y + DIMY / 2;
        rectB.h = bon.getTailleB().x * TAILLE_SPRITE;
        rectB.w = bon.getTailleB().y * TAILLE_SPRITE;
        if (bon.getNomB() == "h" && !bon.estPris) // si le bonus avec le nom indiqué n'est pas pris, on affiche le sprite de l'objet.
        {
            SDL_RenderCopy(renderer, textureBonus[0], NULL, &rectB);
        }
        else if (bon.getNomB() == "j" && !bon.estPris)
        {
            SDL_RenderCopy(renderer, textureBonus[1], NULL, &rectB);
        }
        else if (bon.getNomB() == "b" && !bon.estPris)
        {
            SDL_RenderCopy(renderer, textureBonus[2], NULL, &rectB);
        }
        else if (bon.getNomB() == "r") // pour le ressort, on affiche une texture quand il est pris et une quand il ne l'est pas, pour faire une petite animation.
        {
            if (bon.estPris)
            {
                Mix_PlayMusic(ressort, 1); // on joue le son du ressort quand il est pris.
                SDL_RenderCopy(renderer, textureBonus[4], NULL, &rectB);
                if (jeu.Pdroite) // on indique la texture que le personnage doit avoir dans cet état.
                    SDL_RenderCopy(renderer, texturePersD, NULL, &rectPers);
                else
                    SDL_RenderCopy(renderer, texturePersG, NULL, &rectPers);
            }
            else
                SDL_RenderCopy(renderer, textureBonus[3], NULL, &rectB);
        }
        else if (bon.getNomB() == "t") // le trou noir ne peut pas être pris, donc pas besoin de le prendre en compte.
        {
            SDL_RenderCopy(renderer, textureBonus[5], NULL, &rectB);
        }
        if (bon.getNomB() == "h" && bon.estPris) // quand un bonus est pris, on prend en compte le temps pour lequel il l'est, et on joue le son du bonus.
        {
            Mix_PlayMusic(helico, 1);
            tpsH = bon.getDuree();
        }
        else if (bon.getNomB() == "j" && bon.estPris) // MEME PRINCIPE POUR LES BONUS SI-DESSOUS.
        {
            Mix_PlayMusic(jetpack, 1);
            tpsJ = bon.getDuree();
        }
        else if (bon.getNomB() == "b" && bon.estPris)
        {
            Mix_PlayMusic(ressort, 1);
            tpsB = bon.getDuree();
        }
        if (tpsH > 0) // si ce temps d'activation est détecté comme étant initialisé, alors on renvoie les textures correspondantes..
        {
            if (jeu.Pdroite) //.. en prenant en compte la direction du personnage.
                SDL_RenderCopy(renderer, texturePersH[0], NULL, &rectPers);
            else
                SDL_RenderCopy(renderer, texturePersH[1], NULL, &rectPers);
            tpsH -= dt; // on décrémente le temps d'activation.
        }
        else if (tpsJ > 0) // MEME PRINCIPE POUR TOUS LES BONUS SI-DESSOUS.
        {
            if (jeu.Pdroite)
                SDL_RenderCopy(renderer, texturePersJ[0], NULL, &rectPers);
            else
                SDL_RenderCopy(renderer, texturePersJ[1], NULL, &rectPers);
            tpsJ -= dt;
        }
        else if (tpsB > 0)
        {
            if (jeu.Pdroite)
                SDL_RenderCopy(renderer, texturePersB[0], NULL, &rectPers);
            else
                SDL_RenderCopy(renderer, texturePersB[1], NULL, &rectPers);
            tpsB -= dt;
        }
    }
    for (int i = 0; i < perso.getNombreProj(); i++) // affichage des projectiles.
    {
        const projectile &proj = perso.getProjectileAff(i); // toujours la même méthode.
        SDL_Rect rectProj;
        if (proj.existe)
        {
            rectProj.x = convertPos(proj.getpos()).y;
            rectProj.y = convertPos(proj.getpos()).x - cam.y + DIMY / 2;
            rectProj.h = 0.5 * TAILLE_SPRITE;
            rectProj.w = 0.5 * TAILLE_SPRITE;
            SDL_RenderCopy(renderer, projTex, NULL, &rectProj);
        }
    }
    if (jeu.getConstPersonnage().enVie == false) // si le personnage est mort, on joue le son correspondant à la fin de partie.
    {
        if (tpsSonMort == 0)
            tpsSonMort = 0.01;
    }
    SDL_RenderCopy(renderer, score, NULL, &scoreRect); // on fait le render du score ici pour l'afficher devant l'intégraliter des éléments.
    SDL_RenderPresent(renderer);
}

void JeuModeGRAPHIQUE::boucleAffGRAPHIQUE(Jeu &jeu, double dt)
{
    SDL_Event events;                         // on déclare une structure Event pour gérer les évènements (clavier/souris..).
    affichageInitGRAPHIQUE();                 // initialisation de la SDL.
    InitTexture();                            // initialisation des textures.
    initSon();                                // initialisation des sons.
    initFont();                               // initialisation des polices.
    std::chrono::high_resolution_clock timer; // on utilise une clock pour déterminer la vitesse de raffraichissements du jeu.
    bool quit = false;                        // condition du while.
    while (!quit)
    {
        auto start = timer.now();      // on commence la mesure du temps de raffraichissements.
        SDL_Delay(30);                 // on commence la boucle ici, et on met un délai de 30 milisecondes entre chaque affichage.
        jeu.update(dt);                // on update le jeu.
        while (SDL_PollEvent(&events)) // on prend en compte tous les évènements.
        {
            if (events.type == SDL_QUIT)         // si on quitte la fenêtre..
                quit = true;                     //.. on quitte le jeu.
            else if (events.type == SDL_KEYDOWN) // si on appuies sur une touche..
            {

                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:        // si c'est espace..
                    jeu.actionClavier('r', dt); // lance un projectile.
                    Mix_PlayMusic(tir, 1);
                    break;
                case SDL_SCANCODE_LEFT:         // si c'est flèche gauche..
                    jeu.actionClavier('g', dt); // se déplace a gauche.
                    break;
                case SDL_SCANCODE_RIGHT:        // si c'est flèche droite..
                    jeu.actionClavier('d', dt); // se déplace a droite.
                    break;
                case SDL_SCANCODE_A: // si c'est la touche Q (SCANCODE_A = Q car SDL fonctionne en QWERTY, si vous êtes en QWERTY ce sera A).
                    quit = true;     // quitte le jeu
                    break;
                default:
                    break;
                }
            }
        }
        if (jeu.PcollPl)                                                                      // si le personnage est en collision avec une plateforme..
            Mix_PlayMusic(saut, 1);                                                           // .. on joue le son du saut.
        affichageGRAPHIQUE(jeu, dt);                                                          // on affiche le jeu après l'update.
        auto stop = timer.now();                                                              // fin de mesure du temps de raffraichissement.
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count(); // dt = le temps mesuré.
        if (tpsSonMort > 0)                                                                   // si le son de la mort doit être joué, on le joue.
        {
            Mix_PlayMusic(Pmort, 1);
            tpsSonMort -= dt;
        }
        if (Mix_PlayingMusic() == 0 && jeu.getConstPersonnage().enVie == false) // on attend que les sons se termine pour quitter (spécialement celui de la fin de partie).
            quit = true;
    }
    affDetruireGRAPHIQUE(); // si on sort de la boucle alors on détruit tout.
}

void JeuModeGRAPHIQUE::affDetruireGRAPHIQUE() // on libère toute la mémoire, sans quitter la SDL qui sera encore utilisé pour le menu.
{
    if (withSound)
        Mix_Quit();
    Mix_FreeMusic(saut);
    Mix_FreeMusic(helico);
    Mix_FreeMusic(jetpack);
    Mix_FreeMusic(Mmeurt);
    Mix_FreeMusic(tir);
    Mix_FreeMusic(ressort);
    Mix_FreeMusic(Pmort);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(score);
    SDL_DestroyTexture(texturePersD);
    SDL_DestroyTexture(textureBackground);
    SDL_DestroyTexture(texturePersF);
    SDL_DestroyTexture(texturePersS);
    SDL_DestroyTexture(texturePersG);
    SDL_DestroyTexture(texturePlat[0]);
    SDL_DestroyTexture(texturePlat[1]);
    SDL_DestroyTexture(texturePersH[0]);
    SDL_DestroyTexture(texturePersH[1]);
    SDL_DestroyTexture(texturePersJ[0]);
    SDL_DestroyTexture(texturePersJ[1]);
    for (int i = 0; i < NB_BONUS; i++)
    {
        SDL_DestroyTexture(textureBonus[i]);
    }
    for (int i = 0; i < NB_MONSTRE; i++)
    {
        SDL_DestroyTexture(textureMonstre[i]);
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
}
