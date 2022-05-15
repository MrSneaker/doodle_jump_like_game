#ifndef __JEUMODEGRAPHIQUE_H__
#define __JEUMODEGRAPHIQUE_H__

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include "JeuModeTXT.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>

class JeuModeGRAPHIQUE
{
private:
    Jeu jeu;                        /*! \brief Un objet jeu.*/
    Vec2 cam;                       /*! \brief Caméra du jeu.*/
    SDL_Window *window;             /*! \brief Une structure de fenêtre SDL.*/
    SDL_Renderer *renderer;         /*! \brief Une structure de rendu SDL.*/
    SDL_Texture *textureBackground; /*! \brief La texture de l'arrière plan.*/
    SDL_Texture *texturePersF;      /*! \brief La texture du personnage par défaut.*/
    SDL_Texture *texturePersD;      /*! \brief La texture du personnage quand il va à droite.*/
    SDL_Texture *texturePersG;      /*! \brief La texture du personnage quand il va à gauche*/
    SDL_Texture *texturePersS;      /*! \brief La texture du personnage quand il tire.*/
    SDL_Texture *texturePersJ[2];   /*! \brief Tableau une dimension de deux textures pour le personnage avec jetpack.*/
    SDL_Texture *texturePersH[2];   /*! \brief Tableau une dimension de deux textures pour le personnage avec Hélice*/
    SDL_Texture *texturePersB[2];   /*! \brief Tableau une dimension de deux textures pour le personnage avec bottes ressort.*/
    SDL_Texture *texturePlat[2];    /*! \brief Tableau une dimension de deux textures pour les plateformes.*/
    SDL_Texture *textureMonstre[4]; /*! \brief Tableau une dimension de quatres textures pour les monstres.*/
    SDL_Texture *textureBonus[6];   /*! \brief Tableau une dimension de six textures pour les bonus.*/
    SDL_Texture *projTex;           /*! \brief Texture du projectile.*/
    TTF_Font *font;                 /*! \brief Structure de police d'écriture SDL. */
    SDL_Color font_color;           /*! \brief Structure de couleurs SDL permettant de définir la couleur de la police.*/
    SDL_Surface *scoreSurf;         /*! \brief Surface permettant de créer la texture d'affichage du score.*/
    SDL_Texture *score;             /*! \brief Texture du score.*/
    Mix_Music *saut;                /*! \brief Son  pour le saut*/
    Mix_Music *helico;              /*! \brief Son pour l'hélice.*/
    Mix_Music *jetpack;             /*! \brief Son pour le jetpack.*/
    Mix_Music *tir;                 /*! \brief Son pour le tir.*/
    Mix_Music *Mmeurt;              /*! \brief Son pour signifier au joueur qu'il a touché un monstre / qu'il l'a tué.*/
    Mix_Music *ressort;             /*! \brief Son pour le ressort.*/
    Mix_Music *Pmort;               /*! \brief Son pour la mort du personnage.*/
    bool withSound;                 /*! \brief Booléen vérifiant le bon déroulement de l'initialisation de SDL_Mixer.*/
    const int NB_BONUS = 5;         /*! \brief Entier définissant le nombre de bonus/malus.*/
    const int NB_MONSTRE = 4;       /*! \brief Entier définnisant le nombre de monstre.*/
    float tpsJ = 0;                 /*! \brief Réel définnissant la durée du jetpack.*/
    float tpsH = 0;                 /*! \brief Réel définnissant la durée de l'hélice.*/
    float tpsB = 0;                 /*! \brief Réel définnissant la durée des bottes ressort.*/
    float tpsSonMort = 0;           /*! \brief Réel définnissant la durée du son pour la mort du personnage (pour éviter que le jeu se ferme pendant que le son joue).*/
    const int TAILLE_SPRITE = 32;   /*! \brief Entier définnissant la taille des sprites.*/
    const int DIMX = 300;           /*! \brief Entier déterminant la taille de l'affichage en X.*/
    const int DIMY = 600;           /*! \brief Entier déterminant la taille de l'affichage en Y.*/

public:
    JeuModeGRAPHIQUE();                           /*! \brief Constructeur de JeuModeGRAPHIQUE, initialise la caméra en 0,0 et initialise toutes les textures à NULL.*/
    ~JeuModeGRAPHIQUE();                          /*! \brief Destructeur de JeuModeGRAPHIQUE.*/
    Vec2 convertPos(Vec2 pos);                    /*! \brief Fonction de conversion des positions logiques vers les positions d'affichages.*/
    void InitCam();                               /*! \brief Initialisation de la caméra, 0 en x et égale à la position du personnage en y.*/
    void InitTexture();                           /*! \brief Initialisation des textures depuis leurs sources.*/
    void initSon();                               /*! \brief Initialisation des sons depuis leurs sources.*/
    void initFont();                              /*! \brief Initialisation des polices depuis leurs sources.*/
    void affichageInitGRAPHIQUE();                /*! \brief Initialisation de la SDL2.*/
    void affichageGRAPHIQUE(Jeu &jeu, double dt); /*! \brief Procédure d'affichage en fonction du jeu \param jeu passé par référence, et du double de la vitesse de raffraichissements \param dt.*/
    void boucleAffGRAPHIQUE(Jeu &jeu, double dt); /*! \brief Procédure permettant le rafraichissement de l'affichage en fonction du jeu \param jeu passé par référence et de la vitesse de raffraichissement \param dt, et la prise en compte des événements.*/
    void affDetruireGRAPHIQUE();                  /*! \brief Détruit l'affichage SDL, mais ne quitte pas SDL.*/
};

#endif