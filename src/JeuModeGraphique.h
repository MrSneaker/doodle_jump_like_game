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
    Jeu jeu;
    SDL_Window * window; /*fenetre SDL */ 
    SDL_Renderer * renderer; /*render SDL */
    SDL_Texture * texture;
    TTF_Font * font;
    SDL_Color font_color;
    bool souris;
    bool touche;
    Mix_Chunk * sound; 
    bool withSound;
    const int NB_BONUS = 4;
    const int NB_MONSTRE = 4;
    
    
public:
    JeuModeGRAPHIQUE();
    ~JeuModeGRAPHIQUE();
    JeuModeTXT txt;
    Vec2 cam;
    Vec2 convertPos(Vec2 pos);
    void InitCam();
    void affichageInitGRAPHIQUE(); /*! \brief affichage de SDL2*/
    void affichageGRAPHIQUE(Jeu &jeu, double dt); /*! \brief affiche l'image dans la fenetre SDL2*/
    void boucleAffGRAPHIQUE(Jeu &jeu, double dt); /*! \brief rafraichissement de l'image*/
    void affDetruireGRAPHIQUE(); /*! \brief Détruit l'affichage*/
    
    
    
};




#endif