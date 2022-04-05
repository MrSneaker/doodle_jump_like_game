#ifndef __JEUMODEGRAPHIQUE_H__
#define __JEUMODEGRAPHIQUE_H__

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>


//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface *m_surface;
    SDL_Texture *m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



class JeuModeGRAPHIQUE
{
private:
    Jeu jeu;
    SDL_Window * window; /*fenetre SDL */ 
    int winx, winy;
    int TAILLE_BORDURE;
    SDL_Renderer * renderer; /*render SDL */
    SDL_Surface *screen = NULL ;
    SDL_Surface *background  = NULL ;
    SDL_Surface *menu[3] = {NULL} ;
    SDL_Rect *rectangle;
    TTF_Font *police_ecriture;
    
    //image img_Perso;
    //image img_Monstres;
    
    
public:
    JeuModeGRAPHIQUE();
    ~JeuModeGRAPHIQUE();
    void updatePlateau(Jeu &jeu);
    void affichageInitGRAPHIQUE(Jeu &jeu, double dt);
    void boucleAffGRAPHIQUE(Jeu &jeu, double dt);
    void affDetruireGRAPHIQUE(Jeu &jeu);
    
};




#endif